#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    int copies;
    std::string author;

    static int validate(int count) {
        if (count < 0) throw std::invalid_argument("copies cannot be negative");
        return count;
    }

public:
    Book() : Book("Untitled", 0, "Unknown") {}
    explicit Book(const std::string& t) : Book(t, 1, "Unknown") {}
    Book(const std::string& t, int count) : Book(t, count, "Unknown") {}
    Book(const std::string& t, int count, const std::string& a)
        : title(t), copies(validate(count)), author(a) {}

    void print() const {
        std::cout << title << " | copies=" << copies << " | author=" << author << '\n';
    }
};

class ImplicitDemo {
public:
    ImplicitDemo(int) { std::cout << "ImplicitDemo constructed\n"; }
};

class ExplicitDemo {
public:
    explicit ExplicitDemo(int) { std::cout << "ExplicitDemo constructed\n"; }
};

int main() {
    Book empty;
    Book donated("The Alchemist");
    Book inventory("Clean Code", 4, "Robert C. Martin");
    empty.print();
    donated.print();
    inventory.print();

    try {
        Book invalid("Invalid", -2);
        invalid.print();
    } catch (const std::invalid_argument& e) {
        std::cout << "Rejected: " << e.what() << '\n';
    }

    ImplicitDemo a = 5; // allowed: converting constructor is not explicit
    (void)a;
    // ExplicitDemo b = 5; // intentionally fails: explicit constructor blocks copy-init
    ExplicitDemo c(5);
    (void)c;
    return 0;
}
