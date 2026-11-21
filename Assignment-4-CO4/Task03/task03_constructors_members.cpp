#include <iostream>
#include <string>

class Address {
private:
    std::string city;
    int pin;

public:
    Address(const std::string& c, int p) : city(c), pin(p) {
        std::cout << "Address constructed\n";
    }
    ~Address() { std::cout << "Address destroyed\n"; }

    std::string str() const {
        return city + "-" + std::to_string(pin);
    }
};

class Person {
protected:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Person constructed\n";
    }
    virtual ~Person() { std::cout << "Person destroyed\n"; }
};

class Student : public Person {
private:
    long long regNo;
    Address home;

public:
    Student(const std::string& n, int a, long long reg,
            const std::string& city, int pin)
        : Person(n, a), regNo(reg), home(city, pin) {
        std::cout << "Student constructed\n";
    }

    ~Student() override { std::cout << "Student destroyed\n"; }

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") "
                  << home.str() << '\n';
    }
};

class Course {
private:
    std::string title;

public:
    explicit Course(const std::string& t) : title(t) {
        std::cout << "Course constructed: " << title << '\n';
    }
    ~Course() { std::cout << "Course destroyed: " << title << '\n'; }
};

class EnrolledStudent : public Person {
private:
    Course course;

public:
    EnrolledStudent(const std::string& n, int a, const std::string& c)
        : Person(n, a), course(c) {
        std::cout << "EnrolledStudent constructed\n";
    }
    ~EnrolledStudent() override {
        std::cout << "EnrolledStudent destroyed\n";
    }
};

struct Engine {
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};

struct Vehicle {
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle "; }
};

struct Car : Vehicle {
    Engine e;
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

int main() {
    std::cout << "Complete-the-code constructor:\n";
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();

    std::cout << "\nConstruction/destruction order:\n";
    {
        Car c;
        std::cout << "| ";
    }
    std::cout << '\n';

    std::cout << "\nMember class example:\n";
    {
        EnrolledStudent es("Nila", 20, "Object Oriented Programming");
    }
    return 0;
}
