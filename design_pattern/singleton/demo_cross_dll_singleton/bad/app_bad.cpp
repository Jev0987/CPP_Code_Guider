#include <iostream>

#include "plugin_bad_api.h"
#include "singleton_bad.h"

int main() {

  // 直接使用单例
  std::cout << "[bad] app instance addr:    0x" << std::hex << badInstanceAddr() << std::dec
            << "\n";
  // 外部使用单例
  std::cout << "[bad] plugin instance addr: 0x" << std::hex << pluginBadAddr() << std::dec
            << "\n";

  badInstance().setNum(42);
  std::cout << "[bad] app set 42, plugin sees: " << pluginBadGetNum() << "\n";

  pluginBadSetNum(99);
  std::cout << "[bad] plugin set 99, app sees: " << badInstance().getNum() << "\n";

  const bool same_addr = (badInstanceAddr() == pluginBadAddr());
  std::cout << "[bad] same instance? " << (same_addr ? "YES" : "NO") << "\n";
  return 0;
}
