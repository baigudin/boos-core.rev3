/**
 * Factory of an operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_FACTORY_HPP_
#define KERNEL_FACTORY_HPP_

#include "api.Object.hpp"
#include "api.Semaphore.hpp"
#include "api.Interrupt.hpp"
#include "api.Task.hpp"

namespace kernel
{
    class Factory : public ::api::Object
    {
    
    public:
    
        /** 
         * Destructor.
         */
        virtual ~Factory(){}
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.   
         * @return new semaphore resource, or NULL if error has been occurred.
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits) = 0;
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         * @return new semaphore resource, or NULL if error has been occurred.         
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits, bool isFair) = 0;
        
        /**
         * Creates new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return new interrupt resource, or NULL if error has been occurred.
         */  
        virtual ::api::Interrupt* createInterrupt(::api::Task& handler, int32 source) = 0;
        
        /**
         * Returns a factory of an operating system kernel.
         *
         * @return a kernel factory, or NULL if error has been occurred.
         */
        static ::kernel::Factory* create();
 
    };
}
#endif // KERNEL_FACTORY_HPP_
