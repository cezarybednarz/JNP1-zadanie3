#include "fibo.h"

#include <utility>

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

Fibo::Fibo() {
    bits = boost::dynamic_bitset<>(1);
    bits[0] = 0;
}

Fibo::Fibo(const Fibo& f) {

}

Fibo::Fibo(const boost::dynamic_bitset<>& bits) {
    this->bits = bits;
}


bool Fibo::operator<(const Fibo& f) const {
    return bits < f.bits;
}

bool Fibo::operator<=(const Fibo& f) const {
    return bits <= f.bits;
}

bool Fibo::operator>(const Fibo& f) const {
    return bits > f.bits;
}

bool Fibo::operator>=(const Fibo& f) const {
    return bits >= f.bits;
}

bool Fibo::operator==(const Fibo& f) const {
    return bits == f.bits;
}

bool Fibo::operator!=(const Fibo& f) const {
    return bits != f.bits;
}

Fibo& Fibo::operator+=(const Fibo& f) {
    bits.resize(std::max(bits.size(), f.bits.size()) + 1);

    for (unsigned i = bits.size() - 1; i >= 2; --i) {
        if (bits[i] & f.bits[i]) {
            bits[i] = 1;
            if (bits[i - 2] | f.bits[i - 2]) {
                bits[i + 1] = 1;
                bits[i - 2] = 1;
                i -= 3;
                continue;
            } else {
                bits[i - 1] = 1;
                bits[i - 2] = 1;
                i -= 3;
                continue;
            }
        } else {
            bits[i] = bits[i] | f.bits[i];
        }
    }

    normalize();
    return *this;
}

Fibo Fibo::operator+(const Fibo& f) const {
    return *this += f;
}

Fibo Fibo::operator&(const Fibo& f) const {
    return Fibo(bits & f.bits);
}

Fibo Fibo::operator|(const Fibo& f) const {
    return Fibo(bits | f.bits);
}

Fibo Fibo::operator^(const Fibo& f) const {
    return Fibo(bits ^ f.bits);
}
