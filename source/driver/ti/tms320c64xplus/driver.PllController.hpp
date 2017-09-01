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
      // SYSREFCLK must be in 400 MHz to 1200 MHz range 
      if(cpuClock_ < 400000000 || cpuClock_ > 1200000000) return false;
      uint64 pllm = cpuClock_ / sourceClock_ - 1;
      if(pllm & ~0x000000000000003f) return false;      
      // CLKIN cycle time in ns
      int64 c = 1000000000 / sourceClock_;
      // Create PLL registers map
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
      // Program PREDIV and PLLM
      regPll->prediv.bit.ratio = 0;
      regPll->prediv.bit.preden  = 1;
      regPll->pllm.bit.pllm = pllm & 0x000000000000003f;
      
      // Program PLLDIV1n
      // TODO: SUPPLEMENT SOME SETS WHEN THOSE ARE NEEDED
      
      // Wait 128 * C ns for TMS320C645x or min 1000 ns for TMS320C6457 for PLL reset
      count = 128 * c;
      if(count < 1000) count = 1000;
      while(count) count--;
      // Bring PLL out of reset
      regPll->pllctl.bit.pllrst = 0;
      // Wait 2000 * C ms for PLL lock
      count = 2000 * c;
      while(count) count--;      
      // Enable PLL mode
      regPll->pllctl.bit.pllen = 1;
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
