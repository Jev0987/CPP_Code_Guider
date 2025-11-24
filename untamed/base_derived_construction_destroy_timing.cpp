/*
 * @Descripttion: 基类子类的构造函数执行时机
 * @Author: Jev
 * @Date: 25-6-15
 */
#include <iostream>
#include <memory>
// 基类
class Base {
 public:
  Base() { std::cout << "Base::Base()" << std::endl; }

  ~Base() { std::cout << "Base::~Base()" << std::endl; }

  void print() { std::cout << "Base::print()" << std::endl; }
};

// 派生类
class Derived : public Base {
 public:
  Derived() : Base() { std::cout << "Derived::Derived()" << std::endl; }

  ~Derived() { std::cout << "Derived::~Derived()" << std::endl; }

  void print() { std::cout << "Derived::print()" << std::endl; }
};

void demo_create_destroy() {
  std::shared_ptr<Base> base = std::make_shared<Derived>();
  base->print();  // Base::print()

  std::cout << " ===================== " << std::endl;

  auto derived = std::make_shared<Derived>();
  derived->print();

  std::cout << " ===================== " << std::endl;
}

// Base::Base()
// Derived::Derived()
// Base::print()
//  =====================
// Base::Base()
// Derived::Derived()
// Derived::print()
//  =====================
// Derived::~Derived()
// Base::~Base()
// Derived::~Derived()
// Base::~Base()