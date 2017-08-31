/** 
 * TI TMS320C645x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_PLL_CONTROLLER_HPP_
#define DRIVER_PLL_CONTROLLER_HPP_

#include "driver.PllResource.hpp"
#include "driver.reg.Pllc.hpp"

namespace driver
{
  class PllController : public ::driver::PllResource
  {
    friend class ::driver::Pll;
      
    typedef ::driver::PllResource  Parent;
    
  public:
  
    /** 
     * Constructor.
     */     
    PllController() : Parent()
    {
    }
    
    /** 
     * Destructor.
     */
    virtual ~PllController()
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
      volatile uint32 count;
      cpuClock_ = config.cpuClock;
      sourceClock_ = config.sourceClock;
      reg::Pllc* regPll = new (reg::Pllc::ADDRESS1) reg::Pllc();
      // Wait 100 us for PLL stabilization 
      count = 100000;
      while(count) count--;
      // Set PLL to bypass mode
      regPll->pllctl.bit.pllensrc = 0;
      regPll->pllctl.bit.pllen = 0;
      // Wait 4 cycles for the slowest PLLOUT
      count = 4;
      while(count) count--;
      // Reset PLL
      regPll->pllctl.bit.pllrst = 1;
      // Program PLLOUT
      regPll->prediv.bit.ratio = 0;
      regPll->prediv.bit.preden  = 1;      
      regPll->pllm.bit.pllm = 20;
     
      return true;
    }

    /**
     * Deinitialization.
     */
    static void deinit()
    {
    }
    
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    PllController(const PllController& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    PllController& operator =(const PllController& obj);
    
    /**
     * Reference clock rate in Hz (no boot).
     */      
    static int64 sourceClock_;
    
    /**
     * ARM clock rate in Hz (no boot).
     */      
    static int64 cpuClock_;
    
  };
  
  /**
   * Reference clock rate in Hz (no boot).
   */      
  int64 PllController::sourceClock_;
  
  /**
   * ARM clock rate in Hz (no boot).
   */      
  int64 PllController::cpuClock_;
  
}
#endif // DRIVER_PLL_CONTROLLER_HPP_
