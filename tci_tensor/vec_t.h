#ifndef _vector_t_h
#define _vector_t_h

#include "tcidef.h"
#include <initializer_list>

#define TT template <class T, size_t N>
#define T0 template <class T>
#define _T0 template <class _T>
#define CC vec_t<T, N>
#define CM vec_t<T, M>
#define C2 vec_t<T, 2>
#define C3 vec_t<T, 3>
#define _C2 vec_t<_T, 2>
#define _C3 vec_t<_T, 3>

namespace tci
{
    TT class vec_t
    {
    protected:
        T *_pdata;

    public:
        vec_t();
        ~vec_t();

        vec_t(std::initializer_list<T> l);
        vec_t(CC &copy);
        vec_t(CC &&move);

        T *begin();
        T *end();

        T &operator[](size_t index);
        CC operator+(const CC &rhs); // Liner add
        CC operator-(const CC &rhs); // Liner substrate
        CC operator*(const CC &rhs); // Hadamard product
        CC operator*(const T &rhs);  // Liner scaler product
        CC operator/(const T &rhs);  // Liner scaler devision
        T operator^(const CC &rhs);  // Inner product

        // special
        // Outer product, Euclidian
        // 2-dimension
        _T0 friend _T operator&(const _C2 &lhs, const _C2 &rhs);
        // 3-dimention
        _T0 friend _C3 operator&(const _C3 &lhs, const _C3 &rhs);
    };
}

#include "vec_t.cpp"

#endif //_vector_t_h