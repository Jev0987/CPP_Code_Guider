/*
 * @Descripttion: 没有使用策略模式的情况
 * @Author: jev
 * @Date: 2025-08-17
 */

enum TaxBase { CN_Tax, US_Tax, JP_Tax };

class SalesOrder {
    TaxBase tax;

public:
    void setTaxType(TaxBase cur_tax) { tax = cur_tax; }

    double calcTax() {
        // ...

        if (tax == CN_Tax) {
            // ...
        } else if (tax == US_Tax) {
            // ...
        } else if (tax == JP_Tax) {
            // ...
        }  // 如果你要加新的方式，就得不断从后面补充
    }
};

int main(int argc, char** argv) {
    SalesOrder calc;

    calc.setTaxType(CN_Tax);

    double num = calc.calcTax();

    return 0;
}