#ifndef _mat_t_h
#define _mat_t_h

#include "vec_t.h"

namespace tci
{
    template <class T>
    class mat_t
    {
    private:
        vec_t<vec_t<T>> _vdata{0};
        size_t _rows;
        size_t _cols;

    public:
        explicit mat_t(size_t rows = 0, size_t cols = 0);
        mat_t(const std::initializer_list<vec_t<T>> &l);
        ~mat_t();

        vec_t<T> &operator[](size_t index);
        vec_t<T> *begin();
        vec_t<T> *end();
    };
}

#include "mat_t.cpp"

#endif //_mat_t_h