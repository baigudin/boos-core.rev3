/** 
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Mutex.hpp"
#include "system.System.hpp"

namespace system
{
    /** 
     * Constructor.
     */      
    Mutex::Mutex() : Parent(),
        isConstructed_ (getConstruct()),
        kernel_        (NULL){
        setConstruct( construct() ); 
    }    
  
    /** 
     * Destructor.
     */
    Mutex::~Mutex()
    {
        delete kernel_;
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
        if( not isConstructed_ ) return false;
        return kernel_->lock();
    }
    
    /**
     * Unlocks the mutex.
     */      
    void Mutex::unlock()
    {
        if( not isConstructed_ ) return ;
        kernel_->unlock();
    }
  
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Mutex::isBlocked()
    {
        if( not isConstructed_ ) return false;
        return kernel_->isBlocked();
    }
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.   
     */
    bool Mutex::construct()
    {
        if( not isConstructed_ ) return false;
        ::api::Kernel& kernel = System::getKernel();
        kernel_ = kernel.createMutex();
        return kernel_ != NULL ? kernel_->isConstructed() : false;        
    }
}
