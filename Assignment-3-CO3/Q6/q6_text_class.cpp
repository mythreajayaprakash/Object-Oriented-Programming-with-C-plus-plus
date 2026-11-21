#include <cstring>
#include <iostream>
#include <stdexcept>

class Text {
    char* data;
public:
    explicit Text(const char* s = "") {
        const std::size_t n = std::strlen(s);
        data = new char[n + 1];
        std::memcpy(data, s, n + 1);
    }
    Text(const Text& other) {
        const std::size_t n = std::strlen(other.data);
        data = new char[n + 1];
        std::memcpy(data, other.data, n + 1);
    }
    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        const std::size_t n = std::strlen(other.data);
        char* fresh = new char[n + 1];
        std::memcpy(fresh, other.data, n + 1);
        delete[] data;
        data = fresh;
        return *this;
    }
    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        const std::size_t a = std::strlen(data), b = std::strlen(other.data);
        char* joined = new char[a + b + 1];
        std::memcpy(joined, data, a);
        std::memcpy(joined + a, other.data, b + 1);
        Text result(joined);
        delete[] joined;
        return result;
    }
    bool operator==(const Text& other) const { return std::strcmp(data, other.data) == 0; }
    bool operator!=(const Text& other) const { return !(*this == other); }
    friend std::ostream& operator<<(std::ostream& out, const Text& value) {
        return out << value.data;
    }
};

int main() {
    Text a("Hello "), b("World"), empty;
    Text c = a + b;
    std::cout << c << " | empty=[" << empty << "]\n";
    a = a; // self-assignment
    Text longText("A longer SMS message used to exercise dynamic allocation.");
    Text copy = longText;
    copy = c;
    std::cout << "copy=" << copy << " equal=" << std::boolalpha << (copy == c)
              << " notEqual=" << (copy != b) << '\n';
    return 0;
}
