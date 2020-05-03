#include "solver.hpp"
#include <cmath>
#include <stdexcept>
using namespace solver;

/*
    ComplexVariable Class implemention:
*/

// Operator *:
ComplexVariable &ComplexVariable::operator*(std::complex<double> cmplx_coe) {
    ComplexVariable *res = new ComplexVariable(m_x2 * cmplx_coe, m_x * cmplx_coe, m_c * cmplx_coe);
    return *res;
}

ComplexVariable &ComplexVariable::operator*(const ComplexVariable &other) {
    std::complex<double> zero = std::complex<double>(0, 0);
    // Handle the power > 2
    if (m_x2 * other.m_x2 != zero || (m_x2 * other.m_x + m_x * other.m_x2) != zero) {
        throw runtime_error("Power cannot be greater then 2!");
    }
    std::complex<double> a = m_x2 * other.m_c + m_x * other.m_x + m_c * other.m_x2;
    std::complex<double> b = m_x * other.m_c + m_c * other.m_x;
    std::complex<double> c = m_c * other.m_c;

    ComplexVariable *res = new ComplexVariable(a, b, c);
    return *res;
}

ComplexVariable &solver::operator*(std::complex<double> cmplx_coe, const ComplexVariable &other) // friend
{
    ComplexVariable *res = new ComplexVariable(other.m_x2 * cmplx_coe, other.m_x * cmplx_coe, other.m_c * cmplx_coe);
    return *res;
}

// Operator +:
ComplexVariable &ComplexVariable::operator+(std::complex<double> cmplx_coe) {
    ComplexVariable *res = new ComplexVariable(m_x2, m_x, m_c + cmplx_coe);
    return *res;
}

ComplexVariable &ComplexVariable::operator+(const ComplexVariable &other) {
    ComplexVariable *res = new ComplexVariable(m_x2 + other.m_x2, m_x + other.m_x, m_c + other.m_c);
    return *res;
}

ComplexVariable &solver::operator+(std::complex<double> cmplx_coe, const ComplexVariable &other) //friend
{
    ComplexVariable *res = new ComplexVariable(other.m_x2, other.m_x, other.m_c + cmplx_coe);
    return *res;
}

// Operator ==:
ComplexVariable &ComplexVariable::operator==(std::complex<double> cmplx_coe) {
    ComplexVariable *res = new ComplexVariable(m_x2, m_x, m_c - cmplx_coe);
    return *res;
}

ComplexVariable &ComplexVariable::operator==(const ComplexVariable &other) {
    ComplexVariable *res = new ComplexVariable(m_x2 - other.m_x2, m_x - other.m_x, m_c - other.m_c);
    return *res;
}

ComplexVariable &solver::operator==(std::complex<double> cmplx_coe, const ComplexVariable &other) //friend
{
    ComplexVariable *res = new ComplexVariable(other.m_x2, other.m_x, other.m_c - cmplx_coe);
    return *res;
}

// Operator -:

ComplexVariable &ComplexVariable::operator-(const ComplexVariable &other) {
    ComplexVariable *res = new ComplexVariable(m_x2 - other.m_x2, m_x - other.m_x, m_c - other.m_c);
    return *res;
}

ComplexVariable &ComplexVariable::operator-(std::complex<double> cmplx_coe) {
    ComplexVariable *res = new ComplexVariable(m_x2, m_x, m_c - cmplx_coe);
    return *res;
}

ComplexVariable &solver::operator-(std::complex<double> cmplx_coe, const ComplexVariable &other) //friend
{
    ComplexVariable *res = new ComplexVariable(-other.m_x2, -other.m_x, cmplx_coe - other.m_c);
    return *res;
}

// Operator /:

ComplexVariable &ComplexVariable::operator/(std::complex<double> cmplx_coe) {
    if (cmplx_coe == std::complex<double>(0, 0)) {
        throw runtime_error("Cannot divide by 0!");
    }

    ComplexVariable *res = new ComplexVariable(m_x2 / cmplx_coe, m_x / cmplx_coe, m_c / cmplx_coe);
    return *res;
}

ComplexVariable &solver::operator/(std::complex<double> cmplx_coe, const ComplexVariable &other) //friend
{
    std::complex<double> zero = std::complex<double>(0, 0);
    if (other.m_x2 == zero || other.m_x == zero || other.m_c == zero) {
        throw runtime_error("Cannot divide by 0!");
    }
    ComplexVariable *res = new ComplexVariable(cmplx_coe / other.m_x2, cmplx_coe / other.m_x, cmplx_coe / other.m_c);
    return *res;
}

// Operator ^:
ComplexVariable &ComplexVariable::operator^(int pow) {
    ComplexVariable *res;
    if (pow < 0 || pow > 2 || (m_x2 != std::complex<double>(0, 0) && pow > 1)) {
        throw runtime_error("Power cannot be greater then 2 or less then 0!");
    }

    if (pow == 0) {
        res = new ComplexVariable(0, 0, 1);
        return *res;
    } else if (pow == 1) {
        res = new ComplexVariable(m_x2, m_x, m_c);
        return *res;
    } else {
        ComplexVariable x(m_x2, m_x, m_c);
        ComplexVariable y(m_x2, m_x, m_c);
        res = &(x * y);
        return *res;
    }
}

// Solve:
std::complex<double> solver::solve(const ComplexVariable &cv) {
    std::complex<double> zero = std::complex<double>(0, 0);
    if (cv.m_x2 == zero && cv.m_x == zero && cv.m_c == zero) {
        throw runtime_error("Infinite Solutions!");
    }

    if (cv.m_x2 == zero) {
        if (cv.m_x == zero) {
            throw runtime_error("No Solution!");
        }
        return (-cv.m_c) / cv.m_x;
    }

    std::complex<double> delta = pow(cv.m_x, 2) - 4.0 * cv.m_x2 * cv.m_c;

    return ((-cv.m_x) + sqrt(delta)) / (2.0 * cv.m_x2);
}
