/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_TIMER_CONTROLLER_HPP_
#define BOOS_DRIVER_TIMER_CONTROLLER_HPP_

#include "boos.driver.TimerResource.hpp"
#include "boos.driver.Interrupt.hpp"
#include "boos.Configuration.hpp"

namespace driver
{
  class TimerController : public ::driver::TimerResource
  {
    friend class ::driver::Timer;
    
    typedef ::driver::TimerResource  Parent;

  public:
  
    /** 
     * Constructor.
     */      
    TimerController() : Parent(),
      number_ (0),
      count_  (0),
      period_ (0){
    }  
    
    /** 
     * Constructor.
     *
     * @param number available timer number.
     */
    TimerController(int32 number) : Parent(),
      number_ (number),
      count_  (0),
      period_ (0){
    }

    /** 
     * Destructor.
     */    
    virtual ~TimerController()
    {
    }
    
    /**
     * Gets this timer counter.
     *
     * @return timer counter register value.   
     */      
    virtual int64 getCount() const
    {
      return count_;
    }
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    virtual int64 getPeriod() const
    {
      return period_;
    }  
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    virtual void setCount(int64 count)
    {
      count_ = count;
    }      
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero sets the period to maxinum value.
     */      
    virtual void setPeriod(int64 us=0)
    {
      period_ = us == 0 ? -1 : us;
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
     * Returns this timer number.
     *
     * @return number of this timer, or -1 if error has been occurred.
     */      
    virtual int32 number() const
    {
      return number_;
    }
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const
    {
      return 0;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
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
      return true;
    }
    
    /**
     * Returns an available interrupt source for this timer.
     *
     * @return available interrupt source, or -1 if error has been occurred.
     */  
    virtual int32 interrupSource() const
    {
      return -1;
    }
    
  private:
    
    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config)
    {
      config_ = config;
      return true;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
    }

    /**
     * The kernel configuration (no boot).
     */
    static Configuration config_;

    /**
     * Number of this timer
     */
    int32 number_;

    /**
     * Number of this timer
     */
    int64 count_;

    /**
     * Number of this timer
     */
    int64 period_;
    
  }; 
  
  /**
   * The kernel configuration (no boot).
   */
  ::Configuration TimerController::config_;
     
}
#endif // BOOS_DRIVER_TIMER_CONTROLLER_HPP_
