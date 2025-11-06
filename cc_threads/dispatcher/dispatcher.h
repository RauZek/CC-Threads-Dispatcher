#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "base_thread.h"

namespace cc_threads {

using CreateProcessFunc = IBaseThread* (*)();

class Dispatcher : public BaseThread {
   public:
    Dispatcher();
    ~Dispatcher() override;

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

   protected:
    void Process(uint32_t id) override;

   private:
    void LoadProcessLib(const std::string& lib_path,
                        const std::string& create_func_name);

    std::vector<void*> lib_handles_;
    std::vector<std::unique_ptr<IBaseThread>> processes_;
    std::map<uint32_t, std::vector<IBaseThread*>> msg_routing_table_;
};

}  // namespace cc_threads

#endif  // __DISPATCHER_H__
