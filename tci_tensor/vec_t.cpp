#include "vec_t.h"
#include <algorithm>

namespace tci
{
    TT CC::vec_t()
    {
        _pdata = new T[N];
    }
    TT CC::~vec_t()
    {
        delete[] _pdata;
    }
    TT CC::vec_t(std::initializer_list<T> l)
        : vec_t()
    {
        size_t i = 0;
        auto p = l.begin();
        auto d = l.end();
        while (i < N && p < d)
        {
            *(_pdata + i) = *p;
            ++i;
            ++p;
        }
    }
    TT CC::vec_t(CC &copy)
        : vec_t()
    {
        _pdata = std::copy(copy.begin(), copy.end(), _pdata);
    }
    TT CC::vec_t(CC &&move)
    {
        _pdata = move._pdata;
        move._pdata = nullptr;
    }

    TT T *CC::begin()
    {
        return _pdata;
    }
    TT T *CC::end()
    {
        return _pdata + N;
    }

    TT T &CC::operator[](size_t index)
    {
        if (index < N)
            return _pdata[index];
        throw ERR(std::out_of_range);
    }
    TT CC CC::operator+(const CC &rhs)
    {
        CC r;
        for (T *i = r.begin(), *j = begin(), *k = rhs.begin();
             i < r.end();
             ++i, ++j, ++k)
        {
            *i = *j + *k;
        }
        return r;
    }
    TT CC CC::operator-(const CC &rhs)
    {
        CC r;
        for (T *i = r.begin(), *j = begin(), *k = rhs.begin();
             i < r.end();
             ++i, ++j, ++k)
        {
            *i = *j - *k;
        }
        return r;
    }
    TT CC CC::operator*(const CC &rhs)
    {
        CC r;
        for (T *i = r.begin(), *j = begin(), *k = rhs.begin();
             i < r.end();
             ++i, ++j, ++k)
        {
            *i = *j * *k;
        }
        return r;
    }
    TT CC CC::operator*(const T &rhs)
    {
        CC r;
        for (T *i = r.begin(), *j = begin();
             i < r.end();
             ++i, ++j)
        {
            *i = *j * rhs;
        }
        return r;
    }
    TT CC CC::operator/(const T &rhs)
    {
        CC r;
        for (T *i = r.begin(), *j = begin();
             i < r.end();
             ++i, ++j)
        {
            *i = *j / rhs;
        }
        return r;
    }
    TT T CC::operator^(const CC &rhs)
    {
        T r;
        for (T *j = begin(), *k = rhs.begin();
             j < end();
             ++j, ++k)
        {
            r += *j * *k;
        }
        return r;
    }

    _T0 _T operator&(const _C2 &lhs, const _C2 &rhs)
    {
        // x0y1 – y0x1
        return lhs._pdata[0] * rhs._pdata[1] - lhs._pdata[1] * rhs._pdata[0];
    }
    _T0 _C3 operator&(const _C3 &lhs, const _C3 &rhs)
    {
        _C3 r;
        //[a1b2-a2b1，a2b0-a0b2，a0b1-a1b0]
        r._pdata[0] = lhs._pdata[1] * rhs._pdata[2] - lhs._pdata[2] * rhs._pdata[1];
        r._pdata[1] = lhs._pdata[2] * rhs._pdata[0] - lhs._pdata[0] * rhs._pdata[2];
        r._pdata[2] = lhs._pdata[0] * rhs._pdata[1] - lhs._pdata[1] * rhs._pdata[0];
        return r;
    }
}