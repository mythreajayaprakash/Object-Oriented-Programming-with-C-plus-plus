#include <iomanip>
#include <iostream>
#include <string>

class Cart {
private:
    std::string items[10];
    double prices[10]{};
    int n = 0;
    double discount = 0.0;

public:
    Cart& add(const std::string& item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }

    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    double total() const {
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            sum += prices[i];
        }
        return sum * (100.0 - discount) / 100.0;
    }

    void show() const {
        for (int i = 0; i < n; ++i) {
            std::cout << items[i] << ": " << prices[i] << '\n';
        }
        std::cout << "Total: " << total() << '\n';
    }
};

int main() {
    // (a) Direct object access
    Cart direct;
    direct.add("Bread", 50);

    // (b) Pointer to an existing object; use ->
    Cart* pointer = &direct;
    pointer->add("Milk", 40);

    // (c) Reference access
    Cart& reference = direct;
    reference.add("Eggs", 60);

    // (d) Dynamically allocated object; pair new with delete
    Cart* dynamicCart = new Cart;
    dynamicCart->add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << std::fixed << std::setprecision(2)
              << "Dynamic cart total: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    // Exact TODO program from the assignment; expected total is 324.00.
    Cart c;
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* p = &c;
    p->add("Oil", 180);
    std::cout << "Assignment output: " << std::fixed
              << std::setprecision(2) << p->total() << '\n';

    // Array of pointers: find the cart with the highest total.
    Cart c1, c2, c3;
    c1.add("Item A", 100);
    c2.add("Item B", 250);
    c3.add("Item C", 175);
    Cart* carts[] = {&c1, &c2, &c3};

    Cart* highest = carts[0];
    for (Cart* current : carts) {
        if (current->total() > highest->total()) {
            highest = current;
        }
    }
    std::cout << "Highest cart total: " << highest->total() << '\n';
    return 0;
}
