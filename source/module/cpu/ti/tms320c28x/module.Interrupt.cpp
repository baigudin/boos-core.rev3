/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Interrupt.hpp"
#include "module.InterruptController.hpp"

namespace module
{
    /**
     * Returns the interrupt interface of a target processor.
     *
     * @param res the module resource creating structure.     
     * @return target processor interrupt interface.
     */
    ::module::Interrupt* Interrupt::create(const ::module::Interrupt::Resource res) 
    {
        ::module::InterruptController* resource;
        resource = res.handler != NULL ? new InterruptController(res.handler, res.source) : new InterruptController();
        if(resource == NULL) return NULL; 
        if(resource->isConstructed()) return resource;       
        delete resource;
        return NULL;      
    }
    
    /**
     * Initializes the module.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    bool Interrupt::initialize(const ::Configuration config)  
    {
        return InterruptController::initialize(config);
    }
  
    /**
     * Deinitializes the module.
     */
    void Interrupt::deinitialize()
    {
        InterruptController::deinitialize();
    }
}
