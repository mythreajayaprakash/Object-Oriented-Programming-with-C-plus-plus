#include <chrono>
#include <iostream>
#include <string>
#include <utility>

class Prescription {
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new std::string[count] : nullptr) {}

    // TODO 1 completed: allocate independent storage and copy each element.
    Prescription(const Prescription& other)
        : n(other.n), medicines(other.n > 0 ? new std::string[other.n] : nullptr) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
    }

    // TODO 2 completed: copy-and-swap style assignment with self-assignment guard.
    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this;
        std::string* fresh = other.n > 0 ? new std::string[other.n] : nullptr;
        for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
        delete[] medicines;
        medicines = fresh;
        n = other.n;
        return *this;
    }

    ~Prescription() {
        delete[] medicines; // TODO 3 completed
    }

    void set(int i, const std::string& medicine) {
        if (i < 0 || i >= n) throw std::out_of_range("medicine index");
        medicines[i] = medicine;
    }

    std::string get(int i) const {
        if (i < 0 || i >= n) throw std::out_of_range("medicine index");
        return medicines[i];
    }

    int size() const { return n; }
};

void takeByValue(Prescription p) { (void)p.get(0); }
void takeByConstReference(const Prescription& p) { (void)p.get(0); }

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';

    r = r; // self-assignment test
    takeByValue(p);
    takeByConstReference(p);

    for (int count : {10, 1000, 100000}) {
        Prescription large(count);
        for (int i = 0; i < count; ++i) large.set(i, "Medicine");
        const auto start = std::chrono::steady_clock::now();
        Prescription copy = large;
        const auto stop = std::chrono::steady_clock::now();
        const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        std::cout << "Copied " << count << " medicines in " << ns << " ns (record repeated runs)\n";
        (void)copy;
    }
    return 0;
}
