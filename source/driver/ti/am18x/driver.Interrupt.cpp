/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "driver.Interrupt.hpp"
#include "driver.InterruptController.hpp"

namespace driver
{
  /**
   * Returns the interrupt interface of a target processor.
   *
   * @param res the driver resource creating structure.     
   * @return target processor interrupt interface.
   */
  ::driver::Interrupt* Interrupt::create(const ::driver::Interrupt::Resource res) 
  {
    ::driver::InterruptController* resource;
    resource = res.handler != NULL ? new InterruptController(res.handler, res.source) : new InterruptController();
    if(resource == NULL) return NULL; 
    if(resource->isConstructed()) return resource;       
    delete resource;
    return NULL;      
  }
  
  /**
   * Initializes the driver.
   *
   * @param config a target processor configuration.
   * @return true if no errors have been occurred.
   */   
  bool Interrupt::init(const ::Configuration config)  
  {
    return InterruptController::init(config);
  }

  /**
   * Deinitializes the driver.
   */
  void Interrupt::deinit()
  {
    InterruptController::deinit();
  }
}
