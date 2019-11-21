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

    unsigned i = bits.size() - 1;
    while (bits[i]) {
        bits.pop_back();
        --i;
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

// If fibits are normalized we can determine longer by length.
bool Fibo::operator<(const Fibo& f) const {
    if (bits.size() == f.bits.size()) {
        return bits < f.bits;
    }
    return bits.size() < f.bits.size();
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

Fibo& Fibo::operator&=(const Fibo& f) {
    if (bits.size() > f.bits.size()) {
        bits.resize(f.bits.size());
    } else {
        bits.resize(f.bits.size(), false);
    }

    this->bits &= f.bits;
    normalize();
    return *this;
}

Fibo& Fibo::operator|=(const Fibo& f) {
    if (bits.size() > f.bits.size()) {
        Fibo copy(f);
        copy.bits.resize(bits.size(), false);
        this->bits |= copy.bits;
    } else {
        bits.resize(f.bits.size(), false);
        this->bits |= f.bits;
    }

    normalize();
    return *this;
}

Fibo Fibo::operator+(const Fibo& f) const {
    Fibo copy(*this);
    return copy += f;
}

Fibo Fibo::operator&(const Fibo& f) const {
    Fibo copy(*this);
    return copy &= f;
}

Fibo Fibo::operator|(const Fibo& f) const {
    Fibo copy(*this);
    return copy |= f;
}

Fibo Fibo::operator^(const Fibo& f) const {
    return Fibo(bits ^ f.bits);
}
