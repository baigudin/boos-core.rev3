/** 
 * System types.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_TYPES_HPP_
#define SYSTEM_TYPES_HPP_

#include "library.Align.hpp"

namespace system
{
    typedef ::library::Align<int16>     Int16a;
    typedef ::library::Align<int32>     Int32a;
    typedef ::library::Align<int64>     Int64a;
    typedef ::library::Align<uint16>    Uint16a;
    typedef ::library::Align<uint32,3>  Uint24a;
    typedef ::library::Align<uint32>    Uint32a;
    typedef ::library::Align<uint64>    Uint64a;
}
 
#endif // SYSTEM_TYPES_HPP_
