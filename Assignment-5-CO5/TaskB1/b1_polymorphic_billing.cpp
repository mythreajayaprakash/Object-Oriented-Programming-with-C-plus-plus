#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(std::string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const { return "Bill"; }
    void print() const { std::cout << type() << ' ' << patient << ": " << total() << '\n'; }
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(const std::string& p, double c, double t) : Bill(p), consultation(c), tests(t) {
        if (c < 0 || t < 0) throw std::invalid_argument("negative charge");
    }
    double total() const override { return consultation + tests; }
    std::string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(const std::string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {
        if (d < 0 || rate < 0 || s < 0) throw std::invalid_argument("negative inpatient charge");
    }
    double total() const override { return days * perDay + surgery; }
    std::string type() const override { return "IP"; }
};
class DayCare : public Bill {
    double package;
public:
    DayCare(const std::string& p, double v) : Bill(p), package(v) {
        if (v < 0) throw std::invalid_argument("negative package");
    }
    double total() const override { return package; }
    std::string type() const override { return "DayCare"; }
};
class Emergency : public Bill {
    double base, perHour; int hours;
public:
    Emergency(const std::string& p, double b, double rate, int h)
        : Bill(p), base(b), perHour(rate), hours(h) {
        if (b < 0 || rate < 0 || h < 0) throw std::invalid_argument("negative emergency charge");
    }
    double total() const override { return base + perHour * hours; }
    std::string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override { return bill.total(); }
};
class Insurance : public Payer {
    double limit, copayPercent;
public:
    Insurance(double l, double c) : limit(l), copayPercent(c) {
        if (l < 0 || c < 0 || c > 100) throw std::invalid_argument("invalid insurance policy");
    }
    double amountCovered(const Bill& bill) const override {
        const double eligible = bill.total() * (1.0 - copayPercent / 100.0);
        return eligible < limit ? eligible : limit;
    }
};
class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "OP") return 1500;
        if (bill.type() == "IP") return 30000;
        if (bill.type() == "DayCare") return 12000;
        if (bill.type() == "Emergency") return 10000;
        throw std::runtime_error("unknown package");
    }
};

int main() {
    std::vector<std::unique_ptr<Bill>> bills;
    bills.push_back(std::make_unique<OutPatient>("Ravi", 500, 1200));
    bills.push_back(std::make_unique<InPatient>("Meena", 3, 2500, 40000));
    bills.push_back(std::make_unique<DayCare>("Asha", 18000));
    bills.push_back(std::make_unique<Emergency>("Kiran", 2000, 500, 4));

    SelfPay self;
    Insurance insurance(50000, 20);
    GovernmentScheme scheme;
    double total = 0;
    for (const auto& b : bills) {
        b->print();
        total += b->total();
        std::cout << "  self=" << self.amountCovered(*b)
                  << " insurance=" << insurance.amountCovered(*b)
                  << " scheme=" << scheme.amountCovered(*b) << '\n';
    }
    std::cout << "Day total " << total << '\n';
}
