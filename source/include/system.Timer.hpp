/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Sergey Baigudin
 */
#ifndef SYSTEM_TIMER_HPP_
#define SYSTEM_TIMER_HPP_

#include "Object.hpp" 
#include "api.Timer.hpp" 

namespace driver { class Timer; }

namespace system
{
    class Timer : public ::Object<>, public ::api::Timer
    {
        typedef ::Object<> Parent;
  
    public:
  
        /** 
         * Constructor.
         *
         * Constructs this object and allocs 
         * a first free hardware timer.
         */      
        Timer();
        
        /** 
         * Constructor.
         *
         * @param index available timer index.
         */
        Timer(int32 index);
       
        /** 
         * Destructor.
         */    
        virtual ~Timer();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;    
        
        /**
         * Gets this timer counter.
         *
         * @return timer counter register value.   
         */      
        virtual int64 getCount() const;
        
        /**
         * Gets this timer period.
         *
         * @return timer period register value.
         */      
        virtual int64 getPeriod() const;
        
        /**
         * Sets this timer counter.
         *
         * @param count timer counter register value.
         */      
        virtual void setCount(int64 count);
        
        /**
         * Sets this timer period.
         *
         * @param us timer period in microseconds, zero sets 
         *           the period to maxinum value.
         */      
        virtual void setPeriod(int64 us=0);
        
        /**
         * Starts this timer count.
         */      
        virtual void start();
        
        /**
         * Stops this timer count.
         */      
        virtual void stop();
       
        /**
         * Returns this timer index.
         *
         * @return index of this timer, or -1 if error is occurred.
         */
        virtual int32 getIndex() const;
      
    protected:
  
        /** 
         * Returns extended interface of interrupt.
         *
         * @return extended interface.
         */  
        ::driver::Timer& getDriver();
  
    private:
    
        /**
         * Constructor.
         *
         * @param index available timer index.
         * @return true if object has been constructed successfully.
         */
        bool construct(int32* index);
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Timer(const Timer& obj);
       
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Timer& operator =(const Timer& obj);
       
        /**
         * Extended timer controller interface.
         */    
        ::driver::Timer* driver_;
      
    };
}
#endif // SYSTEM_TIMER_HPP_
