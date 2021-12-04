#include "vec_t.h"
#include <algorithm>

namespace tci
{
    TT CC::vec_t()
    {
        _pdata = new T[N]();
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

    TT template <size_t M>
    CC::vec_t(CM &copy)
    {
        _pdata = new T[N];
        isequal_const(N, M)
            ? std::copy(copy.begin(), copy.end(), _pdata)
            : std::copy(copy.begin(), copy.begin() + ((N < M) ? N : M), _pdata);
    }
    TT CC::vec_t(CC &&move)
    {
        _pdata = move._pdata;
        move._pdata = nullptr;
    }

    TT T *CC::begin() const
    {
        return _pdata;
    }
    TT T *CC::end() const
    {
        return _pdata + N;
    }

    TT T &CC::operator[](size_t index)
    {
        if (index < N)
            return _pdata[index];
        throw ERR(std::out_of_range);
    }

    // Liner add
    TT template <size_t M>
    auto CC::operator+(const CM &rhs) -> LargerVec_T<N, M>
    {
        LargerVec_T<N, M> r;
        T *i = r.begin(), *j = begin(), *k = rhs.begin();
        for (; j < end() && k < rhs.end(); ++i, ++j, ++k)
        {
            *i = *j + *k;
        }
        if (N > M)
        {
            for (; j < end(); ++i, ++j)
                *i = *j;
        }
        if (N < M)
        {
            for (; k < rhs.end(); ++i, ++k)
                *i = *k;
        }
        return r;
    }

    // Liner increase
    TT template <size_t M>
    CC &CC::operator+=(const CM &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i += *j;
        }
        return *this;
    }

    // Liner substrate
    TT template <size_t M>
    auto CC::operator-(const CM &rhs) -> LargerVec_T<N, M>
    {
        LargerVec_T<N, M> r;
        T *i = r.begin(), *j = begin(), *k = rhs.begin();
        for (; j < end() && k < rhs.end(); ++i, ++j, ++k)
        {
            *i = *j - *k;
        }
        if (N > M)
        {
            for (; j < end(); ++i, ++j)
                *i = *j;
        }
        if (N < M)
        {
            for (; k < rhs.end(); ++i, ++k)
                *i = -*k;
        }
        return r;
    }

    // Liner decrease
    TT template <size_t M>
    CC &CC::operator-=(const CM &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i -= *j;
        }
        return *this;
    }

    // Hadamard produce
    TT template <size_t M>
    auto CC::operator*(const CM &rhs) -> LargerVec_T<N, M>
    {
        LargerVec_T<N, M> r;
        for (T *i = r.begin(), *j = begin(), *k = rhs.begin();
             j < end() && k < rhs.end();
             ++i, ++j, ++k)
        {
            *i = *j * *k;
        }
        return r;
    }

    // Hadamard multiple
    TT template <size_t M>
    CC &CC::operator*=(const CM &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i *= *j;
        }
        return *this;
    }

#define _OP_NIB(op)                      \
    CC r;                                \
    for (T *i = r.begin(), *j = begin(); \
         i < r.end();                    \
         ++i, ++j)                       \
    {                                    \
        *i = *j op rhs;                  \
    }                                    \
    return r;
#define _OPEQ_NIB(op)                                          \
    std::for_each(begin(), end(), [&rhs](T &i) { i += rhs; }); \
    return *this;

    // Liner scaler add
    TT CC CC::operator+(const T &rhs){_OP_NIB(+)}
    // Liner scaler increase
    TT CC &CC::operator+=(const T &rhs){_OPEQ_NIB(+)}
    // Liner scaler substrate
    TT CC CC::operator-(const T &rhs){_OP_NIB(-)}
    // Liner scaler decrease
    TT CC &CC::operator-=(const T &rhs){_OPEQ_NIB(-)}
    // Liner scaler product
    TT CC CC::operator*(const T &rhs){_OP_NIB(*)}
    // Liner scaler multiple
    TT CC &CC::operator*=(const T &rhs){_OPEQ_NIB(*)}
    // Liner scaler devision
    TT CC CC::operator/(const T &rhs){_OP_NIB(/)}
    // Liner scaler devide
    TT CC &CC::operator/=(const T &rhs){_OPEQ_NIB(/)}

    // For-each operation
    TT CC CC::op_c(const T &rhs, std::function<T(T, T)> op)
    {
        CC r;
        for (T *i = r.begin(), *j = begin();
             i < r.end();
             ++i, ++j)
        {
            *i = op(*j, rhs);
        }
        return r;
    }
    // For-each operation
    TT CC &CC::op_eq(const T &rhs, std::function<T(T)> op)
    {
        std::for_each(begin(), end(), [&rhs, &op](T &i)
                      { op(i, rhs); });
        return *this;
    }

    // Inner product
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

    // Swap
    TT inline void CC::swap(CC &rhs)
    {
        std::swap(_pdata, rhs._pdata);
    }
    _TT void swap(_CC &lhs, _CC &rhs)
    {
        lhs.swap(rhs);
    }

    // Outer product, Euclidian, 2-dimension
    _T0 _T operator&(const _C2 &lhs, const _C2 &rhs)
    {
        // x0y1 – y0x1
        return lhs._pdata[0] * rhs._pdata[1] - lhs._pdata[1] * rhs._pdata[0];
    }
    // Outer product, Euclidian, 3-dimention
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

// Cancel all marcos
#undef _OP_NIB
#undef _OPEQ_NIB