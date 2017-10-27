/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Main.hpp" 
#include "system.System.hpp" 
#include "system.Thread.hpp"

namespace system
{
    /**
     * The system method stated after the kernel start.
     * 
     * @return error code or zero.
     */   
    int32 Main::main()
    {
        int32 stage = 0;
        int32 error = -1;
        do
        {
            // Stage 1
            stage++;
            if( not ::system::System::initialize() ) break;      
            // Stage 2
            stage++;
            if( not ::system::Thread::initialize() ) break;              
            // Stage complete
            stage = -1;
            {
                MainThread thread;
                if( thread.isConstructed() )
                {
                    thread.start();
                    thread.yield();
                    error = thread.error();            
                }
            }

        }
        while(false);
        switch(stage)
        {
            default:
            case  2: ::system::Thread::deinitialize();            
            case  1: ::system::System::deinitialize();
            case  0: break;
        }
        return error;
    }
}
