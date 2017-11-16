/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"
#include "system.Main.hpp"

namespace system
{
    /** 
     * Returns the operating system syscall interface.
     *
     * @return the operating system syscall interface.
     */   
    ::api::System& System::call()
    {
        return Main::getSystem();    
    }

}
