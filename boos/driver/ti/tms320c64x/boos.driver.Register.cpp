/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.driver.RegisterController.hpp"

namespace driver
{
  /**
   * Returns the register interface of a target processor.
   *
   * @return target processor register interface, or NULL if error has been occurred.
   */
  ::driver::Register* Register::create()
  {
    ::driver::Register* resource = new RegisterController();
    if(resource == NULL) return NULL; 
    if(resource->isConstructed()) return resource;       
    delete resource;
    return NULL;      
  }
  
  /** 
   * Access to protected memory mapped CPU registers.
   *
   * @return the interface, or NULL if CPU family does not have protected registers, or error has been occurred.
   */    
  ::api::Toggle* Register::access()
  {
    return NULL;
  }
  
  /**
   * Initializes the driver.
   *
   * @param config a target processor configuration.
   * @return true if no errors have been occurred.
   */   
  bool Register::init(const ::Configuration config)
  {
    return config.sourceClock < 0 ? false : true;
  }

  /**
   * Deinitializes the driver.
   */
  void Register::deinit()
  {
  }  
}
