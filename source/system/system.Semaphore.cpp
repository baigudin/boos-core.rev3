/** 
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Semaphore.hpp"
#include "system.System.hpp"

namespace system
{
    /** 
     * Constructor.
     *
     * In this case the semaphore will be constructed as unfair.
     *
     * @param permits the initial number of permits available.
     */      
    Semaphore::Semaphore(int32 permits) : Parent(),
        isConstructed_ (getConstruct()),
        semaphore_     (NULL){
        setConstruct( construct(permits, NULL) ); 
    }    
    
    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.      
     * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
     */      
    Semaphore::Semaphore(int32 permits, bool isFair) : Parent(),
        isConstructed_ (getConstruct()),
        semaphore_     (NULL){
        setConstruct( construct(permits, &isFair) );   
    }
  
    /** 
     * Destructor.
     */
    Semaphore::~Semaphore()
    {
        delete semaphore_;
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
        if( not isConstructed_ ) return false;
        return semaphore_->acquire();    
    }
  
    /**
     * Acquires the given number of permits from this semaphore.
     *
     * @param permits the number of permits to acquire.
     * @return true if the semaphore is acquired successfully.
     */   
    bool Semaphore::acquire(int32 permits)
    {
        if( not isConstructed_ ) return false;
        return semaphore_->acquire(permits);        
    }
  
    /**
     * Releases one permit.
     */
    void Semaphore::release()
    {
        if( not isConstructed_ ) return;
        semaphore_->release();        
    }    
  
    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     */  
    void Semaphore::release(int32 permits)
    {
        if( not isConstructed_ ) return;
        semaphore_->release(permits);            
    }  
    
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Semaphore::isBlocked()
    {
        if( not isConstructed_ ) return false;
        return semaphore_->isBlocked();        
    }
    
    /**
     * Tests if this semaphore is fair.
     *
     * @return true if this semaphore has fairness set true.
     */  
    bool Semaphore::isFair() const
    {
        if( not isConstructed_ ) return false;    
        return semaphore_->isFair(); 
    }
    
    /**
     * Constructor.
     *
     * @param permits the initial number of permits available.      
     * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.     
     * @return true if object has been constructed successfully.   
     */
    bool Semaphore::construct(int32 permits, bool* isFair)
    {
        if( not isConstructed_ ) return false;
        ::api::Kernel& kernel = System::call().getKernel();
        if( isFair == NULL )
        {
            semaphore_ = kernel.createSemaphore(permits);
        }
        else
        {
            semaphore_ = kernel.createSemaphore(permits, *isFair);
        }
        return semaphore_ != NULL ? semaphore_->isConstructed() : false;        
    }
}
