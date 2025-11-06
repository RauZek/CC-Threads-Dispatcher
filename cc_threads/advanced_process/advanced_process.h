#ifndef _ADVANCED_PROCESS_H_
#define _ADVANCED_PROCESS_H_

#include <cstdint>
#include <iostream>
#include <vector>

#include "base_thread.h"

namespace cc_threads {

class AdvancedProcess : public BaseThread {
 public:
  AdvancedProcess();
  ~AdvancedProcess() override = default;

  AdvancedProcess(const AdvancedProcess&) = delete;
  AdvancedProcess& operator=(const AdvancedProcess&) = delete;

 protected:
  void Process(uint32_t id) override;
};

extern "C" IBaseThread* Create() {
  return new AdvancedProcess();
}

}  // namespace cc_threads

#endif  // _ADVANCED_PROCESS_H_
