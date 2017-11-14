/**
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_MUTEX_HPP_
#define KERNEL_MUTEX_HPP_

#include "Object.hpp"
#include "api.Mutex.hpp"
#include "api.Thread.hpp"
#include "kernel.Kernel.hpp"
#include "library.LinkedList.hpp"

namespace kernel
{  
    class Mutex : public ::Object<>, public ::api::Mutex
    {
        typedef ::Object<> Parent;    
  
    public:
  
        /** 
         * Constructor.
         */    
        Mutex() : Parent(),
            isConstructed_ (getConstruct()),
            scheduler_     (NULL),
            thread_        (NULL),                        
            id_            (UNLOCKED_ID),
            count_         (1),
            fifo_          (NULL){    
            setConstruct( construct() );    
        }

        /** 
         * Destructor.
         */      
        virtual ~Mutex()
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
         * Locks the mutex.
         *
         * @return true if the mutex is lock successfully.
         */      
        virtual bool lock()
        {
            if( not isConstructed_ ) return false;
            bool is = thread_->disable();
            // The first checking for acquiring available permits of the mutex
            if( count_ - 1 >= 0 && fifo_.isEmpty() )
            {
                // Decrement the number of available permits
                count_ -= 1;
                // Go through the mutex to critical section
                return thread_->enable(is, true);      
            }
            ::api::Thread& thread = scheduler_->getCurrentThread();            
            // Add current thread to the queue tail
            if( fifo_.add(&thread) == false ) return thread_->enable(is, false);
            while(true)
            {
                // Block current thread on the mutex and switch to another thread
                thread.block(*this);
                // Test if head thread is current thread
                if(fifo_.peek() != &thread) continue;
                // Test available permits for no breaking the fifo queue by removing
                if(count_ - 1 < 0) continue;
                // Decrement the number of available permits
                count_ -= 1;        
                // Remove head thread
                return thread_->enable( is, fifo_.remove() );
            }    
        }
        
        /**
         * Unlocks the mutex.
         */      
        virtual void unlock()
        {
            if( not isConstructed_ ) return;
            bool is = thread_->disable();
            count_ += 1;
            thread_->enable(is);  
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
            bool res = count_ > 0 ? false : true;
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
        Mutex(const Mutex& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Mutex& operator =(const Mutex& obj);      
        
        /**
         * The unlocked id.
         */
        static const int64 UNLOCKED_ID = -1;    
        
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
         * The identifier of locked thread.
         */
        int64 id_;
        
        /**
         * The mutex counter.
         */
        int32 count_;
        
        /** 
         * Queue of locked threads.
         */     
        ::library::LinkedList< ::api::Thread* > fifo_;
  
    };
}
#endif // KERNEL_MUTEX_HPP_
