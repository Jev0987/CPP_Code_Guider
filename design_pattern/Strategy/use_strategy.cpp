/*
 * @Descripttion:
 * @Author: jev
 * @Date: 2025-08-17
 */

class TaxStrategy {
public:
    TaxStrategy() {};

    virtual ~TaxStrategy() {};

    virtual double Tax(const int num) = 0;
};

class CNTax : public TaxStrategy {
public:
    virtual double Tax(const int num) {
        // do Chinese calc tax
    }
};

class StrategyFactroy {
    // 抽象工厂
public:
    TaxStrategy* NewStrategy() {
        // 抽象工厂方法
    };
};

class USTax : public TaxStrategy {
public:
    virtual double Tax(const int num) {
        // do us calc tax
    }
};

class JPTax : public TaxStrategy {
public:
    virtual double Tax(const int num) {
        // do Japen calc tax
    }
};

class SalesOrder {
private:
    TaxStrategy* strategy;

public:
    SalesOrder(StrategyFactroy* strategyFactroy) {
        this->strategy = strategyFactroy->NewStrategy();
    }

    ~SalesOrder() { delete strategy; }

    double calcTax(int num) {
        double val = strategy->Tax(num);
        return val;
    }
};

int main(int argc, char** argv) { return 0; }
