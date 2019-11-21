#ifndef __FIBO_H__
#define __FIBO_H__

#include "boost/dynamic_bitset.hpp"
#include <string>

class Fibo {

private:
    boost::dynamic_bitset<> bits;
    explicit Fibo(const boost::dynamic_bitset<>& bits);
    void normalize();

public:
    Fibo();
    ~Fibo();
    Fibo(const Fibo& f);
    Fibo(const Fibo&& f);
    explicit Fibo(std::string s);
    Fibo(unsigned long long n);
    Fibo(unsigned long n);
    Fibo(unsigned int n);
    Fibo(unsigned short n);
    Fibo(long long n);
    Fibo(long n);
    Fibo(int n);
    Fibo(short n);


    Fibo& operator=(const Fibo& f);
    Fibo& operator=(const Fibo&& f);

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

    Fibo operator+(const Fibo& f) const;
    Fibo operator&(const Fibo& f) const;
    Fibo operator|(const Fibo& f) const;
    Fibo operator^(const Fibo& f) const;
    Fibo operator<<(const Fibo& f) const;

    size_t length();

    friend const Fibo Zero();
    friend const Fibo One();

    friend std::ostream& operator<<(std::ostream& out, const Fibo& f);

};


#endif // __FIBO_H__
