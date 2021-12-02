#ifndef _ration_h
#define _ration_h

#include <iostream>

using std::istream;
using std::ostream;

class ration_t
{
private:
    long long int m_a;
    long long int m_b;

public:
    ration_t(long long int a = 0, long long int b = 1);
    ~ration_t() = default;

    long double eval() const;

    ration_t operator+(const ration_t &r);
    ration_t operator-(const ration_t &r);
    ration_t operator-();
    ration_t operator*(const ration_t &r);
    ration_t operator/(const ration_t &r);

    ration_t &operator+=(const ration_t &r);
    ration_t &operator-=(const ration_t &r);
    ration_t &operator*=(const ration_t &r);
    ration_t &operator/=(const ration_t &r);

    bool operator==(const ration_t &r);
    bool operator!=(const ration_t &r);
    bool operator>=(const ration_t &r);
    bool operator<=(const ration_t &r);
    bool operator>(const ration_t &r);
    bool operator<(const ration_t &r);

    std::string to_latex();

    friend istream &operator>>(istream &in, ration_t &me);
    friend ostream &operator<<(ostream &out, const ration_t &me);

private:
    void __simplify();
};

#endif //_ration_h