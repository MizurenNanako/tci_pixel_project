#ifndef _vector_t_h
#define _vector_t_h

#include "tcidef.h"
#include <initializer_list>

#define TT template <class T, size_t N>
#define CC vec_t<T, N>
#define CC1 vec_t<T, M>

namespace tci
{
    TT class vec_t
    {
    private:
        T *_pdata;

    public:
        vec_t();
        ~vec_t();

        vec_t(std::initializer_list<T> l);

        T *begin();
        T *end();

        T &operator[](size_t index);
        CC operator+(CC &rhs);
        CC operator-(CC &rhs);
    };
}

#endif //_vector_t_h