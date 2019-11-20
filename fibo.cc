#include "fibo.h"

#include <utility>

Fibo::Fibo() {
    bits = boost::dynamic_bitset<>(1);
    bits[0] = 0;
}

void Fibo::normalize() {
    for (unsigned i = bits.size() - 1; i >= 1; --i) {
        if (bits[i] & bits[i - 1]) {
            if (i == bits.size() - 1) {
                bits.push_back(1);
            } else {
                bits[i + 1] = 1;
                bits[i] = 0;
                bits[i] = 0;
            }
        }
    }
}

const Fibo operator+(const Fibo& a, const Fibo& b) {
    Fibo c;
    c.bits.resize(std::max(a.bits.size(), b.bits.size()) + 1);

    for (unsigned i = a.bits.size() - 1; i >= 2; --i) {
        if (a.bits[i] & b.bits[i]) {
            c.bits[i] = 1;
            if (a.bits[i - 2] | b.bits[i - 2]) {
                c.bits[i + 1] = 1;
                c.bits[i - 2] = 1;
                i -= 3;
                continue;
            } else {
                c.bits[i - 1] = 1;
                c.bits[i - 2] = 1;
                i -= 3;
                continue;
            }
        } else {
            c.bits[i] = a.bits[i] | b.bits[i];
        }
    }

    c.normalize();
    return c;
}
