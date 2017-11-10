/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Interrupt.hpp"
#include "system.System.hpp"

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
        interrupt_     (NULL){
        setConstruct( construct(handler, source) );
    }
    
    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
        delete interrupt_;
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
        interrupt_ = System::call().getKernel().createInterrupt(handler, source);
        return interrupt_ != NULL ? interrupt_->isConstructed() : false;
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
        interrupt_->jump();
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
        if( not isConstructed_ ) return;
        interrupt_->clear();  
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
        if( not isConstructed_ ) return;
        interrupt_->set();  
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
        if( not isConstructed_ ) return false;  
        return interrupt_->disable();
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
        if( not isConstructed_ ) return;
        interrupt_->enable(status);  
    }

}
