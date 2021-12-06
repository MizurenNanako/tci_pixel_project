#include "vec_t.h"
#include <algorithm>
#include <iostream>

namespace tci
{
    template <class T>
    vec_t<T>::vec_t(size_t init_size)
        : _size{init_size}
    {
        _pdata = new T[_size]();
    }
    template <class T>
    vec_t<T>::~vec_t()
    {
        delete[] _pdata;
    }
    template <class T>
    vec_t<T>::vec_t(std::initializer_list<T> l)
        : vec_t(l.size())
    {
        T *p = _pdata;
        for (const T &i : l)
        {
            *(p++) = i;
        }
    }

    template <class T>
    vec_t<T>::vec_t(vec_t<T> &copy)
        : vec_t(copy._size)
    {
        std::copy(copy.begin(), copy.end(), _pdata);
    }
    template <class T>
    vec_t<T>::vec_t(vec_t<T> &&move)
    {
        _pdata = move._pdata;
        _size = move._size;
        move._pdata = nullptr;
    }

    template <class T>
    T *vec_t<T>::begin() const
    {
        return _pdata;
    }
    template <class T>
    T *vec_t<T>::end() const
    {
        return _pdata + _size;
    }

    template <class T>
    T &vec_t<T>::operator[](size_t index)
    {
        if (index < _size)
            return _pdata[index];
        throw new ERR(std::out_of_range, "Invalid Index");
    }

    // Liner add
    template <class T>
    vec_t<T> vec_t<T>::operator+(const vec_t<T> &rhs)
    {
        vec_t<T> r(MAX(_size, rhs._size));
        T *i = r.begin(), *j = begin(), *k = rhs.begin();
        for (; j < end() && k < rhs.end(); ++i, ++j, ++k)
        {
            *i = *j + *k;
        }
        if (_size > rhs._size)
        {
            for (; j < end(); ++i, ++j)
                *i = *j;
        }
        if (_size < rhs._size)
        {
            for (; k < rhs.end(); ++i, ++k)
                *i = *k;
        }
        return r;
    }

    // Liner increase
    template <class T>
    vec_t<T> &vec_t<T>::operator+=(const vec_t<T> &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i += *j;
        }
        return *this;
    }

    // Liner substrate
    template <class T>
    vec_t<T> vec_t<T>::operator-(const vec_t<T> &rhs)
    {
        vec_t<T> r(MAX(_size, rhs._size));
        T *i = r.begin(), *j = begin(), *k = rhs.begin();
        for (; j < end() && k < rhs.end(); ++i, ++j, ++k)
        {
            *i = *j - *k;
        }
        if (_size > rhs._size)
        {
            for (; j < end(); ++i, ++j)
                *i = *j;
        }
        if (_size < rhs._size)
        {
            for (; k < rhs.end(); ++i, ++k)
                *i = -*k;
        }
        return r;
    }

    // Liner decrease
    template <class T>
    vec_t<T> &vec_t<T>::operator-=(const vec_t<T> &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i -= *j;
        }
        return *this;
    }

    // Hadamard produce
    template <class T>
    vec_t<T> vec_t<T>::operator*(const vec_t<T> &rhs)
    {
        vec_t<T> r(MAX(_size, rhs._size));
        for (T *i = r.begin(), *j = begin(), *k = rhs.begin();
             j < end() && k < rhs.end();
             ++i, ++j, ++k)
        {
            *i = *j * *k;
        }
        return r;
    }

    // Hadamard multiple
    template <class T>
    vec_t<T> &vec_t<T>::operator*=(const vec_t<T> &rhs)
    {
        for (T *i = begin(), *j = rhs.begin();
             i < end() && j < rhs.end(); ++i, ++j)
        {
            *i *= *j;
        }
        return *this;
    }

#define _OP_NIB(op)                      \
    vec_t<T> r(_size);                   \
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
    template <class T>
    vec_t<T> vec_t<T>::operator+(const T &rhs) { _OP_NIB(+) }
    // Liner scaler increase
    template <class T>
    vec_t<T> &vec_t<T>::operator+=(const T &rhs) { _OPEQ_NIB(+) }
    // Liner scaler substrate
    template <class T>
    vec_t<T> vec_t<T>::operator-(const T &rhs) { _OP_NIB(-) }
    // Liner scaler decrease
    template <class T>
    vec_t<T> &vec_t<T>::operator-=(const T &rhs) { _OPEQ_NIB(-) }
    // Liner scaler product
    template <class T>
    vec_t<T> vec_t<T>::operator*(const T &rhs) { _OP_NIB(*) }
    // Liner scaler multiple
    template <class T>
    vec_t<T> &vec_t<T>::operator*=(const T &rhs) { _OPEQ_NIB(*) }
    // Liner scaler devision
    template <class T>
    vec_t<T> vec_t<T>::operator/(const T &rhs) { _OP_NIB(/) }
    // Liner scaler devide
    template <class T>
    vec_t<T> &vec_t<T>::operator/=(const T &rhs) { _OPEQ_NIB(/) }

    // For-each operation
    template <class T>
    vec_t<T> vec_t<T>::op_c(const T &rhs, std::function<T(T, T)> op)
    {
        vec_t<T> r;
        for (T *i = r.begin(), *j = begin();
             i < r.end();
             ++i, ++j)
        {
            *i = op(*j, rhs);
        }
        return r;
    }
    // For-each operation
    template <class T>
    vec_t<T> &vec_t<T>::op_eq(const T &rhs, std::function<T(T)> op)
    {
        std::for_each(begin(), end(), [&rhs, &op](T &i)
                      { op(i, rhs); });
        return *this;
    }

    // Inner product
    template <class T>
    T vec_t<T>::operator^(const vec_t<T> &rhs)
    {
        if (_size != rhs._size)
            throw new ERR(std::out_of_range, "Dimension Error On Cross Produce");
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
    template <class T>
    inline void vec_t<T>::swap(vec_t<T> &rhs)
    {
        std::swap(_pdata, rhs._pdata);
    }
    template <class T>
    void swap(vec_t<T> &lhs, vec_t<T> &rhs)
    {
        lhs.swap(rhs);
    }

    // Outer product, Euclidian, 2 or 3-dimension
    template <class _T>
    vec_t<_T> operator&(const vec_t<_T> &lhs, const vec_t<_T> &rhs)
    {
        if (lhs._size == 2 && rhs._size == 2)
            // x0y1 – y0x1
            return lhs._pdata[0] * rhs._pdata[1] - lhs._pdata[1] * rhs._pdata[0];
        if (lhs._size == 3 && rhs._size == 3)
        {
            vec_t<_T> r;
            //[a1b2-a2b1，a2b0-a0b2，a0b1-a1b0]
            r._pdata[0] = lhs._pdata[1] * rhs._pdata[2] - lhs._pdata[2] * rhs._pdata[1];
            r._pdata[1] = lhs._pdata[2] * rhs._pdata[0] - lhs._pdata[0] * rhs._pdata[2];
            r._pdata[2] = lhs._pdata[0] * rhs._pdata[1] - lhs._pdata[1] * rhs._pdata[0];
            return r;
        }
        throw new ERR(std::out_of_range, "Dimension Error On Cross Produce");
    }
}

// Cancel all marcos
#undef _OP_NIB
#undef _OPEQ_NIB