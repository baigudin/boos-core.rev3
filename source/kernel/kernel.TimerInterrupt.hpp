/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_TIMER_INTERRUPT_HPP_
#define KERNEL_TIMER_INTERRUPT_HPP_

#include "kernel.Interrupt.hpp"
#include "kernel.Timer.hpp"

namespace kernel
{
    class TimerInterrupt : public ::kernel::Interrupt, public ::kernel::Timer
    {
        typedef ::kernel::Interrupt ParentInt;    
        typedef ::kernel::Timer     ParentTim;
      
    public:
  
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         */     
        TimerInterrupt(::api::Task& handler) : 
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
        TimerInterrupt(::api::Task& handler, int32 number) : 
            Interrupt (),
            Timer     (number){
            setConstruct( construct(&handler) );    
        }        
        
        /** 
         * Destructor.
         */
        virtual ~TimerInterrupt()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            if( not ParentInt::isConstructed() ) return false;
            if( not ParentTim::isConstructed() ) return false;    
            return true;
        }        
      
    protected:
    
        /** 
         * Constructor.
         */     
        TimerInterrupt() :
            Interrupt (),
            Timer     (){
            setConstruct( construct(NULL) );
        }        
        
        /**
         * Sets the object constructed flag.
         *
         * @param flag constructed flag.
         */      
        virtual void setConstruct(bool flag)
        {
            ParentInt::setConstruct(flag);
            ParentTim::setConstruct(flag);    
        }        
        
        /**
         * Returns the object constructed flag.
         *
         * @return reference to the constructed flag.
         */      
        virtual const bool& getConstruct()     
        {
            return ParentInt::getConstruct();  
        }         
      
    private:
  
        /**
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @return true if object has been constructed successfully.     
         */     
        bool construct(::api::Task* handler)
        {
            if( not isConstructed() ) return false;
            if(handler == NULL) return true;
            return ParentInt::setHandler(*handler, ParentTim::getInterrupSource());
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        TimerInterrupt(const TimerInterrupt& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        TimerInterrupt& operator =(const TimerInterrupt& obj);      
  
    };
}
#endif // KERNEL_TIMER_INTERRUPT_HPP_
