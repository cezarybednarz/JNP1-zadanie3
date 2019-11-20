#include "fibo.h"

#include <utility>

Fibo::Fibo() {
    bits = boost::dynamic_bitset<>(1);
    bits[0] = 0;
}

unsigned Fibo::size() const {
    return bits.size();
}

const Fibo operator+(const Fibo& a, const Fibo& b) {
    unsigned diff = std::abs((int)a.size() - (int)b.size());

    if (diff > 0) {
        if (a.size() > b.size()) {
            b.append(boost::dynamic_bitset<>(diff));
        } else {
            a.append(boost::dynamic_bitset<>(diff));
        }
    }

    for (unsigned i = a.size() - 1; i >= 0; --i) {

    }
}


int main() {
    // wrzucilem to z tresci tutaj zeby sie latwiej kompilowalo xd

    // Fibo f;

    // assert(f == Zero());
    // assert(Fibo(f) == Zero());
    // assert(Zero() < One());
    // assert(Fibo("11") == Fibo("100"));
    // assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
    // assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    // assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    // assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    // assert((Fibo("101") << 3) == Fibo("101000"));

    // f = One();
    // f <<= 3;
    // assert(f == Fibo("1000"));

    // f = One();
    // assert(f + Fibo("1") == Fibo("10"));
    // assert(f == One());

    // Fibo f1("101");
    // Fibo f2 = Fibo("101");
    // assert(f1 == f2);

    // assert(Fibo("11").length() == 3); // 11 == 100

    // std::cout << Fibo("11") << std::endl; // prints 100
}
