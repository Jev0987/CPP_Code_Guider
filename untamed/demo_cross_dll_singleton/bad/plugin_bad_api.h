#pragma once

#include <cstdint>

extern "C" {
void pluginBadSetNum(int num);
int pluginBadGetNum();
std::uintptr_t pluginBadAddr();
}
