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
        kernel_        (NULL){
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
        kernel_        (NULL){
        setConstruct( construct(permits, &isFair) );   
    }
  
    /** 
     * Destructor.
     */
    Semaphore::~Semaphore()
    {
        delete kernel_;
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
        return kernel_->acquire();    
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
        return kernel_->acquire(permits);        
    }
  
    /**
     * Releases one permit.
     */
    void Semaphore::release()
    {
        if( not isConstructed_ ) return;
        kernel_->release();        
    }    
  
    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     */  
    void Semaphore::release(int32 permits)
    {
        if( not isConstructed_ ) return;
        kernel_->release(permits);            
    }  
    
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Semaphore::isBlocked()
    {
        if( not isConstructed_ ) return false;
        return kernel_->isBlocked();        
    }
    
    /**
     * Tests if this semaphore is fair.
     *
     * @return true if this semaphore has fairness set true.
     */  
    bool Semaphore::isFair() const
    {
        if( not isConstructed_ ) return false;    
        return kernel_->isFair(); 
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
        ::api::Kernel& kernel = System::getKernel();
        if( isFair == NULL )
        {
            kernel_ = kernel.createSemaphore(permits);
        }
        else
        {
            kernel_ = kernel.createSemaphore(permits, *isFair);
        }
        return kernel_ != NULL ? kernel_->isConstructed() : false;        
    }
}
