/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp"

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
    volatile bool exe = true;
    while(exe)
    {
        asm(" nop");
        asm(" nop");
        asm(" nop");                
    }
    return 0;
}
