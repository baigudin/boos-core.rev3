/** 
 * System class of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SYSTEM_HPP_
#define SYSTEM_SYSTEM_HPP_

#include "api.Kernel.hpp"

namespace system
{
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
         * Loads a program for executing.
         *
         * @param path a system path to a program.
         * @return true if program has been loaded successfully.
         */    
        static bool loadProgram(const char* path);
        
        /**
         * Terminates the operating system execution.
         */
        static void terminate();        
        
        /**
         * Returns an kernel factory of the operating system.
         *
         * @return a kernel factory.
         */
        static ::api::Kernel& getKernel();
        
        /**
         * Initializes the resource.
         *
         * @param kernel a kernel resources factory.              
         * @return true if no errors have been occurred.
         */   
        static bool initialize(::api::Kernel& kernel);

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
         * A kernel factory of the operating system (no boot).
         */
        static ::api::Kernel* kernel_;
  
    };
}
#endif // SYSTEM_SYSTEM_HPP_
