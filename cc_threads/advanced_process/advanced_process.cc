#include "advanced_process.h"

#include <algorithm>
#include <iostream>

namespace cc_threads {

AdvancedProcess::AdvancedProcess() : BaseThread() {
    for (uint32_t i = 30; i <= 40; ++i) {
        supported_msgs_.push_back(i);
    }
    for (uint32_t i = 50; i <= 60; ++i) {
        supported_msgs_.push_back(i);
    }
    StartThread();
}

void AdvancedProcess::Process(uint32_t id) {
    auto it = std::find(supported_msgs_.begin(), supported_msgs_.end(), id);
    if (it != supported_msgs_.end()) {
        std::cout << "[ADVANCED_PROCESS] [INFO] Processing message: " << id
                  << std::endl;
    } else {
        std::cerr << "[ADVANCED_PROCESS] [ERROR] Received unsupported message: "
                  << id << std::endl;
    }
}

}  // namespace cc_threads
