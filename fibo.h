#ifndef __FIBO_H__
#define __FIBO_H__

#include "boost/dynamic_bitset.hpp"
#include <string>

class Fibo {

private:
    boost::dynamic_bitset<> bits;
    void normalize();

public:
    Fibo();
    ~Fibo();
    Fibo(const Fibo& f);
    Fibo(Fibo&& f);
    explicit Fibo(int n);
    explicit Fibo(unsigned n);
    explicit Fibo(unsigned long n);
    explicit Fibo(unsigned long long n);
    explicit Fibo(std::string s);

    Fibo& operator=(Fibo& f);
    Fibo& operator=(Fibo&& f);

    Fibo& operator+=(const Fibo& f);
    Fibo& operator&=(const Fibo& f);
    Fibo& operator|=(const Fibo& f);
    Fibo& operator^=(const Fibo& f);
    Fibo& operator<<=(const Fibo& f);

    bool operator<(const Fibo& f) const;
    bool operator>(const Fibo& f) const;
    bool operator<=(const Fibo& f) const;
    bool operator>=(const Fibo& f) const;
    bool operator==(const Fibo& f) const;
    bool operator!=(const Fibo& f) const;

    Fibo operator+(const Fibo& f);
    Fibo operator&(const Fibo& f);
    Fibo operator|(const Fibo& f);
    Fibo operator^(const Fibo& f);
    Fibo operator<<(const Fibo& f);

    Fibo& Zero() const;
    Fibo& One() const;
};

friend std::ostream& operator<<(std::ostream&, const Fibo&);

#endif // __FIBO_H__