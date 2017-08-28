/** 
 * Target processor watchdog controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_WATCHDOG_HPP_
#define DRIVER_WATCHDOG_HPP_

#include "api.Object.hpp"
#include "Configuration.hpp"

namespace driver
{
  class Watchdog : public ::api::Object
  {
  
  public:
  
    /** 
     * Destructor.
     */                               
    virtual ~Watchdog(){}
        
    /**
     * Returns the Watchdog interface of a target processor.
     *
     * @return target processor hardware interface, or NULL if error has been occurred.
     */
    static ::driver::Watchdog* create();    
    
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
#endif // DRIVER_WATCHDOG_HPP_
