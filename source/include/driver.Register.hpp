/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Sergey Baigudin
 */
#ifndef DRIVER_REGISTER_HPP_
#define DRIVER_REGISTER_HPP_

#include "api.Object.hpp"
#include "api.Stack.hpp"
#include "api.Toggle.hpp"
#include "Configuration.hpp"

namespace driver
{
    class Register : public ::api::Object
    {
      
    public:
      
        /** 
         * Destructor.
         */    
        virtual ~Register(){}
        
        /** 
         * Initializes the CPU registers.
         *
         * Usually, this method is used for normally restoring 
         * from some interrupt service routines. 
         *
         * @param stack a stack.
         * @param entry router entry point.
         * @param arg1  first router argument.
         * @param arg2  second router argument.     
         */  
        virtual void setInitialization(::api::Stack<int64>& stack, 
                                       int32 entry, 
                                       int32 arg1, int32 arg2) = 0;
        
        /** 
         * Returns a pointer to the first register of CPU context.
         *
         * @return memory address of registers order, or NULL 
         *         if error has been occurred.
         */    
        virtual void* getRegisters() = 0;
        
        /**
         * Returns the register interface of a target processor.
         *
         * @return target processor register interface, or NULL 
         *         if error has been occurred.
         */
        static ::driver::Register* create();
        
        /** 
         * Allows an access to protected memory mapped registers.
         */    
        static void allow();
        
        /** 
         * Protects an access to protected memory mapped registers.
         */    
        static void protect();    
        
        /**
         * Initializes the driver.
         *
         * @param config a target processor configuration.
         * @return true if no errors have been occurred.
         */   
        static bool initialize(const ::Configuration config);
        
        /**
         * Deinitializes the driver.
         */
        static void deinitialize();    
      
    };
}
#endif // DRIVER_REGISTER_HPP_
