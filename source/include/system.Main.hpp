/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MAIN_HPP_
#define SYSTEM_MAIN_HPP_

#include "Configuration.hpp"
#include "api.Kernel.hpp"

namespace system
{
    class Main
    {
    
    public:
   
        /**
         * The method which will be stated first.
         * 
         * @param config the operating system configuration.         
         * @param kernel a kernel resources factory.
         * @return error code or zero.
         */
        static int32 main(const ::Configuration config, ::api::Kernel& kernel);

    };
}
#endif // SYSTEM_MAIN_HPP_
