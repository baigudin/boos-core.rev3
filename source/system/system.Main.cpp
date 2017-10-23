/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Main.hpp" 
#include "kernel.Thread.hpp"

using namespace kernel;

namespace system
{
    /**
     * The system method stated after the kernel start.
     * 
     * @return error code or zero.
     */   
    int32 Main::main()
    {
        int32 error = -1;
        Thread main;
        ::kernel::Thread thread(main);
        if( not thread.isConstructed() ) return error;
        thread.start();
        thread.join();
        return main.error();
    }
}
