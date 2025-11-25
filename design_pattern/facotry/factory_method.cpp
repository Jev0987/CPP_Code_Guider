/*
 * @Descripttion: 工厂方法
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

// 抽象工厂 -> 通过抽象工厂优化简单工厂里需要在函数内增加节点类型的问题
class INodeFactory {
public:
    virtual ~INodeFactory() = default;
    virtual INode* createNode(NodeType type) = 0;
};

// 控制节点工厂
class ControlNodeFactory : public INodeFactory {
public:
    INode* createNode(NodeType type) override { return new ControlNode(); }
};

// 动作节点工厂
class ActionNodeFactory : public INodeFactory {
public:
    INode* createNode(NodeType type) override { return new ActionNode(); }
};

// 条件节点工厂
class ConditionNodeFactory : public INodeFactory {
public:
    INode* createNode(NodeType type) override { return new ConditionNode(); }
};

int main() {
    ControlNodeFactory controlNodeFactory;
    ActionNodeFactory actionNodeFactory;
    ConditionNodeFactory conditionNodeFactory;
    INode* node = controlNodeFactory.createNode(NodeType::CONTROL);
    INode* node2 = actionNodeFactory.createNode(NodeType::ACTION);
    INode* node3 = conditionNodeFactory.createNode(NodeType::CONDITION);
    if (node) {
        node->tick();
        delete node;
    }
    if (node2) {
        node2->tick();
        delete node2;
    }
    if (node3) {
        node3->tick();
        delete node3;
    }
    return 0;
}