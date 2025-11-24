/*
 * @Descripttion: 依赖注入demo
 * @Author: jev
 * @version:
 * @Date: 2025-11-03
 * @LastEditors: jev
 * @LastEditTime: 2025-11-03
 */
#include <iostream>

class Engine {
public:
    virtual ~Engine() = default;
    virtual void start() = 0;
};

class GasolineEngine : public Engine {
public:
    void start() override { std::cout << "gasoline engine start." << std::endl; }
};

class Car {
public:
    virtual void start() = 0;
    virtual ~Car() = default;
};

class Car_1 : Car {
public:
    // 构造函数注入
    Car_1(Engine* engine)
        : engine_(engine) {}
    ~Car_1() {
        if (engine_ != nullptr) { delete engine_; }
    }

    void start() override {
        if (engine_) { engine_->start(); }
    }

private:
    Engine* engine_;
};

class Car_2 : public Car {
public:
    // setter 方法注入
    void setEngine(Engine* engine) {
        if (engine_ != nullptr) { delete engine_; }
        engine_ = engine;
    }

    ~Car_2() {
        if (engine_ != nullptr) { delete engine_; }
    }

    void start() override {
        if (engine_) { engine_->start(); }
    }

private:
    Engine* engine_ = nullptr;
};

class EngineInjectable {
public:
    virtual ~EngineInjectable() = default;
    virtual void injectEngine(Engine* engine) = 0;
};

class Car_3
    : public EngineInjectable
    , Car {
public:
    // 接口注入
    void injectEngine(Engine* engine) override {
        if (engine_ != nullptr) { delete engine_; }
        engine_ = engine;
    }

    ~Car_3() {
        if (engine_ != nullptr) { delete engine_; }
    }

    void start() override {
        if (engine_) { engine_->start(); }
    }

private:
    Engine* engine_ = nullptr;
};