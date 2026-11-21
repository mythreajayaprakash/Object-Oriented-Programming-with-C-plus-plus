#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double real) : re(real), im(0) {}
    Complex(double real, double imag) : re(real), im(imag) {}

    Complex operator+(const Complex& z) const { return {re + z.re, im + z.im}; }
    Complex operator-(const Complex& z) const { return {re - z.re, im - z.im}; }
    Complex operator*(const Complex& z) const {
        return {re * z.re - im * z.im, re * z.im + im * z.re};
    }
    Complex operator/(const Complex& z) const {
        const double denominator = z.re * z.re + z.im * z.im;
        if (denominator == 0.0) throw std::domain_error("division by zero impedance");
        return {(re * z.re + im * z.im) / denominator,
                (im * z.re - re * z.im) / denominator};
    }
    bool operator==(const Complex& z) const {
        constexpr double EPS = 1e-9;
        return std::abs(re - z.re) < EPS && std::abs(im - z.im) < EPS;
    }
    double magnitude() const { return std::sqrt(re * re + im * im); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& z) {
        out << z.re << (z.im < 0 ? " - j" : " + j") << std::abs(z.im);
        return out;
    }
};

int main() {
    const double omega = 100.0;
    const double L = 0.01;
    const double C = 0.001;

    Complex resistor(10.0, 0.0);
    Complex inductor(0.0, omega * L);
    Complex capacitor(0.0, -1.0 / (omega * C));

    Complex series = resistor + inductor + capacitor;
    std::cout << "Series impedance: " << series
              << " |Z|=" << series.magnitude() << '\n';

    Complex z1(10.0, 5.0), z2(20.0, -2.0);
    Complex parallel = (z1 * z2) / (z1 + z2);
    std::cout << "Parallel impedance: " << parallel
              << " |Z|=" << parallel.magnitude() << '\n';

    try {
        Complex invalid = z1 / Complex(0.0, 0.0);
        std::cout << invalid << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Safe error: " << e.what() << '\n';
    }
    return 0;
}
