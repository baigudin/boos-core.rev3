/** 
 * System class of the operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SYSTEM_HPP_
#define KERNEL_SYSTEM_HPP_

#include "Types.hpp"

namespace api { class Toggle; }

namespace kernel
{
    class SystemTimerInterrupt;
    
    class System
    {
      
    public:
      
        /** 
         * Returns a current value of the running system in milliseconds.
         *
         * @return time in milliseconds.
         */
        static int64 getTimeMs();
        
        /** 
         * Returns a current value of the running system in nanoseconds.
         *
         * @return time in nanoseconds.
         */      
        static int64 getTimeNs();
        
        /**
         * Terminates the operating system execution.
         */
        static void terminate();
        
        /**
         * Initializes the resource.
         *
         * @return true if no errors have been occurred.
         */   
        static bool initialize();
        
        /**
         * Deinitializes the resource.
         */
        static void deinitialize();        
  
    private:
    
        /**
         * Tests if the module has been initialized.
         *
         * @return true if the module has been initialized successfully.
         */    
        static bool isInitialized();    
    
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x95277129;    
        
        /**
         * the module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;           
        
        /**
         * The module initialization stage (no boot).
         */
        static int32 stage_;
  
        /**
         * Hardware timer interrupt resource (no boot).
         */
        static SystemTimerInterrupt* interrupt_;
        
        /**
         * Global interrupt resource (no boot).
         */
        static ::api::Toggle* global_;    
  
    };
}
#endif // KERNEL_SYSTEM_HPP_
