#ifndef _tcidef_h
#define _tcidef_h

#include <cstddef>
#include <stdexcept>

#define ERR(EXCEPTION) \
    new EXCEPTION { __FILE__ + __func__ }

namespace tci
{
    const size_t _BUFLEN = 16;
    
    template <bool Condition, typename Then, typename Else>
    struct IfThenElse;

    template <typename Then, typename Else>
    struct IfThenElse<true, Then, Else>
    {
        using Result = Then;
    };

    template <typename Then, typename Else>
    struct IfThenElse<false, Then, Else>
    {
        using Result = Else;
    };
}

#endif //_tcidef_h