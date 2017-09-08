/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_TIMER_CONTROLLER_HPP_
#define DRIVER_TIMER_CONTROLLER_HPP_

#include "driver.TimerResource.hpp"
#include "driver.Interrupt.hpp"
#include "driver.reg.Timer.hpp"

namespace driver
{
  class TimerController : public ::driver::TimerResource
  {
    typedef ::driver::TimerResource  Parent;
    
  public:
  
    /**
     * Available interrupt sources.
     */
    enum InterruptSource
    {
      TINTLO0 = 67, // Timer 0 lower counter interrupt
      TINTHI0 = 68, // Timer 0 higher counter interrupt
      TINTLO1 = 69, // Timer 1 lower counter interrupt
      TINTHI1 = 70  // Timer 1 higher counter interrupt
    };

    /** 
     * Constructor.
     */      
    TimerController() : Parent(),
      index_  (-1),
      regTim_ (NULL){
      for(int32 i=0; i<RESOURCES_NUMBER; i++) 
      {
        if( construct(i) == true )
        {
          setConstruct(true);
          return;
        }
      }
      setConstruct(false);
    }    
    
    /** 
     * Constructor.
     *
     * @param index available timer index.
     */
    TimerController(int32 index) : Parent(),
      index_  (-1),
      regTim_ (NULL){
      setConstruct( construct(index) );
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
      if( not isConstructed_ ) return;
    }      
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero sets the period to maxinum value.
     */      
    virtual void setPeriod(int64 us=0)
    {
      if( not isConstructed_ ) return;
    }
    
    /**
     * Starts this timer count.
     */      
    virtual void start()
    {
      if( not isConstructed_ ) return;  
    }
    
    /**
     * Stops this timer count.
     */      
    virtual void stop()
    {
      if( not isConstructed_ ) return;   
    }

    /**
     * Returns this timer index.
     *
     * @return index of this timer, or -1 if error has been occurred.
     */      
    virtual int32 getIndex() const
    {
      return isConstructed_ ? index_ : -1;
    }
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const
    {
      return 64;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
    {
      if( not isConstructed_ ) return 0; 
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
      switch(index_)
      {
        case 0: return TINTLO0;
        case 1: return TINTLO1;
      }
      return -1;
    }
    
    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const ::Configuration& config)
    {
      isInitialized_ = 0;        
      config_ = config;
      for(int32 i=0; i<RESOURCES_NUMBER; i++) 
      {
        lock_[i] = false;      
      } 
      isInitialized_ = IS_INITIALIZED;            
      return true;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
    {
      isInitialized_ = 0;    
    }    
    
  private:
  
    /** 
     * Constructor.
     *
     * @param index available timer index.
     * @return boolean result.
     */  
    bool construct(int32 index)
    {
      if(isInitialized_ != IS_INITIALIZED) return false;    
      uint32 addr;
      bool is = Interrupt::globalDisable();
      switch(index)
      {
        case  0: addr = reg::Timer::ADDRESS0; break;
        case  1: addr = reg::Timer::ADDRESS1; break;
        default: return Interrupt::globalEnable(is, false);
      }    
      if(lock_[index] == true) return Interrupt::globalEnable(is, false); 
      regTim_ = new (addr) reg::Timer();
      lock_[index] = true;
      index_ = index;
      return Interrupt::globalEnable(is, true);    
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    TimerController(const TimerController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    TimerController& operator =(const TimerController& obj);
    
    /**
     * The driver initialized falg value.
     */
    static const int32 IS_INITIALIZED = 0x95633217;        

    /**
     * Number of HW timers.
     */
    static const int32 RESOURCES_NUMBER = 2;
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    static int32 isInitialized_;        
    
    /**
     * The operating system configuration (no boot).
     */
    static ::Configuration config_;     
    
    /**
     * Locked by some object flag of each HW timer (no boot).
     */    
    static bool lock_[RESOURCES_NUMBER];
    
    /**
     * Number of hardware timer
     */
    int32 index_;
    
    /**
     * HW timer registers.
     */
    reg::Timer* regTim_;        
  
  };
  
  /**
   * Driver has been initialized successfully (no boot).
   */
  int32 TimerController::isInitialized_;    
  
  /**
   * The operating system configuration (no boot).
   */
  ::Configuration TimerController::config_;

  /**
   * Locked by some object flag of each HW timer (no boot).  
   */
  bool TimerController::lock_[TimerController::RESOURCES_NUMBER];
  
}
#endif // DRIVER_TIMER_CONTROLLER_HPP_
