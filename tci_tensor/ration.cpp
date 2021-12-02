#include "ration.h"
#include <string>
#include <numeric>
#include <sstream>

ration_t::ration_t(long long int a, long long int b)
    : m_a{a}, m_b{b}
{
    __simplify();
}

long double ration_t::eval() const
{
    return (long double)m_a / m_b;
}

ration_t ration_t::operator+(const ration_t &r)
{
    long long int base = std::lcm(m_b, r.m_b);
    return ration_t{
        m_a * base / m_b + r.m_a * base / r.m_b,
        base};
}
ration_t ration_t::operator-(const ration_t &r)
{
    long long int base = std::lcm(m_b, r.m_b);
    return ration_t{
        m_a * base / m_b - r.m_a * base / r.m_b,
        base};
}
ration_t ration_t::operator-()
{
    return ration_t{-m_a, m_b};
}
ration_t ration_t::operator*(const ration_t &r)
{
    return ration_t{m_a * r.m_a, m_b * r.m_b};
}
ration_t ration_t::operator/(const ration_t &r)
{
    return ration_t{m_a * r.m_b, m_b * r.m_a};
}

ration_t &ration_t::operator+=(const ration_t &r)
{
    long long int base = std::lcm(m_b, r.m_b);
    m_a = m_a * base / m_b + r.m_a * base / r.m_b;
    m_b = base;
    __simplify();
    return *this;
}
ration_t &ration_t::operator-=(const ration_t &r)
{
    long long int base = std::lcm(m_b, r.m_b);
    m_a = m_a * base / m_b - r.m_a * base / r.m_b;
    m_b = base;
    __simplify();
    return *this;
}
ration_t &ration_t::operator*=(const ration_t &r)
{
    m_a *= r.m_a;
    m_b *= r.m_b;
    __simplify();
    return *this;
}
ration_t &ration_t::operator/=(const ration_t &r)
{
    m_a *= r.m_b;
    m_b *= r.m_a;
    __simplify();
    return *this;
}

bool ration_t::operator==(const ration_t &r)
{
    return m_a == r.m_a && m_b == r.m_b;
}
bool ration_t::operator!=(const ration_t &r)
{
    return m_a != r.m_a || m_b != r.m_b;
}
bool ration_t::operator>=(const ration_t &r)
{
    return eval() >= r.eval();
}
bool ration_t::operator<=(const ration_t &r)
{
    return eval() <= r.eval();
}
bool ration_t::operator>(const ration_t &r)
{
    return eval() > r.eval();
}
bool ration_t::operator<(const ration_t &r)
{
    return eval() < r.eval();
}

std::string ration_t::to_latex()
{
    std::stringstream res;
    if (m_b == 1)
    {
        res << m_a;
        return res.str();
    }
    long long int t_a = m_a;
    if (m_a < 0)
    {
        t_a = -m_a;
        res << '-';
    }
    res << R"(\frac{)";
    res << t_a;
    res << "}{";
    res << m_b;
    res << '}';
    return res.str();
}

istream &operator>>(istream &in, ration_t &me)
{
    std::string buf;
    in >> buf;
    /* int sym = -1;
    size_t pos_minus = buf.find('-');
    if (pos_minus == std::string::npos)
    {
        sym = 1;
    } */
    size_t pos_backsplash = buf.find('/');
    if (pos_backsplash != std::string::npos)
    {
        me.m_a = atoll(buf.substr(0, pos_backsplash).c_str());
        me.m_b = atoll(buf.substr(pos_backsplash + 1).c_str());
    }
    else
    {
        me.m_a = atoll(buf.c_str());
        me.m_b = 1;
    }
    me.__simplify();
    return in;
}
ostream &operator<<(ostream &out, const ration_t &me)
{
    if (me.m_b == 1)
        out << me.m_a << '\t';
    else
        out << me.m_a << "/" << me.m_b << '\t';
    return out;
}

void ration_t::__simplify()
{
    if (m_a == 0)
    {
        m_b = 1;
        return;
    }
    if (m_b < 0)
    {
        m_a *= -1;
        m_b *= -1;
    }
    long long int base = std::gcd(m_a, m_b);
    m_a /= base;
    m_b /= base;
}
