/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MAIN_HPP_
#define SYSTEM_MAIN_HPP_

#include "api.Kernel.hpp"
#include "api.System.hpp"
#include "api.Toggle.hpp"

namespace system
{
    class Main
    {
    
    public:
   
        /**
         * The method which will be stated first.
         *        
         * @param kernel a kernel resources factory.
         * @return error code or zero.
         */
        static int32 main(::api::Kernel& kernel);
        
        /**
         * Returns the operating system factory resource.
         *        
         * @return the operating system interface.
         */
        static ::api::System& getSystem();
        
    private:
    
        /**
         * The operating system factory resource (no boot).
         */
        static ::api::System* system_;
        
        /**
         * The operating system global interrupt resource (no boot).
         */
        static ::api::Toggle* global_;         
        
        /**
         * The operating system kernel factory resource (no boot).
         */
        static ::api::Kernel* kernel_;

    };
}
#endif // SYSTEM_MAIN_HPP_
