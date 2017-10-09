/** 
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Mutex.hpp"
#include "system.Thread.hpp"
#include "driver.Interrupt.hpp"

namespace system
{
    typedef ::driver::Interrupt Int;
  
    /** 
     * Constructor.
     */    
    Mutex::Mutex() : Parent(),
        isConstructed_ (getConstruct()),
        id_            (UNLOCKED_ID),
        count_         (1),
        fifo_          (NULL){    
        setConstruct( construct() );    
    }
  
    /** 
     * Destructor.
     */      
    Mutex::~Mutex()
    {
    }
        
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Mutex::isConstructed() const
    {
        return isConstructed_;  
    }
    
    /**
     * Locks the mutex.
     *
     * @return true if the mutex is lock successfully.
     */      
    bool Mutex::lock()
    {
        if(!isConstructed_) return false;
        bool is = Int::disableAll();
        // The first checking for acquiring available permits of the mutex
        if( count_ - 1 >= 0 && fifo_.isEmpty() )
        {
            // Decrement the number of available permits
            count_ -= 1;
            // Go through the mutex to critical section
            return Int::enableAll(is, true);      
        }
        Thread* thread = &Thread::getCurrent();
        // Add current thread to the queue tail
        if( fifo_.add(thread) == false ) return Int::enableAll(is, false);
        while(true)
        {
            // Block current thread on the mutex and switch to another thread
            Thread::block(*this);
            // Test if head thread is current thread
            if(fifo_.peek() != thread) continue;
            // Test available permits for no breaking the fifo queue by removing
            if(count_ - 1 < 0) continue;
            // Decrement the number of available permits
            count_ -= 1;        
            // Remove head thread
            return Int::enableAll( is, fifo_.remove() );
        }    
    }
    
    /**
     * Unlocks the mutex.
     */      
    void Mutex::unlock()
    {
        if(!isConstructed_) return;
        bool is = Int::disableAll();
        count_ += 1;
        Int::enableAll(is);  
    }
  
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Mutex::isBlocked()
    {
        if(!isConstructed_) return false;
        bool is = Int::disableAll();
        bool res = count_ > 0 ? false : true;
        return Int::enableAll(is, res);  
    }
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.   
     */
    bool Mutex::construct()
    {
        if(!isConstructed_) return false;
        return true;
    }
}
