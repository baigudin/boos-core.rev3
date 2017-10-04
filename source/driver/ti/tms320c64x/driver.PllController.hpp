/** 
 * TI TMS320C64x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_PLL_CONTROLLER_HPP_
#define DRIVER_PLL_CONTROLLER_HPP_

#include "driver.PllResource.hpp"

namespace driver
{
  class PllController : public ::driver::PllResource
  {
    typedef ::driver::PllResource  Parent;
    
  public:
  
    /** 
     * Constructor.
     */     
    PllController() : Parent()
    {
      setConstruct( construct() );    
    }
    
    /** 
     * Destructor.
     */
    virtual ~PllController()
    {
    }  

    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const ::Configuration& config)
    {
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
     * Constructs the object.
     *
     * @return true if object has been constructed successfully.
     */
    bool construct()
    {
      if(isInitialized_ != IS_INITIALIZED) return false;
      return true;
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
     * The driver initialized falg value.
     */
    static const int32 IS_INITIALIZED = 0x95633217;    
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    static int32 isInitialized_;        
    
  };
  
  /**
   * Driver has been initialized successfully (no boot).
   */
  int32 PllController::isInitialized_;  

}
#endif // DRIVER_PLL_CONTROLLER_HPP_
