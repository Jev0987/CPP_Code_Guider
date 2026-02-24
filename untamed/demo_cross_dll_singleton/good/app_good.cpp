#include <iostream>

#include "core_good_api.h"
#include "plugin_good_api.h"

int main() {
  std::cout << "[good] app(core) addr:      0x" << std::hex << coreGoodAddr() << std::dec << "\n";
  std::cout << "[good] plugin(core) addr:   0x" << std::hex << pluginGoodAddr() << std::dec
            << "\n";

  coreGoodSetNum(42);
  std::cout << "[good] app set 42, plugin sees: " << pluginGoodGetNum() << "\n";

  pluginGoodSetNum(99);
  std::cout << "[good] plugin set 99, app sees: " << coreGoodGetNum() << "\n";

  const bool same_addr = (coreGoodAddr() == pluginGoodAddr());
  std::cout << "[good] same instance? " << (same_addr ? "YES" : "NO") << "\n";
  return 0;
}
