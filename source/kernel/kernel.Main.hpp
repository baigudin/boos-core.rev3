/** 
 * The operating system kernel main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_MAIN_HPP_
#define KERNEL_MAIN_HPP_

#include "api.Kernel.hpp"

namespace kernel
{
    class Main
    {
    
    public:
   
        /**
         * The method which will be stated first.
         * 
         * @return error code or zero.
         */
        static int32 main();
        
        /**
         * Returns the kernel factory resource.
         *        
         * @return the kernel interface.
         */
        static ::api::Kernel& getKernel();        
        
    private:
        
        /**
         * The kernel factory resource (no boot).
         */
        static ::api::Kernel* kernel_;
        
    };
}
#endif // KERNEL_MAIN_HPP_
