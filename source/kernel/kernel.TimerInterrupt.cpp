/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.TimerInterrupt.hpp"
#include "driver.Interrupt.hpp" 
#include "driver.Timer.hpp"

namespace kernel
{
    /** 
     * Constructor.
     */     
    TimerInterrupt::TimerInterrupt() :
        Interrupt (),
        Timer     (){
        setConstruct( construct(NULL) );
    }
  
    /** 
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     */     
    TimerInterrupt::TimerInterrupt(::api::Task& handler) : 
        Interrupt (),
        Timer     (){
        setConstruct( construct(&handler) );
    }
  
    /**
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @param number  available timer number for interrupting.
     */     
    TimerInterrupt::TimerInterrupt(::api::Task& handler, int32 number) : 
        Interrupt (),
        Timer     (number){
        setConstruct( construct(&handler) );    
    }
  
    /**
     * Destructor.
     */
    TimerInterrupt::~TimerInterrupt()
    {
    }
    
    /**
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @return true if object has been constructed successfully.     
     */     
    bool TimerInterrupt::construct(::api::Task* handler)
    {
        if( not isConstructed() ) return false;
        if(handler == NULL) return true;
        return ResInt::getDriver().setHandler(*handler, ResTim::getDriver().getInterrupSource());
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool TimerInterrupt::isConstructed() const  
    {
        if( not ResInt::isConstructed() ) return false;
        if( not ResTim::isConstructed() ) return false;    
        return true;
    }
    
    /**
     * Sets the object constructed flag.
     *
     * @param flag constructed flag.
     */      
    void TimerInterrupt::setConstruct(bool flag)
    {
        ResInt::setConstruct(flag);
        ResTim::setConstruct(flag);    
    }  
    
    /**
     * Sets the object constructed flag.
     *
     * @param flag constructed flag.
     */      
    const bool& TimerInterrupt::getConstruct()  
    {
        return ResInt::getConstruct();  
    }    
}
