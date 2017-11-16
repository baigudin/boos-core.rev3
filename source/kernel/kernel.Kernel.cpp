/** 
 * System class of the operating system kernel syscalls.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Kernel.hpp"
#include "kernel.Main.hpp"

namespace kernel
{
    /** 
     * Returns a kernel factory.
     *
     * @return a kernel factory.
     */      
    ::api::Kernel& Kernel::call()
    {
        return Main::getKernel();
    }   
}

