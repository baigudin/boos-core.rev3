/** 
 * Target processor phase-locked loop controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_PLL_HPP_
#define MODULE_PLL_HPP_

#include "api.ProcessorPll.hpp"
#include "Configuration.hpp"

namespace module
{
    class Pll
    {
    
    public:
            
        /**
         * Returns the PLL interface of a target processor.
         *
         * @return target processor hardware interface, or NULL if error has been occurred.
         */
        static ::api::ProcessorPll* create();    
        
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
#endif // MODULE_PLL_HPP_
