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
#include "system.TaskBase.hpp"

class TestInterrupt : public ::system::TaskBase
{
    typedef ::system::TaskBase Parent;

public: 
    
    TestInterrupt() : Parent()
    {
    }

    virtual ~TestInterrupt()
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
    TestInterrupt testInterrupt;
    system::Interrupt inerrupt(testInterrupt, 51);
    inerrupt.jump();
    return 0;
}
