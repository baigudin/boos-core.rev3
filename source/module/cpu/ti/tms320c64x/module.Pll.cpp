/** 
 * Target processor phase-locked loop controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Pll.hpp" 
#include "module.PllController.hpp"

namespace module
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    ::module::Pll* Pll::create()
    {
        ::module::PllController* resource;
        resource = new PllController();
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
    bool Pll::initialize(const ::Configuration config)
    {
        return PllController::initialize(config);
    }
  
    /**
     * Deinitializes the module.
     */
    void Pll::deinitialize()
    {
        PllController::deinitialize();  
    }  
}
