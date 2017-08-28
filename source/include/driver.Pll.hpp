/** 
 * Target processor phase-locked loop controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_PLL_HPP_
#define DRIVER_PLL_HPP_

#include "api.Object.hpp"
#include "Configuration.hpp"

namespace driver
{
  class Pll : public ::api::Object
  {
  
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
#endif // DRIVER_PLL_HPP_
