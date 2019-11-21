#include "fibo.h"

#include <iostream>

void Fibo::normalize() {
    for (size_t i = bits.size() - 1; i >= 1; --i) {
        if (bits[i] & bits[i - 1]) {
            if (i == bits.size() - 1) {
                bits.push_back(1);
            }
            bits[i + 1] = 1;
            bits[i] = 0;
            bits[i - 1] = 0;
        }
    }

    size_t i = bits.size() - 1;
    while(!bits.empty() && !bits[i]) {
        bits.pop_back();
        --i;
    }

    if(bits.empty()) {
        bits.push_back(0);
    }
}

Fibo::Fibo() {
    bits.push_back(0);
}

Fibo::~Fibo() { bits.reset(); }

Fibo::Fibo(const Fibo& f) = default;

Fibo::Fibo(std::string s) {
    if(s.empty()) {
        bits.push_back(0);
        return;
    }
    for(size_t i = 0; i < s.size(); ++i) {
        assert(s[i] == '0' || s[i] == '1');
        bits.push_back(s[s.size() - i - 1] - '0');
    }
    normalize();
}

Fibo::Fibo(unsigned long long n) {
    if(n == 0ULL) {
        bits.push_back(0);
        return;
    }
    unsigned long long f1 = 0, f2 = 1, temp = 1;
    size_t length = 0;
    while(f1 + f2 <= n) {
        temp = f1 + f2;
        f1 = f2;
        f2 = temp;
        length++;
    }
    bits.resize(length, false);
    for(size_t i = length - 1; i < length; --i) {
        if(f2 <= n) {
            bits[i] = 1;
            n -= f2;
        }
        temp = f2 - f1;
        f2 = f1;
        f1 = temp;
    }
}

Fibo::Fibo(unsigned long n) : Fibo((unsigned long long) n) {};

Fibo::Fibo(unsigned int n) : Fibo((unsigned long long) n) {};

Fibo::Fibo(unsigned short n) : Fibo((unsigned long long) n) {};

Fibo::Fibo(long long n) {
    assert(n >= 0);
    *this = Fibo((unsigned long long) n);
}

Fibo::Fibo(long n) : Fibo((long long) n) {};

Fibo::Fibo(int n) : Fibo((long long) n) {};

Fibo::Fibo(short n) : Fibo((long long) n) {};

Fibo& Fibo::operator=(const Fibo& f) = default;

Fibo::Fibo(const boost::dynamic_bitset<>& bits) {
    this->bits = bits;
}

// If fibits are normalized we can determine greater by length.
bool operator<(const Fibo& f1, const Fibo& f2) {
    if (f1.bits.size() == f2.bits.size()) {
        return f1.bits < f2.bits;
    }
    return f1.bits.size() < f2.bits.size();
}

bool operator<=(const Fibo& f1, const Fibo& f2) {
    return f1 < f2 || f1 == f2;
}

bool operator>(const Fibo& f1, const Fibo& f2) {
    return f2 < f1;
}

bool operator>=(const Fibo& f1, const Fibo& f2) {
    return f2 <= f1;
}

bool operator==(const Fibo& f1, const Fibo& f2) {
    return f1.bits == f2.bits;
}

bool operator!=(const Fibo& f1, const Fibo& f2) {
    return !(f1 == f2);
}

Fibo& Fibo::operator+=(const Fibo& f) {
    bits.resize(std::max(bits.size(), f.bits.size()) + 1);
    bool add = 0;
    size_t length = std::min(bits.size(), f.bits.size());
    for (size_t i = length - 1; i < length; --i) {
        if (bits[i] && f.bits[i]) {
            if (!add) {
                bits[i] = 0;
                add = true;
            }
            if(i == 1) {
                bits[0] = 1;
            }
            bits[i + 1] = 1;
            i--;
        } else if ((bits[i] || f.bits[i]) && add) {
            bits[i] = 0;
            bits[i + 1] = 1;
        } else {
            if(i != 0) {
                bits[i - 1] |= bits[i];
            } else {
                bits[i] = 1;
            }
            add = false;
        }
    }

    normalize();
    return *this;
}

Fibo& Fibo::operator&=(const Fibo& f) {
    if (bits.size() > f.bits.size()) {
        bits.resize(f.bits.size(), false);
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

Fibo& Fibo::operator^=(const Fibo& f) {
    if (bits.size() > f.bits.size()) {
        Fibo copy(f);
        copy.bits.resize(bits.size(), false);
        this->bits ^= copy.bits;
    } else {
        bits.resize(f.bits.size(), false);
        this->bits ^= f.bits;
    }

    normalize();
    return *this;
}

Fibo& Fibo::operator<<=(size_t n) {
    size_t length = bits.size();
    bits.resize(bits.size() + n);

    for(size_t i = 0; i < length; ++i) {
        bits[bits.size() - length + i] = bits[i];
    }

    for(size_t i = 0; i < length; ++i) {
        bits[i] = 0;
    }

    normalize();
    return *this;
}

const Fibo operator+(Fibo f1, const Fibo& f2) {
    return f1 += f2;
}

const Fibo operator&(Fibo f1, const Fibo& f2) {
    return f1 &= f2;
}

const Fibo operator|(Fibo f1, const Fibo& f2) {
    return f1 |= f2;
}

const Fibo operator^(Fibo f1, const Fibo& f2) {
    return f1 ^= f2;
}


const Fibo Fibo::operator<<(size_t n) const {
    Fibo copy(*this);
    return copy <<= n;
}

size_t Fibo::length() const {
    return bits.size();
}

const Fibo Zero() {
    return Fibo();
}

const Fibo One() {
    return Fibo(1);
}

std::ostream& operator<<(std::ostream& out, const Fibo& f) {
    out << f.bits;
    return out;
}
