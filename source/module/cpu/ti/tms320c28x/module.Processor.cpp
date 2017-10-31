/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Processor.hpp" 
#include "module.ProcessorController.hpp"

namespace module
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    ::module::Processor* Processor::create()
    {
        ::module::Processor* resource;
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
        return ::api::Stack<int64>::FA;
    }
    
    /**
     * Initializes the module.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    bool Processor::initialize(const ::Configuration config)
    {
        return ProcessorController::initialize(config);
    }
    
    /**
     * Deinitializes the module.
     */
    void Processor::deinitialize()
    {
        ProcessorController::deinitialize();  
    }  
}
