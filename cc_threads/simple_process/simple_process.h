#ifndef __SIMPLE_PROCESS_H__
#define __SIMPLE_PROCESS_H__

#include <cstdint>
#include <iostream>
#include <vector>

#include "base_thread.h"

namespace cc_threads {

class SimpleProcess : public BaseThread {
 public:
  SimpleProcess();
  ~SimpleProcess() override = default;

  SimpleProcess(const SimpleProcess&) = delete;
  SimpleProcess& operator=(const SimpleProcess&) = delete;

 protected:
  void Process(uint32_t id) override;
};

extern "C" IBaseThread* Create() {
  return new SimpleProcess();
}

}  // namespace cc_threads

#endif  // __SIMPLE_PROCESS_H__
