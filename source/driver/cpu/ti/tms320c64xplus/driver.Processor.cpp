/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Sergey Baigudin
 */
#include "driver.Processor.hpp"
#include "driver.ProcessorController.hpp"

namespace driver
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL 
     *         if error has been occurred.
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
     * Returns the processor stack operation type.
     *
     * @return the stack operation.     
     */    
    ::api::Stack<int64>::Operation Processor::getStackType()
    {
        return ::api::Stack<int64>::ED;
    }
    
    /**
     * Initializes the driver.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    bool Processor::initialize(const ::Configuration config)
    {
        return ProcessorController::initialize(config);
    }
  
    /**
     * Deinitializes the driver.
     */
    void Processor::deinitialize()
    {
        ProcessorController::deinitialize();  
    }  
}
