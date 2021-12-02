#ifndef _tcidef_h
#define _tcidef_h

#include <cstddef>
#include <stdexcept>

#define ERR(EXCEPTION) \
    new EXCEPTION { __FILE__ + __func__ }

namespace tci
{
    const size_t _BUFLEN = 16;
}

#endif //_tcidef_h