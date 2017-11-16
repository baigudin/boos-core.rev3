/** 
 * System class of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SYSTEM_HPP_
#define SYSTEM_SYSTEM_HPP_

#include "api.System.hpp"

namespace system
{
    class System
    {
      
    public:
    
        /** 
         * Returns the operating system syscall interface.
         *
         * @return the operating system syscall interface.
         */      
        static ::api::System& call();    
      
    };
}
#endif // SYSTEM_SYSTEM_HPP_
