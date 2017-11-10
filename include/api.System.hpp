/**
 * The opearating system syscall interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_SYSTEM_HPP_
#define API_SYSTEM_HPP_

#include "api.Object.hpp"
#include "api.Kernel.hpp"

namespace api
{
    class System : public ::api::Object    
    {
      
    public:
  
        /**
         * Destructor.
         */
        virtual ~System(){}
        
        /** 
         * Returns the operating system kernel interface.
         *
         * @return the operating system kernel interface.
         */      
        virtual ::api::Kernel& getKernel() = 0;
        
        /**
         * Returns running time of the operating system in milliseconds.
         *
         * @return time in milliseconds.
         */
        virtual int64 getTimeMs() = 0;
           
        /**
         * Returns running time of the operating system in nanoseconds.
         *
         * @return time in nanoseconds.
         */
        virtual int64 getTimeNs() = 0;
        
        /**
         * Terminates the operating system execution.
         *
         * @param status a termination status.
         */
        virtual void terminate() = 0;

    };
}
#endif // API_SYSTEM_HPP_
