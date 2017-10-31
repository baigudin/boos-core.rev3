/** 
 * Target processor timer controller resource. 
 *
 * The class describes a skeleton implementation of a timer resource.
 * It should be inherited by all classes, which aim expanding the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_TIMER_BASE_HPP_
#define MODULE_TIMER_BASE_HPP_

#include "Object.hpp"
#include "module.Timer.hpp"

namespace module
{
    class TimerBase : public ::Object<>, public ::module::Timer
    {
        typedef ::Object<>  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        TimerBase() : Parent(),
            isConstructed_ ( getConstruct() ){
        }    
        
        /** 
         * Destructor.
         */                               
        virtual ~TimerBase()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }
        
        /**
         * Gets this timer counter.
         *
         * @return timer counter register value.   
         */      
        virtual int64 getCount() const
        {
            return 0;
        }
        
        /**
         * Gets this timer period.
         *
         * @return timer period register value.
         */      
        virtual int64 getPeriod() const
        {
            return 0;
        }
        
        /**
         * Sets this timer counter.
         *
         * @param count timer counter register value.
         */      
        virtual void setCount(int64 count)
        {
        }
        
        /**
         * Sets this timer period.
         *
         * @param us timer period in microseconds, zero value sets a period to maximum value.
         */      
        virtual void setPeriod(int64 us=0)
        {
        }
        
        /**
         * Starts this timer count.
         */      
        virtual void start()
        {
        }
        
        /**
         * Stops this timer count.
         */      
        virtual void stop()
        {
        }
        
        /**
         * Returns this timer index.
         *
         * @return index of this timer, or -1 if error has been occurred.
         */
        virtual int32 getIndex() const
        {
            return -1;
        }
        
        /**
         * Returns number of timer digits.
         *
         * @return timer digits.
         */  
        virtual int32 getDigit() const
        {
            return 0;
        }
        
        /**
         * Returns this timer internal clock in Hz.
         *
         * @return timer internal clock.
         */  
        virtual int64 getInternalClock() const
        {
            return 0;
        }    
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source, or -1 if error has been occurred.
         */  
        virtual int32 getInterrupSource() const
        {
            return -1;
        }
      
    protected:
      
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
      
    private:
    
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        TimerBase(const TimerBase& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        TimerBase& operator =(const TimerBase& obj);      
  
    };
}
#endif // MODULE_TIMER_BASE_HPP_
