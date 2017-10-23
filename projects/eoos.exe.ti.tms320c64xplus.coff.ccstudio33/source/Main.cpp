/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp"
#include "Object.hpp"
#include "system.Interrupt.hpp"
#include "system.InterruptTask.hpp"

class InterruptTask : public ::system::InterruptTask
{
    typedef ::system::InterruptTask Parent;

public: 
    
    InterruptTask() : Parent()
    {
    }

    virtual ~InterruptTask()
    {
    }    
    
    virtual void main()
    {
        asm(" nop");
        asm(" nop");
        asm(" nop");                
    }

};

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
    // Test an interrupt task
    InterruptTask interruptTask;
    system::Interrupt inerrupt(interruptTask, 51);
    inerrupt.jump();
    return 0;
}
