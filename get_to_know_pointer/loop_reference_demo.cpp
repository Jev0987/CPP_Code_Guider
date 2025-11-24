/*
 * @Descripttion: shared_ptr 可能会导致的循环引用的问题
 * @Author: zhanjiewen
 * @Date: 2025-10-17
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-11-24
 */
#include <iostream>
#include <memory>

struct LoopRefNode {
  int val;
  std::shared_ptr<LoopRefNode> next;  // 危险, 小心循环引用的问题
  LoopRefNode(int value) : val(value) {}
};

struct SafeNode {
  int val;
  std::weak_ptr<SafeNode> next;
  SafeNode(int value) : val(value) {}
};

void loop_refernce() {
  auto n1 = std::make_shared<LoopRefNode>(1);
  auto n2 = std::make_shared<LoopRefNode>(2);
  n1->next = n2;
  n2->next = n1;  // 内存泄漏

  auto n3 = std::make_shared<SafeNode>(3);
  auto n4 = std::make_shared<SafeNode>(4);
  n3->next = n4;
  n4->next = n3;  // 无内存泄漏
}

int main() {
  loop_refernce();
  return 0;
}
