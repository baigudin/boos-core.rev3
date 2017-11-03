/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp" 
#include "system.Main.hpp" 
#include "system.MainThread.hpp"
#include "system.System.hpp" 

namespace system
{
    /**
     * The method which will be stated first.
     * 
     * @param config the operating system configuration.         
     * @param kernel a kernel resources factory.
     * @return error code or zero.
     */
    int32 Main::main(::api::Kernel& kernel)
    {
        int32 stage = 0;
        int32 error = -1;
        do
        {
            // Stage 1
            stage++;
            if( not ::system::System::initialize(kernel) ) break;      
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
                    thread.join();
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
