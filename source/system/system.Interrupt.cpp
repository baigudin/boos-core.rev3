/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Interrupt.hpp"
#include "system.System.hpp"
#include "driver.Interrupt.hpp"
 
namespace system
{
  /**
   * Constructor.
   */
  Interrupt::Interrupt() : Parent(),
    isConstructed_ (getConstruct()),  
    driver_        (NULL){
    setConstruct( construct(NULL, 0) );
  }  
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   */
  Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
    isConstructed_ (getConstruct()),
    driver_        (NULL){
    setConstruct( construct(&handler, source) );
  }
  
  /**
   * Destructor.
   */
  Interrupt::~Interrupt()
  {
    delete driver_;
  }
  
  /**
   * Constructor.
   *
   * @param handler pointer to user class which implements an interrupt handler interface.   
   * @param source  available interrupt source.
   * @return true if object has been constructed successfully.
   */
  bool Interrupt::construct(::api::Task* handler, int32 source)
  {
    if(!isConstructed_) return false;
    ::driver::Interrupt::Resource res;
    if(handler != NULL) 
    {
      res.handler = handler;
      res.source = source;    
    }
    else 
    {
      res.handler = NULL;
      res.source = 0;
    }
    driver_ = ::driver::Interrupt::create(res);    
    return driver_ != NULL ? driver_->isConstructed() : false;
  }

  /**
   * Tests if this object has been constructed.
   *
   * @return true if object has been constructed successfully.
   */    
  bool Interrupt::isConstructed() const
  {
    return isConstructed_;
  }
  
  /**
   * Jumps to interrupt HW vector.
   */  
  void Interrupt::jump()
  {
    if(!isConstructed_) return;
    driver_->jump();
  }
  
  /**
   * Clears an interrupt status of this source.
   */  
  void Interrupt::clear()
  {
    if(!isConstructed_) return;
    driver_->clear();  
  }
  
  /**
   * Sets an interrupt status of this source.
   */  
  void Interrupt::set()
  {
    if(!isConstructed_) return;
    driver_->set();  
  }  
  
  /**
   * Locks this interrupt source.
   *
   * @return an interrupt enable source bit value before method was called.
   */    
  bool Interrupt::disable()
  {
    if(!isConstructed_) return false;  
    return driver_->disable();
  }
  
  /**
   * Unlocks this interrupt source.
   *
   * @param status returned status by disable method.
   */
  void Interrupt::enable(bool status)
  {
    if(!isConstructed_) return;
    driver_->enable(status);  
  }

  /**
   * Initialization.
   *
   * @return true if no errors.
   */
  bool Interrupt::init()
  {
    int32 stage = 0;
    while(true)
    {
      // Stage 1 creates global interrupt class switching
      stage++;
      global_ = new Global();
      if( global_ == NULL || !global_->isConstructed() ) break;
      // Stage complete
      stage = 0;
      break;
    }
    switch(stage)
    {
      case 1: delete global_; global_ = NULL;      
      default: return false;
      case 0: return true;
    }  
  }

  /**
   * Deinitialization.
   */
  void Interrupt::deinit()
  {
    if(global_ != NULL)
    {
      delete global_; 
      global_ = NULL;
    }
  }

  /** 
   * Returns the toggle interface for controlling global interrupts.
   *
   * @return toggle interface.
   */ 
  ::api::Toggle& Interrupt::global()
  {
    if(global_ == NULL) System::terminate();
    return *global_;
  }
  
  /** 
   * Returns interrupt developing interface.
   *
   * @return interrupt developing interface.
   */  
  ::driver::Interrupt& Interrupt::extension()
  {
    if(!isConstructed_) System::terminate();
    return *driver_;
  }
  
  
  /** 
   * Disables all maskable interrupts.
   *
   * @return global interrupt enable bit value before method was called.
   */ 
  bool Interrupt::Global::disable()
  {
    return ::driver::Interrupt::globalDisable();
  }
  
  /** 
   * Enables all maskable interrupts.
   *
   * @param status returned status by disable method.
   */    
  void Interrupt::Global::enable(bool status)
  {
    ::driver::Interrupt::globalEnable(status);  
  }
  
  /**    
   * Hardware global interrupt controller (no boot).
   */
  Interrupt::Global* Interrupt::global_;
}

