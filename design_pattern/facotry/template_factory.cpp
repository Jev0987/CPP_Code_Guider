/*
 * @Descripttion: 模板工厂
 * @Author: jev
 * @Date: 2025-11-25
 */
#include <iostream>
#include <string>

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

// 抽象模板工厂
template <typename AbstractType>  // 抽象类型
class TemplateFactory {
public:
    virtual ~TemplateFactory() = default;
    virtual AbstractType* createNode() = 0;
    virtual AbstractType* createState() = 0;
};

// 具体模板工厂
template <typename AbstractType, typename ConcreteType>  // 具体类型
class ConcreteTemplateFactory : public TemplateFactory<AbstractType> {
public:
    AbstractType* createNode() override { return new ConcreteType(); }
    AbstractType* createState() override { return new ConcreteType(); }
};

int main() {
    // ======== 利用模板创建不同抽象类的节点类型 ========

    // 控制节点
    ConcreteTemplateFactory<INode, ControlNode> controlNodeFactory;
    INode* node = controlNodeFactory.createNode();
    node->tick();
    delete node;

    // 控制状态
    ConcreteTemplateFactory<IState, ControlState> controlStateFactory;
    IState* state = controlStateFactory.createState();
    state->onTick();
    delete state;

    // 动作节点
    ConcreteTemplateFactory<INode, ActionNode> actionNodeFactory;
    INode* action_node = actionNodeFactory.createNode();
    action_node->tick();
    delete action_node;

    return 0;
}