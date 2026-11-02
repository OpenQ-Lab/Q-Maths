//
// Created by matthieu on 8/7/26.
//

#include "complex/complexNb.hpp"

#include <ostream>

namespace qmaths {
// Kept out of the header so users don't pay for <ostream> unless they print
std::ostream &operator<<(std::ostream &os, const complexNb &z) {
    os << z.m_re << (z.m_im < 0 ? " - " : " + ") << (z.m_im < 0 ? -z.m_im : z.m_im) << "i";
    return os;
}
} // namespace qmaths
