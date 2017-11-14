/** 
 * A central processing unit interrupt resource interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_PROCESSOR_INTERRUPT_HPP_
#define API_PROCESSOR_INTERRUPT_HPP_

#include "api.Interrupt.hpp"
#include "api.Task.hpp"
#include "api.ProcessorRegisters.hpp"

namespace api
{
    class ProcessorInterrupt : public ::api::Interrupt
    {
  
    public:
        
        /** 
         * Destructor.
         */                               
        virtual ~ProcessorInterrupt(){}
        
        /**
         * Sets interrupt source handler.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         * @return true if handler is set successfully.
         */      
        virtual bool setHandler(::api::Task& handler, int32 source) = 0;
        
        /**
         * Removes this interrupt source handler.
         */        
        virtual void removeHandler() = 0;
        
        /**
         * Sets new registers context for storing.
         * 
         * Method sets a new register context for storing the CPU registers to it.
         * This method may be called in an user interrupt handler, it means
         * given conxet will be restored by the context restore procedure.
         *
         * @param reg new registers context.
         */
        virtual void setContext(::api::ProcessorRegisters& reg) = 0;

        /**
         * Restores registers context for storing to the default.
         * 
         * Method restores default registers for storing the CPU registers to it.
         * This method may be called in an user interrupt handler, it means
         * the default conxet will be restored with the context restore procedure.
         */
        virtual void restoreContext() = 0;        
      
    };
}
#endif // API_PROCESSOR_INTERRUPT_HPP_
