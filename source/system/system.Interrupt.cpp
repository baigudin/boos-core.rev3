/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Interrupt.hpp"
#include "kernel.Factory.hpp"

using namespace kernel;

namespace system
{
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     */
    Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
        isConstructed_ (getConstruct()),
        kernel_        (NULL){
        setConstruct( construct(handler, source) );
    }
    
    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
        delete kernel_;
    }
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     * @return true if object has been constructed successfully.
     */
    bool Interrupt::construct(::api::Task& handler, int32 source)
    {
        if( not isConstructed_ ) return false;    
        Factory* factory = Factory::create();
        if(factory == NULL) return false;
        if(factory->isConstructed()) 
        {
            kernel_ = factory->createInterrupt(handler, source);
        }
        delete factory;
        return kernel_ != NULL ? kernel_->isConstructed() : false;
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
        kernel_->jump();
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
        if( not isConstructed_ ) return;
        kernel_->clear();  
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
        if( not isConstructed_ ) return;
        kernel_->set();  
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
        if( not isConstructed_ ) return false;  
        return kernel_->disable();
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
        if( not isConstructed_ ) return;
        kernel_->enable(status);  
    }

}
