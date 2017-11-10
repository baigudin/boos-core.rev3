/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Interrupt.hpp"
#include "kernel.Kernel.hpp"
#include "module.Interrupt.hpp"
 
namespace kernel
{
    /**
     * Constructor.
     */
    Interrupt::Interrupt() : Parent(),
        isConstructed_ (getConstruct()),  
        driver_        (NULL){
        setConstruct( construct(NULL, 0) );
    }  
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     */
    Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
        isConstructed_ (getConstruct()),
        driver_        (NULL){
        setConstruct( construct(&handler, source) );
    }
    
    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
        delete driver_;
    }
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     * @return true if object has been constructed successfully.
     */
    bool Interrupt::construct(::api::Task* handler, int32 source)
    {
        if( not isConstructed_ ) return false;
        ::module::Interrupt::Resource res;
        if(handler != NULL) 
        {
            res.handler = handler;
            res.source = source;    
        }
        else 
        {
            res.handler = NULL;
            res.source = 0;
        }
        driver_ = ::module::Interrupt::create(res);    
        return driver_ != NULL ? driver_->isConstructed() : false;
    }
  
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Interrupt::isConstructed() const
    {
        return isConstructed_;
    }
    
    /**
     * Jumps to interrupt HW vector.
     */  
    void Interrupt::jump()
    {
        if( not isConstructed_ ) return;
        driver_->jump();
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
        if( not isConstructed_ ) return;
        driver_->clear();  
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
        if( not isConstructed_ ) return;
        driver_->set();  
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
        if( not isConstructed_ ) return false;  
        return driver_->disable();
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
        if( not isConstructed_ ) return;
        driver_->enable(status);  
    }
    
    /** 
     * Returns interrupt developing interface.
     *
     * @return interrupt developing interface.
     */  
    ::module::Interrupt& Interrupt::getDriver() const
    {
        if( not isConstructed_ ) Kernel::call().getRuntime().terminate(-1);
        return *driver_;
    }
}
