/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_PROCESSOR_HPP_
#define MODULE_PROCESSOR_HPP_

#include "api.Stack.hpp"
#include "Configuration.hpp"

namespace module
{
    class Processor
    {
    
    public:
        
        /**
         * Returns the processor stack operation type.
         *
         * @return the stack operation.     
         */    
        static ::api::Stack<int64>::Operation getStackType();
        
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
#endif // MODULE_PROCESSOR_HPP_
