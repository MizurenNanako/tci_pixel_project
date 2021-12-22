#include "vec_t.h"
#include <algorithm>
#include <iostream>

namespace tci
{
    template <class T>
    inline void vec_t<T>::_allocate()
    {
        if (_max_size)
            _pdata = (T *)malloc(sizeof(T[_max_size]));
        else
            _pdata = nullptr;
    }

    template <class T>
    inline void vec_t<T>::_deallocate()
    {
        if (!_max_size)
            return;
        free(_pdata);
        _pdata = nullptr;
    }

    template <class T>
    vec_t<T>::vec_t(size_t init_size)
        : _max_size{init_size}, _size{init_size}
    {
        _allocate();
        new (_pdata) T[_max_size];
    }
    template <class T>
    vec_t<T>::~vec_t()
    {
        if (_max_size)
            delete[] _pdata;
    }
    template <class T>
    vec_t<T>::vec_t(const std::initializer_list<T> &l)
        : _max_size{l.size()}, _size{l.size()}
    {
        _allocate();
        T *p = _pdata;
        for (const T &i : l)
        {
            new (p++) T{i};
        }
    }

    template <class T>
    vec_t<T>::vec_t(vec_t<T> &copy)
        : _max_size{copy._size}, _size{copy._size}
    {
        _allocate();
        std::copy(copy.begin(), copy.end(), _pdata);
    }
    template <class T>
    vec_t<T>::vec_t(vec_t<T> &&move)
    {
        _pdata = move._pdata;
        _size = move._size;
        _max_size = move._max_size;
        move._pdata = nullptr;
        move._size = move._max_size = 0;
    }

    template <class T>
    vec_t<T> &vec_t<T>::operator=(const vec_t<T> &rhs)
    {
        if (_max_size >= rhs._size)
        {
            std::copy_n(rhs.begin(), rhs._size, _pdata);
            _size = rhs._size;
        }
        else // _max_size < rhs._size
        {
            delete[] _pdata;
            _max_size = _size = rhs._size;
            _allocate();
            std::copy_n(rhs.begin(), _max_size, _pdata);
        }
        return *this;
    }

    template <class T>
    vec_t<T> &vec_t<T>::operator=(vec_t<T> &&rhs)
    {
        _size = rhs._size;
        _max_size = rhs._max_size;
        std::swap(_pdata, rhs._pdata);
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

    // Index access
    template <class T>
    T &vec_t<T>::operator[](size_t index)
    {
        if (index < _size)
            return _pdata[index];
        throw new ERR(std::out_of_range, "Invalid Index");
    }
    // Read access
    template <class T>
    T vec_t<T>::at(size_t index)
    {
        if (index < _size)
            return _pdata[index];
        throw new ERR(std::out_of_range, "Invalid Index");
    }
    // Write access
    template <class T>
    vec_t<T> &vec_t<T>::set(size_t index, T &value)
    {
        if (index < _size)
            _pdata[index] = value;
        throw new ERR(std::out_of_range, "Invalid Index");
        return *this;
    }
    // Dimension
    template <class T>
    inline size_t vec_t<T>::dimension()
    {
        return _size;
    }
    // Resize
    template <class T>
    vec_t<T> &vec_t<T>::resize(size_t dim)
    {
        if (dim)
        {
            if (this)
            {
                if (_max_size < dim)
                {
                    // allocate space
                    T *__pdata = (T *)malloc(sizeof(T[dim]));
                    // initialize the data part
                    T *i = nullptr, *j = nullptr;
                    for (i = __pdata, j = _pdata;
                         (j < _pdata + _size);
                         ++i, ++j)
                    {
                        new (i) T{*j};
                    }
                    // initialize the rest part
                    for (; (i < __pdata + dim); ++i)
                    {
                        new (i) T;
                    }
                    // this is the old code ignoring class type ↓↓↓
                    // std::copy_n(_pdata, MIN(_size, dim), __pdata);
                    // delete buffer, done
                    std::swap(_pdata, __pdata);
                    delete[] __pdata;
                }
            }
            else
            {
                vec_t(dim);
            }
            _size = dim;
        }
        /* else // dim == 0
        {
            if (_max_size)
                delete[] _pdata;
            _pdata = nullptr;
        } */
        return *this;
    }
    // Sum
    template <class T>
    T vec_t<T>::sum()
    {
        T res{0};
        std::for_each(begin(), end(), [&res](T &i)
                      { res += i; });
        return res;
    }
    // Normalize
    template <class T>
    vec_t<T> vec_t<T>::normalize()
    {
        return *this / sum();
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
        std::swap(_size, rhs._size);
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