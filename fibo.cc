#include "fibo.h"

#include <utility>

void Fibo::normalize() {
    for (size_t i = bits.size() - 1; i >= 1; --i) {
        continue;
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

    size_t i = bits.size() - 1;
    while(!bits.empty() && bits[i]) {
        bits.pop_back();
        --i;
    }

    if(bits.empty()) {
        bits.push_back(0);
    }
}

Fibo::Fibo() {
    bits = boost::dynamic_bitset<>(1, false);
}

Fibo::~Fibo() = default;

Fibo::Fibo(const Fibo& f) = default;

Fibo::Fibo(const Fibo&& f) : bits(std::move(f.bits)) {};

Fibo::Fibo(std::string s) {
    bits = boost::dynamic_bitset<>();
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
    bits = boost::dynamic_bitset<>();
    if(n == 0) {
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
    bits.push_back(0);
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

Fibo& Fibo::operator=(const Fibo&& f) {
    bits = std::move(f.bits);
    return *this;
}

Fibo::Fibo(const boost::dynamic_bitset<>& bits) {
    this->bits = bits;
}

// If fibits are normalized we can determine greater by length.
bool Fibo::operator<(const Fibo& f) const {
    if (bits.size() == f.bits.size()) {
        return bits < f.bits;
    }
    return bits.size() < f.bits.size();
}

bool Fibo::operator<=(const Fibo& f) const {
    return *this < f || *this == f;
}

bool Fibo::operator>(const Fibo& f) const {
    return f < *this;
}

bool Fibo::operator>=(const Fibo& f) const {
    return f <= *this;
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

const Fibo Fibo::operator<<(size_t n) const {
    Fibo copy(*this);
    return copy <<= n;
}

const Fibo operator+(Fibo a, const Fibo& b) { return a += b; }
const Fibo operator&(Fibo a, const Fibo& b) { return a &= b; }
const Fibo operator|(Fibo a, const Fibo& b) { return a |= b; }
const Fibo operator^(Fibo a, const Fibo& b) { return a ^= b; }

size_t Fibo::length() {
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
