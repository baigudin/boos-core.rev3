/** 
 * Target processor timer controller resource. 
 *
 * The class describes a skeleton implementation of a timer resource.
 * It should be inherited by all classes, which aim expanding 
 * the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Sergey Baigudin
 */
#ifndef DRIVER_TIMER_RESOURCE_HPP_
#define DRIVER_TIMER_RESOURCE_HPP_

#include "Object.hpp"
#include "driver.Timer.hpp"

namespace driver
{
    class TimerResource : public ::Object<>, public ::driver::Timer
    {
        typedef ::Object<>  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        TimerResource() : Parent(),
            isConstructed_ ( getConstruct() ){
        }    
        
        /** 
         * Destructor.
         */                               
        virtual ~TimerResource()
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
         * @param us timer period in microseconds, zero value sets 
         *           a period to maximum value.
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
         * @return index of this timer, or -1 
         *         if error has been occurred.
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
         * Tests if this timer can interrupt a CPU.
         *
         * @return true if this source is polarizing.
         */  
        virtual bool isInterrupting() const
        {
            return false;
        }
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source, or -1 
         *         if error has been occurred.
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
        TimerResource(const TimerResource& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        TimerResource& operator =(const TimerResource& obj);      
  
    };
}
#endif // DRIVER_TIMER_RESOURCE_HPP_
