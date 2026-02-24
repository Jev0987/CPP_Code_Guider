#pragma once

#include <cstdint>

extern "C" {
void coreGoodSetNum(int num);
int coreGoodGetNum();
std::uintptr_t coreGoodAddr();
}
