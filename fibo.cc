#include "fibo.h"

#include <utility>

// funkcja pomocnicza do operatorow w Fibo
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

// konstruktory i destruktory
Fibo::Fibo() {
    bits = boost::dynamic_bitset<>(1);
}

Fibo::~Fibo() = default;

Fibo::Fibo(const Fibo& f) : bits(f.bits) {};

Fibo::Fibo(const Fibo&& f) : bits(std::move(f.bits)) {};

Fibo& Fibo::operator=(const Fibo& f) = default;

Fibo& Fibo::operator=(const Fibo&& f) {
    bits = std::move(f.bits);
    return *this;
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

Fibo Fibo::operator+(const Fibo& f) const {
    Fibo result;
    result.bits.resize(std::max(bits.size(), f.bits.size()) + 1);

    for (unsigned i = bits.size() - 1; i >= 2; --i) {
        if (bits[i] & f.bits[i]) {
            result.bits[i] = 1;
            if (bits[i - 2] | f.bits[i - 2]) {
                result.bits[i + 1] = 1;
                result.bits[i - 2] = 1;
                i -= 3;
                continue;
            } else {
                result.bits[i - 1] = 1;
                result.bits[i - 2] = 1;
                i -= 3;
                continue;
            }
        } else {
            result.bits[i] = bits[i] | f.bits[i];
        }
    }

    result.normalize();
    return result;
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
