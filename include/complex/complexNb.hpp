#pragma once

#include <ostream>

namespace qmaths {
class complexNb {
public:
    constexpr complexNb() = default;
    constexpr complexNb(double re, double im = 0.0) : m_re(re), m_im(im) {}

    static complexNb fromPolar(double modulus, double argument);

    [[nodiscard]] double re() const;
    [[nodiscard]] double im() const;
    void setRe(double re);
    void setIm(double im);

    [[nodiscard]] complexNb conj() const;
    [[nodiscard]] double abs() const;
    [[nodiscard]] double norm() const;
    [[nodiscard]] double arg() const;
    [[nodiscard]] bool approxEqual(const complexNb &other, double epsilon = 1e-9) const;

    complexNb &operator+=(const complexNb &other);
    complexNb &operator-=(const complexNb &other);
    complexNb &operator*=(const complexNb &other);
    complexNb &operator/=(const complexNb &other);

    complexNb operator-() const;

    friend complexNb operator+(complexNb lhs, const complexNb &rhs);
    friend complexNb operator-(complexNb lhs, const complexNb &rhs);
    friend complexNb operator*(complexNb lhs, const complexNb &rhs);
    friend complexNb operator/(complexNb lhs, const complexNb &rhs);

    friend bool operator==(const complexNb &lhs, const complexNb &rhs) = default;

    friend std::ostream &operator<<(std::ostream &os, const complexNb &z);

private:
    double m_re = 0.0;
    double m_im = 0.0;
};

complexNb exp(const complexNb &z);
} // namespace qmaths
