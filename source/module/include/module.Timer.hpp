/** 
 * Target processor timers factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_TIMER_HPP_
#define MODULE_TIMER_HPP_

#include "api.ProcessorTimer.hpp"
#include "Configuration.hpp"

namespace module
{
    class Timer
    {
    
    public:
    
        /**
         * The module resource creating structure.
         */  
        struct Resource
        {
            /**
             * An available timer index.
             */
            int32 index;
          
        };
                    
        /**
         * Returns the timer interface of a target processor.
         *
         * @param res the module resource creating structure.
         * @return target processor timer interface, or NULL if error has been occurred.
         */
        static ::api::ProcessorTimer* create(const ::module::Timer::Resource res);    
        
        /**
         * Initializes the module.
         *
         * @param config the operating system configuration.
         * @return true if no errors have been occurred.
         */   
        static bool initialize(const ::Configuration config);
        
        /**
         * Deinitializes the module.
         */
        static void deinitialize();    
      
    };
}
#endif // MODULE_TIMER_HPP_
