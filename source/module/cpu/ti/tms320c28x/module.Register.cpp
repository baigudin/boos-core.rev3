/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Register.hpp"
#include "module.RegisterController.hpp"

namespace module
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    ::module::Register* Register::create()
    {
        ::module::RegisterController* resource = new RegisterController();
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
    bool Register::initialize(const ::Configuration config)
    {
        return config.sourceClock < 0 ? false : true;
    }
  
    /**
     * Deinitializes the module.
     */
    void Register::deinitialize()
    {
    }  
}
