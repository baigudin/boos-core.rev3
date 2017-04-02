/** 
 * Hardware timer interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_SYSTEM_SYSTEM_TIMER_INTERRUPT_HPP_
#define BOOS_SYSTEM_SYSTEM_TIMER_INTERRUPT_HPP_

#include "boos.system.TimerInterrupt.hpp"
#include "boos.driver.Interrupt.hpp"
#include "boos.driver.Timer.hpp"
 
namespace system
{
  class SystemTimerInterrupt : public ::system::TimerInterrupt, public ::api::Task
  {
    typedef ::system::TimerInterrupt Parent;
    typedef ::system::Interrupt      ResInt;
    typedef ::system::Timer          ResTim;

  public:

    /** 
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.
     */     
    SystemTimerInterrupt() : Parent(),
      cnt_   (0),
      acc_   (0),
      time_  (0){
      setConstruct( construct() );
    }

    /** 
     * Destructor.
     */
    virtual ~SystemTimerInterrupt()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    virtual bool isConstructed() const
    {
      return this->Parent::isConstructed();
    }   
    
    /**
     * The method with self context.
     */  
    virtual void main()
    {
      updateTime(getPeriod());
    }
    
    /**
     * Returns size of stack.
     *
     * @return stack size in bytes.
     */
    virtual int32 stackSize() const
    {
      return 0x200;
    }

    /**
     * Current value of the running system.
     *
     * @return time in nanoseconds.
     */  
    int64 nanoTime()
    {
      return isConstructed() ? updateTime(getCount()) : 0;
    }

  private:

    /**
     * Update system time.
     *
     * @param cnt the timer counter value.
     * @return updated current time in nanoseconds.
     */    
    int64 updateTime(uint64 cnt)
    {
      int64 time, dc, dt;
      int64 timerFrequency = Timer::extension().internalClock();
      bool is = global().disable();
      // Set delta count it the value in timer clocks
      // which equals a time from previous updating.
      // This time in nanoseconds is a multiplying of
      // the value in timer clocks and system timer period.
      dc = cnt - cnt_;
      // Use a multiplying on 1E+9 for getting a time in nsec
      // from timer frequency in hz
      acc_ = dc * 1000000000 + acc_;
      // The nanoseconds left time after previous updating
      dt = acc_ / timerFrequency;
      // Increment kernel working time in nsec
      time = time_ += dt;
      // Store the remainder for next updating
      acc_ = acc_ - dt * timerFrequency;
      // Store the timer counter value
      cnt_ = cnt;
      global().enable(is);               
      return time;
    } 

    /** 
     * Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct()
    {
      if(!isConstructed()) return false;
      ::api::Task& handler = reinterpret(this);
      int32 source = ResTim::extension().interrupSource();
      if(!ResInt::extension().setHandler(handler, source)) return false;
      setPeriod();
      setCount(0);
      start();
      enable(true);
      return true;
    }

    /**
     * Fixs a collision to call a TimerInterrupt constructor.
     *
     * Method gives to compiler an understanding about what should be called.
     * The parent constructor will called, just not a copy constructor.
     *
     * @param cls pointer to this class.
     * @return the reference to InterruptHandler interface of given class.
     */
    static ::api::Task& reinterpret(SystemTimerInterrupt* cls)
    {
      return *cls;
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    SystemTimerInterrupt(const SystemTimerInterrupt& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    SystemTimerInterrupt& operator =(const SystemTimerInterrupt& obj);    
    
    /**
     * Previous counter value.
     */    
    uint64 cnt_;

    /**
     * Accumulator.
     */    
    uint64 acc_;
    
    /**
     * The kernel working time in nsec.
     */        
    uint64 time_;

  };
}
#endif // BOOS_SYSTEM_SYSTEM_TIMER_INTERRUPT_HPP_
