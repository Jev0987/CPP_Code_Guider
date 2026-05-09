#include <iostream>
#include <memory>

struct LoanData {
    explicit LoanData(int id) : id(id) {
        std::cout << "construct LoanData: " << this->id << '\n';
    }

    ~LoanData() {
        std::cout << "destroy LoanData: " << id << '\n';
    }

    void print() const {
        std::cout << "LoanData(" << id << ") at " << this << '\n';
    }

    int id;
};

class BadBorrower {
   public:
    void borrow(LoanData* data) {
        // 这个 shared_ptr 不负责释放对象，只是把外部裸指针包装起来。
        // 问题：shared_ptr 的引用计数只能管理自己的控制块，无法知道外部对象已经被 delete。
        data_ = std::shared_ptr<LoanData>(data, [](LoanData*) {});
    }

    void use() const {
        std::cout << "BadBorrower still thinks ptr is valid: ";
        data_->print();
    }

   private:
    std::shared_ptr<LoanData> data_;
};

class GoodBorrower {
   public:
    void borrow(const std::shared_ptr<LoanData>& data) {
        // weak_ptr 表示只观察、不拥有；真正使用前必须 lock。
        data_ = data;
    }

    void use() const {
        auto data = data_.lock();
        if (!data) {
            std::cout << "GoodBorrower: object expired, stop using it\n";
            return;
        }

        std::cout << "GoodBorrower got a valid object: ";
        data->print();
    }

   private:
    std::weak_ptr<LoanData> data_;
};

void demo_bad(bool really_use_dangling_ptr) {
    std::cout << "\n[bad demo]\n";

    auto* owner = new LoanData(1);
    BadBorrower borrower;
    borrower.borrow(owner);

    delete owner;
    owner = nullptr;

    std::cout << "external owner deleted the object\n";
    if (really_use_dangling_ptr) {
        std::cout << "next line uses a dangling pointer, this is undefined behavior\n";
        borrower.use();
    } else {
        std::cout << "skip dangling pointer access. Run with --danger to trigger it.\n";
    }
}

void demo_good() {
    std::cout << "\n[good demo]\n";

    GoodBorrower borrower;
    {
        auto owner = std::make_shared<LoanData>(2);
        borrower.borrow(owner);
        borrower.use();
    }

    std::cout << "shared owner released the object\n";
    borrower.use();
}

int main(int argc, char* argv[]) {
    const bool danger = argc > 1 && std::string(argv[1]) == "--danger";

    demo_bad(danger);
    demo_good();

    return 0;
}
