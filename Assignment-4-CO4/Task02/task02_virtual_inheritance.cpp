#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(const std::string& n, int i, const std::string& p)
        : name(n), id(i), phone(p) {}
    virtual ~Person() = default;

    void showPerson() const {
        std::cout << name << " | ID: " << id << " | Phone: " << phone << '\n';
    }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(const std::string& n, int i, const std::string& p,
            const std::string& prog, double g)
        : Person(n, i, p), programme(prog), cgpa(g) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(const std::string& n, int i, const std::string& p,
          const std::string& dept, double s)
        : Person(n, i, p), department(dept), salary(s) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(const std::string& n, int i, const std::string& p,
                      const std::string& prog, double g,
                      const std::string& dept, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, g),
          Staff(n, i, p, dept, s) {}

    void display() const {
        showPerson();
        std::cout << "Programme: " << programme << ", CGPA: " << cgpa << '\n';
        std::cout << "Department: " << department << ", Salary: " << salary << '\n';
    }
};

class ResearchScholar : public Student {
private:
    double fellowship;

public:
    ResearchScholar(const std::string& n, int i, const std::string& p,
                    const std::string& prog, double g, double f)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowship(f) {}

    void display() const {
        showPerson();
        std::cout << "Programme: " << programme << ", CGPA: " << cgpa
                  << ", Fellowship: " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 1001, "9876543210",
                         "AI & DS", 8.7, "Computing", 45000);
    ResearchScholar scholar("Arun", 1002, "9876501234",
                            "Computer Science", 9.1, 15000);

    std::cout << "Teaching Assistant\n";
    ta.display();

    std::cout << "\nResearch Scholar\n";
    scholar.display();
    return 0;
}
