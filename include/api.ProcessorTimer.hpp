/** 
 * A central processing unit timer resource interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_PROCESSOR_TIMER_HPP_
#define API_PROCESSOR_TIMER_HPP_

#include "api.Timer.hpp"

namespace api
{
    class ProcessorTimer : public ::api::Timer
    {
    
    public:
           
        /** 
         * Destructor.
         */                               
        virtual ~ProcessorTimer(){}
        
        /**
         * Returns number of timer digits.
         *
         * @return timer digits.
         */  
        virtual int32 getDigit() const = 0;
        
        /**
         * Returns this timer internal clock in Hz.
         *
         * @return timer internal clock.
         */  
        virtual int64 getInternalClock() const = 0;  
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source, or -1 if error has been occurred.
         */  
        virtual int32 getInterrupSource() const = 0;
      
    };
}
#endif // API_PROCESSOR_TIMER_HPP_
