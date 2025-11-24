/*
 * @Descripttion: 回顾一下 指针的使用
 * @Author: jev
 * @version:
 * @Date: 2025-03-16
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-11-24
 */
#include <iostream>

// 定义一个节点
struct Node {
    int data;
    Node* next;
};

// 释放节点
bool free_node(Node* node) {
    if (node == nullptr) return false;

    Node* cur = node;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
    return true;
}

// 修改节点数据
bool change_node_data(Node* node) {
    if (node == nullptr) return false;

    node->data = 996;

    return true;
}

// 通过地址创建节点数据
bool create_node_data_by_addr(Node** node) {
    Node* new_node = new Node();
    new_node->data = 456;
    new_node->next = nullptr;

    *node = new_node;
    return true;
}

void demo_review_ptr_use() {
    std::cout << __func__ << std::endl;
    // std::shared_ptr<Node> node = std::make_shared<Node>();  //
    // 使用智能指针，就不用手动释放内存了
    Node* node = new Node();
    node->data = 321;
    node->next = nullptr;

    std::cout << "node data: " << node->data << std::endl;

    change_node_data(node);

    std::cout << "node data: " << node->data << std::endl;

    free_node(node);

    Node* new_node = nullptr;
    create_node_data_by_addr(&new_node);

    std::cout << "new_node data: " << new_node->data << std::endl;
}