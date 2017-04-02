/** 
 * Target processor phase-locked loop controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_PLL_HPP_
#define BOOS_DRIVER_PLL_HPP_

#include "boos.api.Object.hpp"
#include "boos.Configuration.hpp"

namespace driver
{
  class ProcessorController;
  
  class Pll : public ::api::Object
  {
    friend class ::driver::ProcessorController;
  
  public:
  
    /** 
     * Destructor.
     */                               
    virtual ~Pll(){}
        
    /**
     * Returns the PLL interface of a target processor.
     *
     * @return target processor hardware interface, or NULL if error has been occurred.
     */
    static ::driver::Pll* create();    
    
  private:    
    
    /**
     * Initializes the driver.
     *
     * @param config the operating system configuration.
     * @return true if no errors have been occurred.
     */   
    static bool init(const ::Configuration config);
    
    /**
     * Deinitializes the driver.
     */
    static void deinit();    
    
  };
}
#endif // BOOS_DRIVER_PLL_HPP_
