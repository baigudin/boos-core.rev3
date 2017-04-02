/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.driver.ProcessorController.hpp"

namespace driver
{
  /**
   * Returns the register interface of a target processor.
   *
   * @return target processor register interface, or NULL if error has been occurred.
   */
  ::driver::Processor* Processor::create()
  {
    ::driver::Processor* resource;
    resource = new ProcessorController();
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
  bool Processor::init(const ::Configuration config)
  {
    return ProcessorController::init(config);
  }

  /**
   * Deinitializes the driver.
   */
  void Processor::deinit()
  {
    ProcessorController::deinit();  
  }  
}