/** 
 * A central processing unit registers resource interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_PROCESSOR_REGISTERS_HPP_
#define API_PROCESSOR_REGISTERS_HPP_

#include "api.Object.hpp"
#include "api.Stack.hpp"

namespace api
{
    class ProcessorRegisters : public ::api::Object
    {
      
    public:
      
        /** 
         * Destructor.
         */    
        virtual ~ProcessorRegisters(){}
        
        /** 
         * Initializes the CPU registers.
         *
         * The method is mostly used for restoring from an interrupt service routine.
         *
         * @param stack    a routine stack.
         * @param entry    a routine entry address.
         * @param argument a routine argument.
         */  
        virtual void setInitialization(::api::Stack<int64>& stack, void* entry, int32 argument) = 0;
        
        /** 
         * Returns a pointer to the first register of CPU registers context.
         *
         * @return memory address of registers order, or NULL if error has been occurred.
         */    
        virtual void* getRegisters() = 0;
      
    };
}
#endif // API_PROCESSOR_REGISTERS_HPP_
