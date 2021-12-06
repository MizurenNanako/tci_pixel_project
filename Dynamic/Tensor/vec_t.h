#ifndef _vec_t_h
#define _vec_t_h

#include "../../Common/tcidef.h"
#include <initializer_list>
#include <functional>

namespace tci
{
    template <class T>
    class vec_t
    {
    private:
    protected:
        T *_pdata;
        size_t _size;

    public:
        vec_t(size_t init_size = 1);
        ~vec_t();

        vec_t(std::initializer_list<T> l);
        vec_t(vec_t<T> &copy);
        vec_t(vec_t<T> &&move);

        T *begin() const;
        T *end() const;

        T &operator[](size_t index);

        // Liner add
        vec_t<T> operator+(const vec_t<T> &rhs);
        // Liner increase
        vec_t<T> &operator+=(const vec_t<T> &rhs);

        // Liner substrate
        vec_t<T> operator-(const vec_t<T> &rhs);
        // Liner decrease
        vec_t<T> &operator-=(const vec_t<T> &rhs);

        // Hadamard produce
        vec_t<T> operator*(const vec_t<T> &rhs);
        // Hadamard multiple
        vec_t<T> &operator*=(const vec_t<T> &rhs);

        // Liner scaler add
        vec_t<T> operator+(const T &rhs);
        // Liner scaler increase
        vec_t<T> &operator+=(const T &rhs);
        // Liner scaler substrate
        vec_t<T> operator-(const T &rhs);
        // Liner scaler decrease
        vec_t<T> &operator-=(const T &rhs);
        // Liner scaler product
        vec_t<T> operator*(const T &rhs);
        // Liner scaler multiple
        vec_t<T> &operator*=(const T &rhs);
        // Liner scaler devision
        vec_t<T> operator/(const T &rhs);
        // Liner scaler devide
        vec_t<T> &operator/=(const T &rhs);

        // For-each calculation
        vec_t<T> op_c(const T &rhs, std::function<T(T, T)> op);
        // For-each operation
        vec_t<T> &op_eq(const T &rhs, std::function<T(T)> op);

        // Inner product
        T operator^(const vec_t<T> &rhs);

        // Swap
        inline void swap(vec_t<T> &rhs);
        template <class _T>
        friend void swap(vec_t<_T> &lhs, vec_t<_T> &rhs);

        // special

        // Outer product, Euclidian, 2-dimension
        template <class _T>
        friend vec_t<_T> operator&(const vec_t<_T> &lhs, const vec_t<_T> &rhs);
        // Outer product, Euclidian, 3-dimention
        template <class _T>
        friend vec_t<_T> operator&(const vec_t<_T> &lhs, const vec_t<_T> &rhs);
    };
}

#include "vec_t.cpp"

#endif //_vec_t_h