/** 
 * Target processor factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_PROCESSOR_HPP_
#define DRIVER_PROCESSOR_HPP_

#include "api.Object.hpp"
#include "api.Stack.hpp"
#include "Configuration.hpp"

namespace driver
{
    class Processor : public ::api::Object
    {
    
    public:
    
        /** 
         * Destructor.
         */                               
        virtual ~Processor(){}
            
        /**
         * Returns the interface of a target processor.
         *
         * @return target processor hardware interface, or NULL if error has been occurred.
         */
        static ::driver::Processor* create(); 
        
        /**
         * Returns the processor stack operation type.
         *
         * @return the stack operation.     
         */    
        static ::api::Stack<int64>::Operation getStackType();
        
        /**
         * Initializes the driver.
         *
         * @param config the operating system configuration.
         * @return true if no errors have been occurred.
         */   
        static bool initialize(const ::Configuration config);
        
        /**
         * Deinitializes the driver.
         */
        static void deinitialize();    
      
    };
}
#endif // DRIVER_PROCESSOR_HPP_
