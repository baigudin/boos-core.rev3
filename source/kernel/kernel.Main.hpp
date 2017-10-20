/** 
 * The operating system kernel main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_MAIN_HPP_
#define KERNEL_MAIN_HPP_

#include "Types.hpp"

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
        
    };
}
#endif // KERNEL_MAIN_HPP_
