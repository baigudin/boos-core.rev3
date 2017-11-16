/** 
 * Target processor timers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Timer.hpp"
#include "module.TimerController.hpp"

namespace module
{
    /**
     * Returns the timer interface of a target processor.
     *
     * @param res the module resource creating structure.
     * @return target processor timer interface, or NULL if error has been occurred.
     */
    ::module::Timer* Timer::create(const ::module::Timer::Resource res)
    {
        ::module::Timer* resource;  
        resource = res.index >= 0 ? new TimerController(res.index) : new TimerController();
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
    bool Timer::initialize(const ::Configuration config)  
    {
        return TimerController::initialize(config);
    }
  
    /**
     * Deinitializes the module.
     */
    void Timer::deinitialize()
    {
        TimerController::deinitialize();
    }  
}
