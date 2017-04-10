/** 
 * Target processor watchdog controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_WATCHDOG_HPP_
#define BOOS_DRIVER_WATCHDOG_HPP_

#include "boos.api.Object.hpp"
#include "boos.Configuration.hpp"

namespace driver
{
  class ProcessorController;
  
  class Watchdog : public ::api::Object
  {
    friend class ::driver::ProcessorController;
  
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
#endif // BOOS_DRIVER_WATCHDOG_HPP_
