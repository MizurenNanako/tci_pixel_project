#include "mat_t.h"

namespace tci
{
    template <class T>
    mat_t<T>::mat_t(size_t rows, size_t cols)
        : _rows{rows}, _cols{cols}
    {
        _vdata.resize(rows);
        std::for_each(_vdata.begin(), _vdata.end(),
                      [&cols](vec_t<T> &i)
                      { i.resize(cols); });
    }
    template <class T>
    mat_t<T>::mat_t(const std::initializer_list<vec_t<T>> &l)
    : _rows{l.size()}
    {
        _cols = 0;
        _vdata.resize(_rows);
        size_t k = 0;
        for (const vec_t<T> &i : l)
        {
            if (i.dimension() > _cols)
                _cols = i.dimension();
            _vdata[k++] = i;
        }
        for (vec_t<T> &i : _vdata)
        {
            i.resize(_cols);
        }
    }
    template <class T>
    mat_t<T>::~mat_t()
    {
        // we don't need to manage it
        // delete[] _vdata;
    }

    template <class T>
    vec_t<T> &mat_t<T>::operator[](size_t index)
    {
        // return _vdata->operator[](index);
        return _vdata[index];
    }
    template <class T>
    vec_t<T> *mat_t<T>::begin()
    {
        // return _vdata->begin();
        return _vdata.begin();
    }
    template <class T>
    vec_t<T> *mat_t<T>::end()
    {
        // return _vdata->end();
        return _vdata.end();
    }
}