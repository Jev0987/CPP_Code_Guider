/*
 * @Descripttion: 简单工厂
 * @Author: jev
 * @Date: 2025-11-25
 */

#include <iostream>
#include <string>

enum class NodeType {
    CONTROL,
    ACTION,
    CONDITION,
};

// 抽象节点
class INode {
public:
    virtual ~INode() = default;
    virtual void tick() = 0;
    virtual NodeType getType() = 0;
};

// 控制节点
class ControlNode : public INode {
public:
    void tick() override { std::cout << "ControlNode tick" << std::endl; }
    NodeType getType() override { return NodeType::CONTROL; }
};

// 动作节点
class ActionNode : public INode {
public:
    void tick() override { std::cout << "ActionNode tick" << std::endl; }
    NodeType getType() override { return NodeType::ACTION; }
};

// 条件节点
class ConditionNode : public INode {
public:
    void tick() override { std::cout << "ConditionNode tick" << std::endl; }
    NodeType getType() override { return NodeType::CONDITION; }
};

// 简单工厂
class NodeFactory {
public:
    static INode* createNode(NodeType type) {
        // 如果有新节点类型出现，还需要修改函数内的switch判断条件
        switch (type) {
        case NodeType::CONTROL:
            return new ControlNode();
        case NodeType::ACTION:
            return new ActionNode();
        case NodeType::CONDITION:
            return new ConditionNode();
        default:
            return nullptr;
        }
    }
};

int main() {
    NodeFactory factory;
    INode* node = factory.createNode(NodeType::CONTROL);
    if (node) {
        node->tick();
        delete node;
    }
    return 0;
}
