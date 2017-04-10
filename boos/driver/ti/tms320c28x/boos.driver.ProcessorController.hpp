/** 
 * TI TMS320F28x3x processor family.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_PROCESSOR_CONTROLLER_HPP_
#define BOOS_DRIVER_PROCESSOR_CONTROLLER_HPP_

#include "boos.driver.Watchdog.hpp"
#include "boos.driver.ProcessorResource.hpp"
#include "boos.driver.Pll.hpp"
#include "boos.driver.Register.hpp"
#include "boos.driver.Interrupt.hpp"
#include "boos.driver.Timer.hpp"

namespace driver
{
  class ProcessorController : public ::driver::ProcessorResource
  {
    friend class ::driver::Processor;
      
    typedef ::driver::ProcessorResource  Parent;
    
  public:
  
    /** 
     * Constructor.
     */     
    ProcessorController() : Parent()
    {
    }
    
    /** 
     * Destructor.
     */
    virtual ~ProcessorController()
    {
    }  
  
  private:  

    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const ::Configuration& config)
    {
      stage_ = 0;
      // Stage 1 
      stage_++;
      if( not ::driver::Watchdog::init(config) ) return false;    
      // Stage 1 
      stage_++;
      if( not ::driver::Pll::init(config) ) return false;    
      // Stage 2 
      stage_++;
      if( not ::driver::Register::init(config) ) return false;
      // Stage 3 
      stage_++;
      if( not ::driver::Interrupt::init(config) ) return false;
      // Stage 4 
      stage_++;
      if( not ::driver::Timer::init(config) ) return false;
      // Stage complete
      stage_ = -1;
      return true;
    }

    /**
     * Deinitialization.
     */
    static void deinit()
    {
      switch(stage_)
      {
        default:
        case  5: ::driver::Timer::deinit();
        case  4: ::driver::Interrupt::deinit();
        case  3: ::driver::Register::deinit();      
        case  2: ::driver::Pll::deinit();
        case  1: ::driver::Watchdog::deinit();        
        case  0: break;
      }
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    ProcessorController(const ProcessorController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    ProcessorController& operator =(const ProcessorController& obj);
    
    /**
     * The processor internal module initialization stage (no boot).
     */
    static int32 stage_;
    
  };
  
  /**
   * The processor internal module initialization stage (no boot).
   */
  int32 ProcessorController::stage_; 
    
}
#endif // BOOS_DRIVER_PROCESSOR_CONTROLLER_HPP_
