#pragma once

#include <cstdint>

extern "C" {
void pluginGoodSetNum(int num);
int pluginGoodGetNum();
std::uintptr_t pluginGoodAddr();
}
