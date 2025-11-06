#include "dispatcher.h"

#include <dlfcn.h>

#include <iostream>
#include <set>

namespace cc_threads {

Dispatcher::Dispatcher() : BaseThread() {
    LoadProcessLib("libcc_simple_process.so", "Create");
    LoadProcessLib("libcc_advanced_process.so", "Create");

    std::set<uint32_t> unique_msgs;
    for (const auto& [msg_id, processes] : msg_routing_table_) {
        unique_msgs.insert(msg_id);
    }
    supported_msgs_.assign(unique_msgs.begin(), unique_msgs.end());
}

Dispatcher::~Dispatcher() {
    for (void* handle : lib_handles_) {
        dlclose(handle);
    }
}

void Dispatcher::LoadProcessLib(const std::string& lib_path,
                                const std::string& create_func_name) {
    void* handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "[DISPATCHER] [FATAL] Failed to load library " << lib_path
                  << ": " << dlerror() << std::endl;
        return;
    }
    lib_handles_.push_back(handle);

    dlerror();
    CreateProcessFunc create_func = reinterpret_cast<CreateProcessFunc>(
        dlsym(handle, create_func_name.c_str()));

    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "[DISPATCHER] [FATAL] Failed to find symbol "
                  << create_func_name << " in " << lib_path << ": "
                  << dlsym_error << std::endl;
        dlclose(handle);
        return;
    }

    std::unique_ptr<IBaseThread> process(create_func());
    IBaseThread* proc_ptr = process.get();
    processes_.push_back(std::move(process));

    const std::vector<uint32_t>& msgs = proc_ptr->GetSupportedMsg();
    for (uint32_t msg_id : msgs) {
        msg_routing_table_[msg_id].push_back(proc_ptr);
    }

    std::cout << "[DISPATCHER] [INFO] Successfully loaded library: " << lib_path
              << std::endl;
}

void Dispatcher::Process(uint32_t id) {
    auto it = msg_routing_table_.find(id);
    if (it != msg_routing_table_.end()) {
        std::cout << "[DISPATCHER] [INFO] Routing message " << id << " to "
                  << it->second.size() << " process(es)." << std::endl;
        for (IBaseThread* proc : it->second) {
            proc->SendMsg(id);
        }
    } else {
        std::cerr << "[DISPATCHER] [ERROR] Received unsupported message: " << id
                  << std::endl;
    }
}

}  // namespace cc_threads
