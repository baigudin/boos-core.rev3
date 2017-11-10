/** 
 * System class of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SYSTEM_HPP_
#define SYSTEM_SYSTEM_HPP_

#include "api.System.hpp"
#include "api.Kernel.hpp"

namespace system
{
    class System
    {
      
    public:
    
        /** 
         * Returns the operating system syscall interface.
         *
         * @return the operating system syscall interface.
         */      
        static ::api::System& call();    
      
        /**
         * Initializes the operating system.
         *
         * @param kernel a kernel resources factory.              
         * @return true if no errors have been occurred.
         */   
        static bool initialize(::api::Kernel& kernel);

        /**
         * Deinitializes the operating system.
         */
        static void deinitialize();        
  
    private:
    
        /**
         * Tests if the operating system has been initialized.
         *
         * @return true if the operating system has been initialized successfully.
         */    
        static bool isInitialized();    
    
        /**
         * The operating system initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x95277129;    
        
        /**
         * The operating system has been initialized successfully (no boot).
         */
        static int32 isInitialized_;           
        
        /**
         * The operating system initialization stage (no boot).
         */
        static int32 stage_;
        
        /**
         * The operating system factory resource (no boot).
         */
        static ::api::System* system_;
  
    };
}
#endif // SYSTEM_SYSTEM_HPP_
