#ifndef _tcidef_h
#define _tcidef_h

#include <cstddef>
#include <stdexcept>

#define ERR(EXCEPTION, STR) \
    EXCEPTION { std::string{STR " in "} + __func__ + " " __FILE__ "\n" }

#define MAX(a, b) \
    (((a) > (b)) ? (a) : (b))

namespace tci
{
    const size_t _BUFLEN = 16;

    template <typename T>
    constexpr bool isequal_const(T N, T M)
    {
        return N == M;
    }

    template <bool Condition, typename Then, typename Else>
    struct TypeIf;

    template <typename Then, typename Else>
    struct TypeIf<true, Then, Else>
    {
        using Result = Then;
    };

    template <typename Then, typename Else>
    struct TypeIf<false, Then, Else>
    {
        using Result = Else;
    };
}

#endif //_tcidef_h
