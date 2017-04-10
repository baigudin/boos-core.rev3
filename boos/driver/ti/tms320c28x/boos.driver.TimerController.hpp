/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_TIMER_CONTROLLER_HPP_
#define BOOS_DRIVER_TIMER_CONTROLLER_HPP_

#include "boos.driver.TimerResource.hpp"
#include "boos.driver.Interrupt.hpp"
#include "boos.driver.Register.hpp"
#include "boos.driver.reg.Timer.hpp"
#include "boos.driver.reg.System.hpp"

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
    }
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    virtual int64 getPeriod() const
    {
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
     * @param us timer period in microseconds, zero sets the period to maxinum value.
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
     * Returns this timer number.
     *
     * @return number of this timer, or -1 if error has been occurred.
     */      
    virtual int32 number() const
    {
    }
    
    /**
     * Returns number of timer digits.
     *
     * @return timer digits.
     */  
    virtual int32 digits() const
    {
      return 32;
    }
    
    /**
     * Returns this timer internal clock in Hz.
     *
     * @return timer internal clock.
     */  
    virtual int64 internalClock() const
    {
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
      bool res = false;
      bool is = Interrupt::globalDisable();
      do{
        if(lock_[index] == true) break; 
        uint32 addr = address(index);
        if(addr == 0) break;
        regTim_ = new (addr) reg::Timer();
        Register::allow();
        // Set the CPU Timer is clocked
        switch(index)
        {
          case  0: regSys_->pclkcr3.bit.cputimer0enclk = 1; break;
          case  1: regSys_->pclkcr3.bit.cputimer1enclk = 1; break;
          case  2: regSys_->pclkcr3.bit.cputimer2enclk = 1; break;               
          default: break;
        }
        Register::protect();      
        index_ = index;        
        lock_[index_] = true;
        res = true;
      }while(false);
      return Interrupt::globalEnable(is, res);    
    }
    
    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config)
    {
      config_ = config;
      isInitialized_ = 0;      
      regSys_ = new (reg::System::ADDRESS) reg::System();            
      Register::allow();
      // Set CPU Timers are not clocked
      regSys_->pclkcr3.bit.cputimer0enclk = 0;
      regSys_->pclkcr3.bit.cputimer1enclk = 0;
      regSys_->pclkcr3.bit.cputimer2enclk = 0;                
      Register::protect();      
      for(int32 i=0; i<RESOURCES_NUMBER; i++) 
      {
        uint32 addr = address(i);
        if(addr == 0) return false;
        reg::Timer* timer = new (addr) reg::Timer();;
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
    
    /**
     * Returns a timer register address.
     *
     * @param index timer index.
     * @return memory address of given timer index.
     */
    static uint32 address(int32 index)
    {
      switch(index)
      {
        case 0: return reg::Timer::ADDRESS0;
        case 1: return reg::Timer::ADDRESS1;
        case 2: return reg::Timer::ADDRESS2;
        default: return 0;
      }
    }    
    
    /**
     * Number of HW timers.
     */
    static const int32 RESOURCES_NUMBER = 3;    
    
    /**
     * The driver initialized falg value.
     */
    static const int32 IS_INITIALIZED = 0x123abc73;
    

    /**
     * The operating system configuration (no boot).
     */
    static Configuration config_;

    /**
     * Locked by some object flag of each HW timer (no boot).
     */    
    static bool lock_[RESOURCES_NUMBER];
    
    /**
     * System Control Registers (no boot).
     */  
    static reg::System* regSys_;
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    static int32 isInitialized_;    
    
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
   * The operating system configuration (no boot).
   */
  ::Configuration TimerController::config_;
  
  /**
   * Locked by some object flag of each HW timer (no boot).  
   */
  bool TimerController::lock_[TimerController::RESOURCES_NUMBER];
  
  /**
   * System Control Registers (no boot).
   */  
  ::driver::reg::System* TimerController::regSys_;
  
  /**
   * Driver has been initialized successfully (no boot).
   */
  int32 TimerController::isInitialized_;
       
}
#endif // BOOS_DRIVER_TIMER_CONTROLLER_HPP_
