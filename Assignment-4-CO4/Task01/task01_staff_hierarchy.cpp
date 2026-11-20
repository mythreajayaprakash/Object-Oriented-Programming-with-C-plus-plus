#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;
    double basic;

public:
    Staff(const std::string& n, int i, double b)
        : name(n), id(i), basic(b) {}
    virtual double pay() const = 0;
    virtual void display() const {
        std::cout << name << " (" << id << ") - Pay: " << pay() << '\n';
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
private:
    double research;

public:
    Professor(const std::string& n, int i, double b, double r)
        : Staff(n, i, b), research(r) {}

    double pay() const override {
        constexpr double DA_RATE = 0.42;
        return basic + basic * DA_RATE + research;
    }
};

class LabAssistant : public Staff {
public:
    LabAssistant(const std::string& n, int i, double b)
        : Staff(n, i, b) {}

    double pay() const override {
        constexpr double DA_RATE = 0.42;
        return basic + basic * DA_RATE;
    }
};

class GuestFaculty : public Staff {
private:
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& n, int i, double h, double r)
        : Staff(n, i, 0.0), hours(h), rate(r) {}

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Asha", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Meena", 103, 40, 1000));

    for (const auto& person : staff) {
        person->display();
    }
    return 0;
}
