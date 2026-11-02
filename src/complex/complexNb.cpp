//
// Created by matthieu on 8/7/26.
//

#include "complex/complexNb.hpp"

#include <cmath>
#include <stdexcept>

namespace qmaths {
complexNb complexNb::fromPolar(double modulus, double argument) {
    return {modulus * std::cos(argument), modulus * std::sin(argument)};
}

double complexNb::re() const { return m_re; }
double complexNb::im() const { return m_im; }
void complexNb::setRe(double re) { m_re = re; }
void complexNb::setIm(double im) { m_im = im; }

complexNb complexNb::conj() const { return {m_re, -m_im}; }

// |z|, hypot avoids overflow on large components
double complexNb::abs() const { return std::hypot(m_re, m_im); }

// |z|^2, the measurement probability of an amplitude
double complexNb::norm() const { return m_re * m_re + m_im * m_im; }

double complexNb::arg() const { return std::atan2(m_im, m_re); }

bool complexNb::approxEqual(const complexNb &other, double epsilon) const {
    return std::abs(m_re - other.m_re) <= epsilon && std::abs(m_im - other.m_im) <= epsilon;
}

complexNb &complexNb::operator+=(const complexNb &other) {
    m_re += other.m_re;
    m_im += other.m_im;
    return *this;
}

complexNb &complexNb::operator-=(const complexNb &other) {
    m_re -= other.m_re;
    m_im -= other.m_im;
    return *this;
}

// (a + bi)(c + di) = (ac - bd) + (ad + bc)i
complexNb &complexNb::operator*=(const complexNb &other) {
    const double re = m_re * other.m_re - m_im * other.m_im;
    const double im = m_re * other.m_im + m_im * other.m_re;
    m_re = re;
    m_im = im;
    return *this;
}

// z / w = z * conj(w) / |w|^2
complexNb &complexNb::operator/=(const complexNb &other) {
    const double denominator = other.norm();
    if (denominator == 0.0) {
        throw std::domain_error("complexNb: division by zero");
    }
    *this *= other.conj();
    m_re /= denominator;
    m_im /= denominator;
    return *this;
}

complexNb complexNb::operator-() const { return {-m_re, -m_im}; }

complexNb operator+(complexNb lhs, const complexNb &rhs) { return lhs += rhs; }
complexNb operator-(complexNb lhs, const complexNb &rhs) { return lhs -= rhs; }
complexNb operator*(complexNb lhs, const complexNb &rhs) { return lhs *= rhs; }
complexNb operator/(complexNb lhs, const complexNb &rhs) { return lhs /= rhs; }

std::ostream &operator<<(std::ostream &os, const complexNb &z) {
    os << z.m_re << (z.m_im < 0 ? " - " : " + ") << std::abs(z.m_im) << "i";
    return os;
}

// e^(a + bi) = e^a * (cos b + i sin b)
complexNb exp(const complexNb &z) { return complexNb::fromPolar(std::exp(z.re()), z.im()); }
} // namespace qmaths
