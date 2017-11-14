/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REGISTERS_HPP_
#define MODULE_REGISTERS_HPP_

#include "api.ProcessorRegisters.hpp"
#include "Configuration.hpp"

namespace module
{
    class Registers
    {
      
    public:
        
        /**
         * Returns the register interface of a target processor.
         *
         * @return target processor register interface, or NULL if error has been occurred.
         */
        static ::api::ProcessorRegisters* create();
        
        /** 
         * Allows an access to protected memory mapped CPU registers.
         */    
        static void allow();
        
        /** 
         * Protects an access to protected memory mapped CPU registers.
         */    
        static void protect();    
        
        /**
         * Initializes the module.
         *
         * @param config a target processor configuration.
         * @return true if no errors have been occurred.
         */   
        static bool initialize(const ::Configuration config);
        
        /**
         * Deinitializes the module.
         */
        static void deinitialize();    
      
    };
}
#endif // MODULE_REGISTERS_HPP_
