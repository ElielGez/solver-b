#include "solver.hpp"
#include <cmath>
#include <stdexcept>
using namespace solver;

/*
    RealVariable Class implemention:
*/

// Operator *:
RealVariable &RealVariable::operator*(double coe) const {
    RealVariable *res = new RealVariable(coe * m_x2, coe * m_x, coe * m_c);
    return *res;
}

RealVariable &RealVariable::operator*(const RealVariable &other) const {
    // Handle the power > 2
    if (m_x2 * other.m_x2 != 0 || (m_x2 * other.m_x + m_x * other.m_x2) != 0) {
        throw runtime_error("Power cannot be greater then 2!");
    }
    double a = m_x2 * other.m_c + m_x * other.m_x + m_c * other.m_x2;
    double b = m_x * other.m_c + m_c * other.m_x;
    double c = m_c * other.m_c;

    RealVariable *res = new RealVariable(a, b, c);
    return *res;
}

RealVariable &solver::operator*(double coe, const RealVariable &other) //friend
{
    RealVariable *res = new RealVariable(coe * other.m_x2, coe * other.m_x, coe * other.m_c);
    return *res;
}

// Operator +:
RealVariable &RealVariable::operator+(double coe) {
    RealVariable *res = new RealVariable(m_x2, m_x, coe + m_c);
    return *res;
}

RealVariable &RealVariable::operator+(const RealVariable &other) {
    RealVariable *res = new RealVariable(m_x2 + other.m_x2, m_x + other.m_x, m_c + other.m_c);
    return *res;
}

RealVariable &solver::operator+(double coe, const RealVariable &other) {
    RealVariable *res = new RealVariable(other.m_x2, other.m_x, coe + other.m_c);
    return *res;
}

// Operator ==:
RealVariable &RealVariable::operator==(double coe) const {
    RealVariable *res = new RealVariable(m_x2, m_x, m_c - coe);
    return *res;
}

RealVariable &RealVariable::operator==(const RealVariable &other) const {
    RealVariable *res = new RealVariable(m_x2 - other.m_x2, m_x - other.m_x, m_c - other.m_c);
    return *res;
}

RealVariable &solver::operator==(double coe, const RealVariable &other) {
    RealVariable *res = new RealVariable(other.m_x2, other.m_x, other.m_c - coe);
    return *res;
}

// Operator -:
RealVariable &RealVariable::operator-(double coe) {
    RealVariable *res = new RealVariable(m_x2, m_x, m_c - coe);
    return *res;
}

RealVariable &RealVariable::operator-(const RealVariable &other) {
    RealVariable *res = new RealVariable(m_x2 - other.m_x2, m_x - other.m_x, m_c - other.m_c);
    return *res;
}

RealVariable &solver::operator-(double coe, const RealVariable &other) {
    RealVariable *res = new RealVariable(-other.m_x2, -other.m_x, coe - other.m_c);
    return *res;
}

// Operator /:
RealVariable &RealVariable::operator/(double coe) {
    if (coe == 0) {
        throw runtime_error("Cannot divide by 0!");
    }

    RealVariable *res = new RealVariable(m_x2 / coe, m_x / coe, m_c / coe);
    return *res;
}

RealVariable &solver::operator/(double coe, const RealVariable &other) {
    if (other.m_x2 == 0 || other.m_x == 0 || other.m_c == 0) {
        throw runtime_error("Cannot divide by 0!");
    }

    RealVariable *res = new RealVariable(coe / other.m_x2, coe / other.m_x, coe / other.m_c);
    return *res;
}

// Operator ^:
RealVariable &RealVariable::operator^(int pow) {
    RealVariable *res;
    if (pow < 0 || pow > 2 || (m_x2 != 0 && pow > 1)) {
        throw runtime_error("Power cannot be greater then 2 or less then 0!");
    }

    if (pow == 0) {
        res = new RealVariable(0, 0, 1);
        return *res;
    } else if (pow == 1) {
        res = new RealVariable(m_x2, m_x, m_c);
        return *res;
    } else {
        RealVariable x(m_x2, m_x, m_c);
        RealVariable y(m_x2, m_x, m_c);
        res = &(x * y);
        return *res;
    }
}

// Solve:
double solver::solve(const RealVariable &rv) {
    if (rv.m_x2 == 0 && rv.m_x == 0 && rv.m_c == 0) {
        throw runtime_error("Infinite Solutions!");
    }

    if (rv.m_x2 == 0) {
        if (rv.m_x == 0) {
            throw runtime_error("No Solution!");
        }
        return (-rv.m_c) / rv.m_x;
    }

    double delta = pow(rv.m_x, 2) - 4 * rv.m_x2 * rv.m_c;

    if (delta < 0) {
        throw runtime_error("No Solution!");
    }

    return ((-rv.m_x) + sqrt(delta)) / (2 * rv.m_x2);
}
