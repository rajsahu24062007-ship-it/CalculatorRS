#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

class VaibhavScientificCalc {
private:
    const double PI = 3.14159265358979323846;

    double toRadians(double deg) {
        return deg * (PI / 180.0);
    }

public:
    // Trigonometry (Degree mode)
    double sinDeg(double x) { return std::sin(toRadians(x)); }
    double cosDeg(double x) { return std::cos(toRadians(x)); }
    double tanDeg(double x) { return std::tan(toRadians(x)); }
    double cosecDeg(double x) { return 1.0 / sinDeg(x); }
    double secDeg(double x) { return 1.0 / cosDeg(x); }
    double cotDeg(double x) { return 1.0 / tanDeg(x); }

    // Logarithms
    double naturalLog(double x) { return std::log(x); }
    double log10(double x) { return std::log10(x); }
    double log2(double x) { return std::log2(x); }

    // Powers & Roots
    double square(double x) { return x * x; }
    double power(double base, double exp) { return std::pow(base, exp); }
    double squareRoot(double x) { return std::sqrt(x); }
    double reciprocal(double x) { return 1.0 / x; }

    // Information Theory & Entropy
    double binaryEntropy(double p) {
        if (p < 0.0 || p > 1.0) throw std::out_of_range("p must be in [0, 1]");
        if (p == 0.0 || p == 1.0) return 0.0;
        return -(p * std::log2(p) + (1.0 - p) * std::log2(1.0 - p));
    }
};

int main() {
    VaibhavScientificCalc calc;
    std::cout << "====================================================\n";
    std::cout << "  Vaibhav's Calculator (Information Theory Engine)  \n";
    std::cout << "====================================================\n";
    std::cout << "sin(30 deg)   = " << calc.sinDeg(30) << "\n";
    std::cout << "log2(8)       = " << calc.log2(8) << "\n";
    std::cout << "sqrt(49)      = " << calc.squareRoot(49) << "\n";
    std::cout << "H(p=0.5)      = " << calc.binaryEntropy(0.5) << " bits\n";
    return 0;
}