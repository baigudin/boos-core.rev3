/** 
 * Target processor timers factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_TIMER_HPP_
#define DRIVER_TIMER_HPP_

#include "api.Timer.hpp"
#include "Configuration.hpp"

namespace driver
{
  class Timer : public ::api::Timer
  {
  
  public:
  
    /**
     * The driver resource creating structure.
     */  
    struct Resource
    {
      /**
       * An available timer index.
       */
      int32 index;
      
    };
  
    /** 
     * Destructor.
     */                               
    virtual ~Timer(){}
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const = 0;
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const = 0;      
    
    /**
     * Tests if this timer can interrupt a CPU.
     *
     * @return true if this source is polarizing.
     */  
    virtual bool isInterrupting() const = 0;
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source, or -1 if error has been occurred.
     */  
    virtual int32 interrupSource() const = 0;
        
    /**
     * Returns the timer interface of a target processor.
     *
     * @param res the driver resource creating structure.
     * @return target processor timer interface, or NULL if error has been occurred.
     */
    static ::driver::Timer* create(const ::driver::Timer::Resource res);    
    
    /**
     * Initializes the driver.
     *
     * @param config the operating system configuration.
     * @return true if no errors have been occurred.
     */   
    static bool init(const ::Configuration config);
    
    /**
     * Deinitializes the driver.
     */
    static void deinit();    
    
  };
}
#endif // DRIVER_TIMER_HPP_
