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
     * Returns the processor stack operation type.
     *
     * @return the stack operation.     
     */    
    ::api::Stack<int64>::Operation Processor::getStackType()
    {
        return ::api::Stack<int64>::ED;
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
