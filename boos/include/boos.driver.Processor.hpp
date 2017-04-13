/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_PROCESSOR_HPP_
#define BOOS_DRIVER_PROCESSOR_HPP_

#include "boos.api.Object.hpp"
#include "boos.api.Stack.hpp"
#include "boos.Configuration.hpp"

namespace system { class Main; }

namespace driver
{
  class Processor : public ::api::Object
  {
    friend class ::system::Main;    
  
  public:
  
    /** 
     * Destructor.
     */                               
    virtual ~Processor(){}
        
    /**
     * Returns the interface of a target processor.
     *
     * @return target processor hardware interface, or NULL if error has been occurred.
     */
    static ::driver::Processor* create(); 

    /**
     * Returns the processor stack operation type.
     *
     * @return the stack operation.     
     */    
    static ::api::Stack<int64>::Operation stackType();
    
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
#endif // BOOS_DRIVER_PROCESSOR_HPP_
