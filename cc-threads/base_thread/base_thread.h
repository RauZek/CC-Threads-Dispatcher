#ifndef __BASE_THREAD_H__
#define __BASE_THREAD_H__

#include <atomic>
#include <cstdint>
#include <thread>
#include <vector>

#include "ibase_thread.h"
#include "thread_safe_queue.h"

namespace cc_threads {

class BaseThread : public IBaseThread {
   public:
    BaseThread();
    virtual ~BaseThread();

    BaseThread(const BaseThread&) = delete;
    BaseThread& operator=(const BaseThread&) = delete;
    BaseThread(BaseThread&&) = delete;
    BaseThread& operator=(BaseThread&&) = delete;

    void SendMsg(uint32_t id) override;
    std::vector<uint32_t>& GetSupportedMsg() override;

   protected:
    virtual void Process(uint32_t id) = 0;

    void StartThread();
    std::vector<uint32_t> supported_msgs_;

   private:
    void Loop();

    std::thread thread_;
    utils::ThreadSafeQueue<uint32_t> msg_queue_;
    std::atomic<bool> stop_thread_{false};
};

}  // namespace cc_threads

#endif  // __BASE_THREAD_H__
