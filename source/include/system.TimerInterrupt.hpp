/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_TIMER_INTERRUPT_HPP_
#define SYSTEM_TIMER_INTERRUPT_HPP_

#include "system.Interrupt.hpp"
#include "system.Timer.hpp"

namespace system
{
    class TimerInterrupt : public ::system::Interrupt, public ::system::Timer
    {
        typedef ::system::Interrupt Parent;
        typedef ::system::Interrupt ResInt;    
        typedef ::system::Timer     ResTim;
      
    public:
  
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         */     
        TimerInterrupt(::api::Task& handler);
        
        /**
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param number  available timer number for interrupting.
         */     
        TimerInterrupt(::api::Task& handler, int32 number);
        
        /** 
         * Destructor.
         */
        virtual ~TimerInterrupt();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;
      
    protected:
    
        /** 
         * Constructor.
         */     
        TimerInterrupt();   
        
        /**
         * Sets the object constructed flag.
         *
         * @param flag constructed flag.
         */      
        virtual void setConstruct(bool flag);
      
    private:
  
        /**
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @return true if object has been constructed successfully.     
         */     
        bool construct(::api::Task* handler);    
        
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
#endif // SYSTEM_TIMER_INTERRUPT_HPP_
