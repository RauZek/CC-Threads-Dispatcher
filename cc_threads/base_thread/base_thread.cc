#include "base_thread.h"

#include <iostream>

namespace cc_threads {

BaseThread::BaseThread() {}

BaseThread::~BaseThread() {
    if (!stop_thread_.load()) {
        SendMsg(0);
    }

    if (thread_.joinable()) {
        thread_.join();
    }
}

void BaseThread::SendMsg(uint32_t id) {
    if (id == 0) {
        stop_thread_.store(true);
    }
    msg_queue_.Push(id);
}

std::vector<uint32_t>& BaseThread::GetSupportedMsg() { return supported_msgs_; }

void BaseThread::Loop() {
    while (true) {
        uint32_t msg = msg_queue_.WaitAndPop();

        if (msg == 0) {
            std::cout << "[Thread " << std::this_thread::get_id()
                      << "] Received the stop message. Exiting the loop..."
                      << std::endl;
            break;
        }

        Process(msg);
    }
}

void BaseThread::StartThread() {
    // Only start if not already running
    if (!thread_.joinable()) {
        thread_ = std::thread(&BaseThread::Loop, this);
    }
}

}  // namespace cc_threads
