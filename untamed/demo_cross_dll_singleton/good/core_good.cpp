#include "core_good_api.h"

#include <cstdint>

namespace {
class GoodSingleton {
 public:
  void setNum(int num) { num_ = num; }
  int getNum() const { return num_; }

 private:
  int num_ = 0;
};

GoodSingleton& goodInstance() {
  static GoodSingleton instance;
  return instance;
}
}  // namespace

extern "C" {

void coreGoodSetNum(int num) { goodInstance().setNum(num); }

int coreGoodGetNum() { return goodInstance().getNum(); }

std::uintptr_t coreGoodAddr() { return reinterpret_cast<std::uintptr_t>(&goodInstance()); }

}
