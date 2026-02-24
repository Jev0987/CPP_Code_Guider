#include "plugin_bad_api.h"
#include "singleton_bad.h"

extern "C" {

void pluginBadSetNum(int num) { BadSingleton::badInstance().setNum(num); }

int pluginBadGetNum() { return BadSingleton::badInstance().getNum(); }

std::uintptr_t pluginBadAddr() { return BadSingleton::badInstanceAddr(); }
}
