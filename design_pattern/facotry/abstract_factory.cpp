/*
 * @Descripttion: 抽象工厂 -> 可以提供同节点类型的不同对象
 * @Author: jev
 * @Date: 2025-11-25
 */
#include <iostream>
#include <string>

// 抽象节点
class INode {
public:
    virtual ~INode() = default;
    virtual void tick() = 0;
};

// 抽象状态
class IState {
public:
    virtual ~IState() = default;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onTick() = 0;
};

// 控制节点
class ControlNode : public INode {
public:
    void tick() override { std::cout << "ControlNode tick" << std::endl; }
};

// 控制状态
class ControlState : public IState {
public:
    void onEnter() override { std::cout << "ControlState onEnter" << std::endl; }
    void onExit() override { std::cout << "ControlState onExit" << std::endl; }
    void onTick() override { std::cout << "ControlState onTick" << std::endl; }
};

// 动作节点
class ActionNode : public INode {
public:
    void tick() override { std::cout << "ActionNode tick" << std::endl; }
};

// 动作状态
class ActionState : public IState {
public:
    void onEnter() override { std::cout << "ActionState onEnter" << std::endl; }
    void onExit() override { std::cout << "ActionState onExit" << std::endl; }
    void onTick() override { std::cout << "ActionState onTick" << std::endl; }
};

class ConditionNode : public INode {
public:
    void tick() override { std::cout << "ConditionNode tick" << std::endl; }
};

// 条件状态
class ConditionState : public IState {
public:
    void onEnter() override { std::cout << "ConditionState onEnter" << std::endl; }
    void onExit() override { std::cout << "ConditionState onExit" << std::endl; }
    void onTick() override { std::cout << "ConditionState onTick" << std::endl; }
};

// 抽象工厂
class INodeFactory {
public:
    virtual ~INodeFactory() = default;
    virtual INode* createNode() = 0;
    virtual IState* createState() = 0;
};

// 控制节点工厂
class ControlNodeFactory : public INodeFactory {
public:
    INode* createNode() override { return new ControlNode(); }
    IState* createState() override { return new ControlState(); }
};

// 动作节点工厂
class ActionNodeFactory : public INodeFactory {
public:
    INode* createNode() override { return new ActionNode(); }
    IState* createState() override { return new ActionState(); }
};

// 条件节点工厂
class ConditionNodeFactory : public INodeFactory {
public:
    INode* createNode() override { return new ConditionNode(); }
    IState* createState() override { return new ConditionState(); }
};

int main() {
    ControlNodeFactory controlNodeFactory;
    ActionNodeFactory actionNodeFactory;
    ConditionNodeFactory conditionNodeFactory;
    INode* node = controlNodeFactory.createNode();
    INode* node2 = actionNodeFactory.createNode();
    INode* node3 = conditionNodeFactory.createNode();
    IState* state = controlNodeFactory.createState();
    IState* state2 = actionNodeFactory.createState();
    IState* state3 = conditionNodeFactory.createState();
    node->tick();
    node2->tick();
    node3->tick();
    state->onTick();
    state2->onTick();
    state3->onTick();

    delete node;
    delete node2;
    delete node3;
    delete state;
    delete state2;
    delete state3;
    return 0;
}