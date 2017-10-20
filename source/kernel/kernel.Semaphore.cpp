/** 
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Semaphore.hpp"
#include "kernel.Thread.hpp"
#include "driver.Interrupt.hpp"

namespace kernel
{
    typedef ::driver::Interrupt Int;
  
    /** 
     * Constructor.
     *
     * In this case the semaphore will be constructed as unfair.
     *
     * @param permits the initial number of permits available.
     */      
    Semaphore::Semaphore(int32 permits) : Parent(),
        isConstructed_ (getConstruct()),
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
    Semaphore::Semaphore(int32 permits, bool isFair) : Parent(),
        isConstructed_ (getConstruct()),  
        permits_ (permits),
        isFair_  (isFair),
        fifo_    (NULL){
        setConstruct( construct() );  
    }
  
    /** 
     * Destructor.
     */
    Semaphore::~Semaphore()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */   
    bool Semaphore::isConstructed() const
    {
        return isConstructed_;
    }
  
    /**
     * Acquires one permit from this semaphore.
     *
     * @return true if the semaphore is acquired successfully.
     */
    bool Semaphore::acquire()
    {
        return acquire(1);
    }
  
    /**
     * Acquires the given number of permits from this semaphore.
     *
     * @param permits the number of permits to acquire.
     * @return true if the semaphore is acquired successfully.
     */   
    bool Semaphore::acquire(int32 permits)
    {
        if(!isConstructed_) return false;
        bool is = Int::disableAll();
        // Acquire fairly
        if(isFair_)
        {
            // The first checking for acquiring available permits of the semaphore
            if( permits_ - permits >= 0 && fifo_.isEmpty() )
            {
                // Decrement the number of available permits
                permits_ -= permits;
                // Go through the semaphore to critical section
                return Int::enableAll(is, true);      
            }
            Thread* thread = &Thread::getCurrent();
            // Add current thread to the queue tail
            if( fifo_.add(thread) == false ) return Int::enableAll(is, false);
            while(true)
            {
                // Block current thread on the semaphore and switch to another thread
                Thread::block(*this);
                // Test if head thread is current thread
                if(fifo_.peek() != thread) continue;
                // Test available permits for no breaking the fifo queue by removing
                if(permits_ - permits < 0) continue;
                // Decrement the number of available permits
                permits_ -= permits;        
                // Remove head thread
                return Int::enableAll( is, fifo_.remove() );
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
                    return Int::enableAll(is, true);
                }
                // Block current thread on the semaphore and switch to another thread
                Thread::block(*this);      
            }  
        }
    }
  
    /**
     * Releases one permit.
     */
    void Semaphore::release()
    {
        release(1);
    }    
  
    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     */  
    void Semaphore::release(int32 permits)
    {
        if(!isConstructed_) return;
        bool is = Int::disableAll();
        permits_ += permits;
        Int::enableAll(is);
    }  
    
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Semaphore::isBlocked()
    {
        if(!isConstructed_) return false;
        bool is = Int::disableAll();
        bool res = permits_ > 0 ? false : true;
        return Int::enableAll(is, res);
    }
    
    /**
     * Tests if this semaphore is fair.
     *
     * @return true if this semaphore has fairness set true.
     */  
    bool Semaphore::isFair() const
    {
        return isFair_;
    }
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.   
     */
    bool Semaphore::construct()
    {
        if(!isConstructed_) return false;
        if(!fifo_.isConstructed()) return false;      
        return true;
    }
}
