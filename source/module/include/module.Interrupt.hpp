/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_INTERRUPT_HPP_
#define MODULE_INTERRUPT_HPP_

#include "api.ProcessorInterrupt.hpp"
#include "api.Task.hpp"
#include "Configuration.hpp"

namespace module
{
    class Interrupt
    {
  
    public:
    
        /**
         * The module resource creating structure.
         */  
        struct Resource
        {
            /**
             * A pointer to a class which implements an interrupt handler interface.
             */
            ::api::Task* handler;

            /**
             * An available interrupt source.     
             */
            int32 source;

        };
              
        /**
         * Returns the interrupt interface of a target processor.
         *
         * @param res the module resource creating structure.     
         * @return target processor interrupt interface.
         */
        static ::api::ProcessorInterrupt* create(const ::module::Interrupt::Resource res);
        
        /**
         * Disables all maskable interrupts.
         *
         * @return global interrupts enable bit value before method was called.
         */
        static bool disableAll();
        
        /**
         * Enables all maskable interrupts.
         *
         * The true passed argument directly turns all maskable interrupts on, 
         * and the false does nothing, the interrupts stay in the current state.     
         *
         * @param status the returned status by disable method.
         */
        static void enableAll(bool status=true);
        
        /**
         * Enables all maskable interrupts.
         *
         * @param status the returned status by disable method.
         * @param ret    value which will be returned.     
         * @return given value.     
         */
        template<typename Type>
        static inline Type enableAll(bool status, Type ret)
        {
            enableAll(status);
            return ret;   
        }    
        
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
#endif // MODULE_INTERRUPT_HPP_
