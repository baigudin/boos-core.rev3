/**
 * A kernel interface of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_KERNEL_HPP_
#define API_KERNEL_HPP_

#include "api.Object.hpp"
#include "api.Runtime.hpp"
#include "api.Value.hpp"
#include "api.Scheduler.hpp"
#include "api.Mutex.hpp"
#include "api.Semaphore.hpp"
#include "api.Interrupt.hpp"
#include "api.Task.hpp"
#include "api.Toggle.hpp"

namespace api
{
    class Kernel : public ::api::Object
    {
    
    public:
    
        /** 
         * Destructor.
         */
        virtual ~Kernel(){}
        
        /** 
         * Returns a default size of stack in bytes.
         *
         * @return a size of stack in bytes.
         */ 
        virtual int32 getStackSize() = 0;        
        
        /** 
         * Returns a kernel runtime environment.
         *
         * @return a kernel runtime environment.
         */      
        virtual ::api::Runtime& getRuntime() = 0;        
        
        /** 
         * Returns a value of a kernel running time in nanoseconds.
         *
         * @return a running time in nanoseconds.
         */      
        virtual ::api::Value<int64>& getExecutionTime() = 0;
        
        /** 
         * Returns a kernel scheduler.
         *
         * @return a kernel scheduler.
         */      
        virtual ::api::Scheduler& getScheduler() = 0;        
        
        /** 
         * Returns a global interrupt resource.
         *
         * @return a global interrupt resource.
         */      
        virtual ::api::Toggle& getGlobalInterrupt() = 0;

        /** 
         * Creates new mutex resource.
         *
         * @return new mutex resource, or NULL if error has been occurred.
         */      
        virtual ::api::Mutex* createMutex() = 0;
        
        /** 
         * Creates new unfair semaphore resource.
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

    };
}
#endif // API_KERNEL_HPP_
