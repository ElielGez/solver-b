#include <complex>
#include <iostream>
using namespace std;

namespace solver {
class RealVariable {
public:
    double m_x2, m_x, m_c;

    RealVariable() : m_x2(0), m_x(1), m_c(0){};
    RealVariable(double x2, double x, double c) : m_x2(x2), m_x(x), m_c(c){};

    RealVariable &operator*(double coe) const;
    RealVariable &operator*(const RealVariable &other) const;
    friend RealVariable &operator*(double coe, const RealVariable &other);

    RealVariable &operator+(double coe);
    RealVariable &operator+(const RealVariable &other);
    friend RealVariable &operator+(double coe, const RealVariable &other);

    RealVariable &operator-(double coe);
    RealVariable &operator-(const RealVariable &other);
    friend RealVariable &operator-(double coe, const RealVariable &other);

    RealVariable &operator/(double coe);
    friend RealVariable &operator/(double coe, const RealVariable &other);

    RealVariable &operator==(double coe) const;
    RealVariable &operator==(const RealVariable &other) const;
    friend RealVariable &operator==(double coe, const RealVariable &other);

    RealVariable &operator^(int pow);
};

class ComplexVariable {
public:
    std::complex<double> m_x2, m_x, m_c;

    ComplexVariable() : m_x2(std::complex<double>(0, 0)), m_x(std::complex<double>(1, 0)), m_c(std::complex<double>(0, 0)){};
    ComplexVariable(std::complex<double> x2, std::complex<double> x, std::complex<double> c) : m_x2(x2), m_x(x), m_c(c){};

    ComplexVariable &operator*(std::complex<double> cmplx_coe);
    ComplexVariable &operator*(const ComplexVariable &other);
    friend ComplexVariable &operator*(std::complex<double> cmplx_coe, const ComplexVariable &other);

    ComplexVariable &operator+(const ComplexVariable &other);
    ComplexVariable &operator+(std::complex<double> cmplx_coe);
    friend ComplexVariable &operator+(std::complex<double> cmplx_coe, const ComplexVariable &other);

    ComplexVariable &operator-(const ComplexVariable &other);
    ComplexVariable &operator-(std::complex<double> cmplx_coe);
    friend ComplexVariable &operator-(std::complex<double> cmplx_coe, const ComplexVariable &other);

    ComplexVariable &operator/(std::complex<double> cmplx_coe);
    friend ComplexVariable &operator/(std::complex<double> cmplx_coe, const ComplexVariable &other);

    ComplexVariable &operator==(const ComplexVariable &other);
    ComplexVariable &operator==(std::complex<double> cmplx_coe);
    friend ComplexVariable &operator==(std::complex<double> cmplx_coe, const ComplexVariable &other);

    ComplexVariable &operator^(int pow);
};
double solve(const RealVariable &rv);
std::complex<double> solve(const ComplexVariable &cv);

}; // namespace solver