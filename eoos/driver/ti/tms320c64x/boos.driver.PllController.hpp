/** 
 * TI TMS320C64x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_PLL_CONTROLLER_HPP_
#define BOOS_DRIVER_PLL_CONTROLLER_HPP_

#include "boos.driver.PllResource.hpp"

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
    
  };
}
#endif // BOOS_DRIVER_PLL_CONTROLLER_HPP_
