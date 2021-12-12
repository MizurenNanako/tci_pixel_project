#include "mat_t.h"

namespace tci
{
    template <class T>
    mat_t<T>::mat_t(size_t rows, size_t cols)
        : _rows{rows}, _cols{cols}
    {
        _pdata.resize(rows);
        std::for_each(_pdata.begin(), _pdata.end(), [const size_t & cols](vec_t<T> &i)
                      { i.resize(cols); });
    }
    template <class T>
    mat_t<T>::mat_t(const std::initializer_list<vec_t<T>> &l)
    {
        size_t maxlen = 0;
        _pdata = new vec_t<T>[l.size()](0);
        for (vec_t<T> &i : l)
        {
            i.dimension() > maxlen ? maxlen = i.dimension(): ;
        }
    }
    template <class T>
    mat_t<T>::~mat_t()
    {
        delete[] _pdata;
    }

    template <class T>
    vec_t<T> &mat_t<T>::operator[](size_t index)
    {
        return _pdata->operator[](index);
    }
    template <class T>
    vec_t<T> *mat_t<T>::begin()
    {
        return _pdata->begin();
    }
    template <class T>
    vec_t<T> *mat_t<T>::end()
    {
        return _pdata->end();
    }
}