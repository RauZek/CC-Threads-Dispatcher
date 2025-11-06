#ifndef __IBASE_THREAD_H__
#define __IBASE_THREAD_H__

#include <cstdint>
#include <vector>

namespace cc_threads {

class IBaseThread {
   public:
    virtual ~IBaseThread() = default;
    virtual void SendMsg(uint32_t id) = 0;
    virtual const std::vector<uint32_t>& GetSupportedMsg() = 0;
};

}  // namespace cc_threads

#endif  // __IBASE_THREAD_H__
