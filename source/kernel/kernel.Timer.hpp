/** 
 * The kernel hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_TIMER_HPP_
#define KERNEL_TIMER_HPP_

#include "kernel.Object.hpp" 
#include "api.ProcessorTimer.hpp" 
#include "module.Timer.hpp"
#include "module.Interrupt.hpp"

namespace kernel
{
    class Timer : public ::kernel::Object, public ::api::ProcessorTimer
    {
        typedef ::kernel::Object    Parent;
        typedef ::module::Interrupt Int;
  
    public:
  
        /** 
         * Constructor.
         *
         * Constructs this object and allocs a first free hardware timer.
         */      
        Timer() : Parent(),
            isConstructed_ (getConstruct()),    
            module_        (NULL){
            setConstruct( construct(NULL) );    
        }

        /** 
         * Constructor.
         *
         * @param index available timer index.
         */
        Timer(int32 index) : Parent(),
            isConstructed_ (getConstruct()),        
            module_        (NULL){
            setConstruct( construct(&index) );
        }        
       
        /** 
         * Destructor.
         */    
        virtual ~Timer()
        {
            bool is = Int::disableAll();
            delete module_;
            Int::enableAll(is);
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
            return isConstructed_ ? module_->getCount() : 0;
        }        
        
        /**
         * Gets this timer period.
         *
         * @return timer period register value.
         */      
        virtual int64 getPeriod() const
        {
            return isConstructed_ ? module_->getPeriod() : 0;
        }          
        
        /**
         * Sets this timer counter.
         *
         * @param count timer counter register value.
         */      
        virtual void setCount(int64 count)
        {
            if( isConstructed_ ) module_->setCount(count);  
        }          
        
        /**
         * Sets this timer period.
         *
         * @param us timer period in microseconds, zero sets the period to maxinum value.
         */      
        virtual void setPeriod(int64 us=0)
        {
            if( isConstructed_ ) module_->setPeriod(us);  
        }
        
        /**
         * Starts this timer count.
         */      
        virtual void start()
        {
            if( isConstructed_ ) module_->start();  
        }
        
        /**
         * Stops this timer count.
         */      
        virtual void stop()
        {
            if( isConstructed_ ) module_->stop();  
        }
       
        /**
         * Returns this timer index.
         *
         * @return index of this timer, or -1 if error has been occurred.
         */
        virtual int32 getIndex() const
        {
            return isConstructed_ ? module_->getIndex() : -1;
        }
        
        /**
         * Returns number of timer digits.
         *
         * @return timer digits.
         */  
        virtual int32 getDigit() const
        {
            return isConstructed_ ? module_->getDigit() : 0;        
        }
        
        /**
         * Returns this timer internal clock in Hz.
         *
         * @return timer internal clock.
         */  
        virtual int64 getInternalClock() const
        {
            return isConstructed_ ? module_->getInternalClock() : 0;                
        }
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source, or -1 if error has been occurred.
         */  
        virtual int32 getInterrupSource() const
        {
            return isConstructed_ ? module_->getInterrupSource() : -1;        
        }        
  
    private:
    
        /**
         * Constructor.
         *
         * @param index available timer index.
         * @return true if object has been constructed successfully.
         */
        bool construct(int32* index)
        {
            if( not isConstructed_ ) return false;
            ::module::Timer::Resource res;
            if(index != NULL) 
            {
                res.index = *index;
            }
            else 
            {
                res.index = -1;    
            }  
            bool is = Int::disableAll();
            module_ = ::module::Timer::create(res);
            Int::enableAll(is);
            return module_ != NULL ? module_->isConstructed() : false;
        }
        
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
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
       
        /**
         * Extended timer controller interface.
         */    
        ::api::ProcessorTimer* module_;
      
    };
}
#endif // KERNEL_TIMER_HPP_
