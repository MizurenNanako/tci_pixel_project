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
    TT CC CC::operator+(CC &rhs)
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
    TT CC CC::operator-(CC &rhs)
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
    TT CC CC::operator*(CC &rhs)
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
    TT T CC::operator^(CC &rhs)
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
}