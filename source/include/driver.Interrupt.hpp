/** 
 * Target processor interrupts factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_INTERRUPT_HPP_
#define DRIVER_INTERRUPT_HPP_

#include "api.Interrupt.hpp"
#include "api.Task.hpp"
#include "driver.Register.hpp"
#include "Configuration.hpp"

namespace driver
{
    class Interrupt : public ::api::Interrupt
    {
  
    public:
    
        /**
         * The driver resource creating structure.
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
         * Destructor.
         */                               
        virtual ~Interrupt(){}
        
        /**
         * Sets interrupt source handler.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         * @return true if handler is set successfully.
         */      
        virtual bool setHandler(::api::Task& handler, int32 source) = 0;
        
        /**
         * Removes this interrupt source.
         */        
        virtual void removeHandler() = 0;
        
        /**
         * Resets registers context for storing to the default.
         * 
         * Method restores default registers for storing the CPU registers to it.
         * This method may be called in an user interrupt handler, it means
         * the default conxet will be restored with the context restore procedure.
         */
        virtual void resetRegister() = 0;
        
        /**
         * Sets new registers context for storing.
         * 
         * Method sets a new register context for storing the CPU registers to it.
         * This method may be called in an user interrupt handler, it means
         * given conxet will be restored by the context restore procedure.
         *
         * @param reg new registers context.
         */
        virtual void setRegister(::driver::Register& reg) = 0;
        
        /**
         * Returns the interrupt interface of a target processor.
         *
         * @param res the driver resource creating structure.     
         * @return target processor interrupt interface.
         */
        static ::driver::Interrupt* create(const ::driver::Interrupt::Resource res);
        
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
        template<class Type>
        static inline bool enableAll(bool status, Type ret)
        {
          enableAll(status);
          return ret;   
        }    
        
        /**
         * Initializes the driver.
         *
         * @param config a target processor configuration.
         * @return true if no errors have been occurred.
         */   
        static bool initialize(const ::Configuration config);
        
        /**
         * Deinitializes the driver.
         */
        static void deinitialize();
      
    };
}
#endif // DRIVER_INTERRUPT_HPP_
