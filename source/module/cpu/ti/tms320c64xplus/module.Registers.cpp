/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Registers.hpp" 
#include "module.RegistersController.hpp"

namespace module
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    ::api::ProcessorRegisters* Registers::create()
    {
        ::api::ProcessorRegisters* resource = new RegistersController();
        if(resource == NULL) return NULL; 
        if(resource->isConstructed()) return resource;       
        delete resource;
        return NULL;      
    }
    
    /** 
     * Allows an access to protected memory mapped CPU registers.
     */    
    void Registers::allow()
    {
    }
    
    /** 
     * Protects an access to protected memory mapped CPU registers.
     */    
    void Registers::protect()
    {
    }
    
    /**
     * Initializes the module.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    bool Registers::initialize(const ::Configuration config)
    {
        return config.sourceClock < 0 ? false : true;
    }
  
    /**
     * Deinitializes the module.
     */
    void Registers::deinitialize()
    {
    }  
}
