#ifndef _vector_t_h
#define _vector_t_h

#include "tcidef.h"
#include <initializer_list>
#include <functional>

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
    private:
        template <size_t A, size_t B>
        using SmallerVec_T =
            typename IfThenElse<(A < B),
                                vec_t<T, A>,
                                vec_t<T, B>>::Result;
        template <size_t A, size_t B>
        using LargerVec_T =
            typename IfThenElse<(A > B),
                                vec_t<T, A>,
                                vec_t<T, B>>::Result;

    protected:
        T *_pdata;

    public:
        vec_t();
        ~vec_t();

        vec_t(std::initializer_list<T> l);
        vec_t(CC &copy);
        vec_t(CC &&move);

        T *begin() const;
        T *end() const;

        T &operator[](size_t index);

        // Liner add
        template <size_t M>
        auto operator+(const CM &rhs) -> LargerVec_T<N, M>;
        // Liner increase
        template <size_t M>
        CC &operator+=(const CM &rhs);

        // Liner substrate
        template <size_t M>
        auto operator-(const CM &rhs) -> LargerVec_T<N, M>;
        // Liner decrease
        template <size_t M>
        CC &operator-=(const CM &rhs);

        // Hadamard produce
        template <size_t M>
        auto operator*(const CM &rhs) -> LargerVec_T<N, M>;
        // Hadamard multiple
        template <size_t M>
        CC &operator*=(const CM &rhs);

        // Liner scaler add
        CC operator+(const T &rhs);
        // Liner scaler increase
        CC &operator+=(const T &rhs);
        // Liner scaler substrate
        CC operator-(const T &rhs);
        // Liner scaler decrease
        CC &operator-=(const T &rhs);
        // Liner scaler product
        CC operator*(const T &rhs);
        // Liner scaler multiple
        CC &operator*=(const T &rhs);
        // Liner scaler devision
        CC operator/(const T &rhs);
        // Liner scaler devide
        CC &operator/=(const T &rhs);

        // For-each calculation
        CC op_c(const T &rhs, std::function<T(T, T)> op);
        // For-each operation
        CC &op_eq(const T &rhs, std::function<T(T)> op);

        // Inner product
        T operator^(const CC &rhs);

        // Swap
        inline void swap(CC &rhs);

        // special

        // Outer product, Euclidian, 2-dimension
        _T0 friend _T operator&(const _C2 &lhs, const _C2 &rhs);
        // Outer product, Euclidian, 3-dimention
        _T0 friend _C3 operator&(const _C3 &lhs, const _C3 &rhs);
    };
}

#include "vec_t.cpp"

#endif //_vector_t_h