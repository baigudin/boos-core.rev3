/**
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SEMAPHORE_HPP_
#define KERNEL_SEMAPHORE_HPP_

#include "kernel.Object.hpp"
#include "api.Semaphore.hpp"
#include "api.Thread.hpp"
#include "kernel.Kernel.hpp"
#include "library.LinkedList.hpp"

namespace kernel
{
    class Semaphore : public ::kernel::Object, public ::api::Semaphore
    {
        typedef ::kernel::Object Parent;
     
    public:
  
        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.   
         */      
        Semaphore(int32 permits) : Parent(),
            isConstructed_ (getConstruct()),
            scheduler_     (NULL),
            thread_        (NULL),            
            permits_       (permits),
            isFair_        (false),    
            fifo_          (NULL){
            setConstruct( construct() );  
        }
        
        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         */      
        Semaphore(int32 permits, bool isFair) : Parent(),
            isConstructed_ (getConstruct()),  
            scheduler_     (NULL),
            thread_        (NULL),              
            permits_       (permits),
            isFair_        (isFair),
            fifo_          (NULL){
            setConstruct( construct() );  
        }

        /** 
         * Destructor.
         */
        virtual ~Semaphore()
        {
        }        
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }        
        
        /**
         * Acquires one permit from this semaphore.
         *
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire()
        {
            return acquire(1);
        }        

        /**
         * Acquires the given number of permits from this semaphore.
         *
         * @param permits the number of permits to acquire.
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire(int32 permits)
        {
            if( not isConstructed_ ) return false;
            bool is = thread_->disable();
            ::api::Thread& thread = scheduler_->getCurrentThread();
            // Acquire fairly
            if(isFair_)
            {
                // The first checking for acquiring available permits of the semaphore
                if( permits_ - permits >= 0 && fifo_.isEmpty() )
                {
                    // Decrement the number of available permits
                    permits_ -= permits;
                    // Go through the semaphore to critical section
                    return thread_->enable(is, true);      
                }
                // Add current thread to the queue tail
                if( fifo_.add(&thread) == false ) return thread_->enable(is, false);
                while(true)
                {
                    // Block current thread on the semaphore and switch to another thread
                    thread.block(*this);
                    // Test if head thread is current thread
                    if(fifo_.peek() != &thread) continue;
                    // Test available permits for no breaking the fifo queue by removing
                    if(permits_ - permits < 0) continue;
                    // Decrement the number of available permits
                    permits_ -= permits;        
                    // Remove head thread
                    return thread_->enable( is, fifo_.remove() );
                }    
            }
            // Acquire unfairly
            else
            {
                while(true)
                {
                    // Check about available permits in the semaphoring critical section
                    if( permits_ - permits >= 0 )
                    {
                        // Decrement the number of available permits
                        permits_ -= permits;
                        // Go through the semaphore to critical section
                        return thread_->enable(is, true);
                    }
                    // Block current thread on the semaphore and switch to another thread
                    thread.block(*this);      
                }  
            }
        }        
        
        /**
         * Releases one permit.
         */
        virtual void release()
        {
            release(1);
        }    
        
        /**
         * Releases the given number of permits.
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits)
        {
            if( not isConstructed_ ) return;
            bool is = thread_->disable();
            permits_ += permits;
            thread_->enable(is);
        }  
        
        /**
         * Tests if this semaphore is fair.
         *
         * @return true if this semaphore has fairness set true.
         */  
        virtual bool isFair() const
        {
            return isFair_;
        }
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked()
        {
            if( not isConstructed_ ) return false;
            bool is = thread_->disable();
            bool res = permits_ > 0 ? false : true;
            return thread_->enable(is, res);
        }
  
    private:   
        
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            if( not isConstructed_ ) return false;
            if( not fifo_.isConstructed() ) return false;
            scheduler_ = &Kernel::call().getScheduler();
            thread_ = &scheduler_->toggle();
            return true;
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Semaphore(const Semaphore& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Semaphore& operator =(const Semaphore& obj);     
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;

        /**
         * The kernel threads scheduler.
         */        
        ::api::Scheduler* scheduler_;
        
        /**
         * The kernel threads switching toggle.
         */        
        ::api::Toggle* thread_;
        
        /**
         * Number of permits for acquiring this semaphore.
         */
        int32 permits_;
        
        /**
         * Semaphore fair flag.
         */    
        bool isFair_;
        
        /** 
         * Queue of locked threads.
         */     
        ::library::LinkedList< ::api::Thread* > fifo_;
  
    };  
}
#endif // KERNEL_SEMAPHORE_HPP_
