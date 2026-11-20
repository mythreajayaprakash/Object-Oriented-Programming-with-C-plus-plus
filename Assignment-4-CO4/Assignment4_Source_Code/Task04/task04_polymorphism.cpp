#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const {
        return 3.5;
    }
    virtual ~Account() {
        std::cout << "Account destructor\n";
    }
};

class SeniorAccount : public Account {
private:
    double* history;

public:
    SeniorAccount() : history(new double[100]{}) {}

    double rate() const override {
        return 4.0;
    }

    ~SeniorAccount() override {
        delete[] history;
        std::cout << "SeniorAccount destructor\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    for (const auto& account : accounts) {
        std::cout << account->rate() << '\n';
    }

    // Demonstrate virtual dispatch through a base-class pointer.
    SeniorAccount senior;
    Account* ptr = &senior;
    std::cout << "Pointer call: " << ptr->rate() << '\n';

    // Output prediction exercise from the assignment:
    // p->rate() calls the non-sliced object's virtual function in this repaired design.
    // The assignment's separate sample has a non-virtual rate() and a virtual vrate().
    return 0;
}
