/*
 * @Descripttion:  头文件声明和定义单例及其对应函数
 * @Author: jev
 * @Date: 2026-02-19
 */

#pragma once

#include <cstdint>

// 声明和定义单例
class BadSingleton {
 public:
  static BadSingleton& badInstance() {
    // Static function in header gives each module its own singleton copy.
    static BadSingleton instance;
    return instance;
  }

  static std::uintptr_t badInstanceAddr() {
    return reinterpret_cast<std::uintptr_t>(&badInstance());
  }

  void setNum(int num) { num_ = num; }
  int getNum() const { return num_; }

 private:
  int num_ = 0;
};
