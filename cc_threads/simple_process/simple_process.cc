#include "simple_process.h"

#include <algorithm>
#include <iostream>

namespace cc_threads {

SimpleProcess::SimpleProcess() : BaseThread() {
    for (uint32_t i = 10; i <= 20; ++i) {
        supported_msgs_.push_back(i);
    }
    for (uint32_t i = 50; i <= 60; ++i) {
        supported_msgs_.push_back(i);
    }
}

void SimpleProcess::Process(uint32_t id) {
    auto it = std::find(supported_msgs_.begin(), supported_msgs_.end(), id);
    if (it != supported_msgs_.end()) {
        std::cout << "[SIMPLE_PROCESS] [INFO] Processing message: " << id
                  << std::endl;
    } else {
        std::cerr << "[SIMPLE_PROCESS] [ERROR] Received unsupported message: "
                  << id << std::endl;
    }
}

}  // namespace cc_threads
