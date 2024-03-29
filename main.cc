#include "fibo.h"

#include <cassert>
#include <iostream>

int main() {

/*
    Fibo f1, f2;
    bool b;

    // nie powinno sie kompilowac i sie nie kompiluje
    Fibo f3(true);
    Fibo f4('a');
    f1 += "10";
    f1 = f2 + "10";
    b = "10" < f2;
    Zero() += Fibo("10");
    One() += Fibo("10");

    // natomiast to powinno
    f1 += 2;
    f1 = f2 + 2;
    b = 2 < f2;
*/

    std::cout << Fibo(44) << " == " << 10010010 << "\n";
    std::cout << Fibo("10010") << " < \n";
    std::cout << Fibo("11") << "\n";

    std::cout << Fibo("1") + Fibo("1") << " == 10\n";
    std::cout << Fibo("1") + Fibo("10") << " == 100\n";
    std::cout << Fibo("10") + Fibo("1") << " == 100\n";
    std::cout << Fibo("10") + Fibo("10") << " == 101\n";


    Fibo f;
    assert(f == Zero());
    assert(Fibo(f) == Zero());
    assert(Zero() < One());
    assert(Fibo("11") == Fibo("100"));
    assert((Fibo("1001") + Fibo("10")) == Fibo("1011")); // blad
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));
    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();
    assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    std::cout << Fibo("11") << std::endl; // prints 100
}
