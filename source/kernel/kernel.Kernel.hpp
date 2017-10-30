/** 
 * System class of the operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_KERNEL_HPP_
#define KERNEL_KERNEL_HPP_

#include "api.Kernel.hpp"
#include "api.Toggle.hpp"

namespace kernel
{
    class Kernel
    {
      
    public:
      
        /** 
         * Returns the kernel factory.
         *
         * @return the kernel factory.
         */      
        static ::api::Kernel& getKernel();        
        
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
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;           
        
        /**
         * The module initialization stage (no boot).
         */
        static int32 stage_;
        
        /**
         * Global interrupt resource (no boot).
         */
        static ::api::Toggle* global_;    
        
        /**
         * The kernel factory resource (no boot).
         */
        static ::api::Kernel* kernel_;
  
    };
}
#endif // KERNEL_KERNEL_HPP_
