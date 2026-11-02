#pragma once

#include <cmath>
#include <iosfwd>
#include <stdexcept>
#include <type_traits>

namespace qmaths {
// Defined in the header so every operation can be inlined and vectorized by the caller
class complexNb {
public:
    constexpr complexNb() noexcept = default;
    constexpr complexNb(double re, double im = 0.0) noexcept : m_re(re), m_im(im) {}

    static complexNb fromPolar(double modulus, double argument) noexcept {
        return {modulus * std::cos(argument), modulus * std::sin(argument)};
    }

    [[nodiscard]] constexpr double re() const noexcept { return m_re; }
    [[nodiscard]] constexpr double im() const noexcept { return m_im; }
    constexpr void setRe(double re) noexcept { m_re = re; }
    constexpr void setIm(double im) noexcept { m_im = im; }

    [[nodiscard]] constexpr complexNb conj() const noexcept { return {m_re, -m_im}; }

    // |z|^2, the measurement probability of an amplitude
    [[nodiscard]] constexpr double norm() const noexcept { return m_re * m_re + m_im * m_im; }

    // |z|, sqrt instead of hypot: amplitudes stay small, no overflow protection needed
    [[nodiscard]] double abs() const noexcept { return std::sqrt(norm()); }

    [[nodiscard]] double arg() const noexcept { return std::atan2(m_im, m_re); }

    [[nodiscard]] constexpr bool approxEqual(const complexNb &other, double epsilon = 1e-9) const noexcept {
        const double dRe = m_re - other.m_re;
        const double dIm = m_im - other.m_im;
        return (dRe < 0 ? -dRe : dRe) <= epsilon && (dIm < 0 ? -dIm : dIm) <= epsilon;
    }

    constexpr complexNb &operator+=(const complexNb &other) noexcept {
        m_re += other.m_re;
        m_im += other.m_im;
        return *this;
    }

    constexpr complexNb &operator-=(const complexNb &other) noexcept {
        m_re -= other.m_re;
        m_im -= other.m_im;
        return *this;
    }

    // (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    constexpr complexNb &operator*=(const complexNb &other) noexcept {
        const double re = m_re * other.m_re - m_im * other.m_im;
        const double im = m_re * other.m_im + m_im * other.m_re;
        m_re = re;
        m_im = im;
        return *this;
    }

    // Real scalar: 2 multiplications instead of 4 multiplications + 2 additions
    constexpr complexNb &operator*=(double scalar) noexcept {
        m_re *= scalar;
        m_im *= scalar;
        return *this;
    }

    // z / w = z * conj(w) / |w|^2, one division then multiplications
    constexpr complexNb &operator/=(const complexNb &other) {
        const double denominator = other.norm();
        if (denominator == 0.0) {
            throw std::domain_error("complexNb: division by zero");
        }
        const double inverse = 1.0 / denominator;
        const double re = (m_re * other.m_re + m_im * other.m_im) * inverse;
        const double im = (m_im * other.m_re - m_re * other.m_im) * inverse;
        m_re = re;
        m_im = im;
        return *this;
    }

    // Real scalar, typically used to normalize a state
    constexpr complexNb &operator/=(double scalar) {
        if (scalar == 0.0) {
            throw std::domain_error("complexNb: division by zero");
        }
        return *this *= 1.0 / scalar;
    }

    constexpr complexNb operator-() const noexcept { return {-m_re, -m_im}; }

    friend constexpr complexNb operator+(complexNb lhs, const complexNb &rhs) noexcept { return lhs += rhs; }
    friend constexpr complexNb operator-(complexNb lhs, const complexNb &rhs) noexcept { return lhs -= rhs; }
    friend constexpr complexNb operator*(complexNb lhs, const complexNb &rhs) noexcept { return lhs *= rhs; }
    friend constexpr complexNb operator*(complexNb lhs, double rhs) noexcept { return lhs *= rhs; }
    friend constexpr complexNb operator*(double lhs, complexNb rhs) noexcept { return rhs *= lhs; }
    friend constexpr complexNb operator/(complexNb lhs, const complexNb &rhs) { return lhs /= rhs; }
    friend constexpr complexNb operator/(complexNb lhs, double rhs) { return lhs /= rhs; }

    friend constexpr bool operator==(const complexNb &lhs, const complexNb &rhs) noexcept = default;

    friend std::ostream &operator<<(std::ostream &os, const complexNb &z);

private:
    double m_re = 0.0;
    double m_im = 0.0;
};

// Same memory layout as C99 `double _Complex`, std::complex<double> and BLAS complex types,
// so a contiguous array of complexNb can be handed to C libraries without copying
static_assert(sizeof(complexNb) == 2 * sizeof(double));
static_assert(alignof(complexNb) == alignof(double));
static_assert(std::is_standard_layout_v<complexNb>);
static_assert(std::is_trivially_copyable_v<complexNb>);

// e^(a + bi) = e^a * (cos b + i sin b)
inline complexNb exp(const complexNb &z) noexcept { return complexNb::fromPolar(std::exp(z.re()), z.im()); }

namespace constants {
inline constexpr complexNb I{0.0, 1.0};
} // namespace constants
} // namespace qmaths
