#include "plugin_good_api.h"

#include "core_good_api.h"

extern "C" {

void pluginGoodSetNum(int num) { coreGoodSetNum(num); }

int pluginGoodGetNum() { return coreGoodGetNum(); }

std::uintptr_t pluginGoodAddr() { return coreGoodAddr(); }

}
