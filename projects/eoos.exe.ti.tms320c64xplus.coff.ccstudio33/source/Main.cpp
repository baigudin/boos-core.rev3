/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp"
#include "system.Interrupt.hpp"

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
    volatile bool exe = true;
    bool is[2];
    api::Toggle& global = system::Interrupt::global();
    while(exe)
    {
        asm(" nop");
        is[0] = global.disable();
        is[1] = global.disable();        
        asm(" nop");
        asm(" nop");
        asm(" nop");                
        global.enable(is[1]);
        global.enable(is[0]);
        asm(" nop");                
    }
    return 0;
}
