/** 
 * TI AM18x processor family.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Sergey Baigudin
 */
#ifndef DRIVER_PROCESSOR_CONTROLLER_HPP_
#define DRIVER_PROCESSOR_CONTROLLER_HPP_

#include "driver.ProcessorResource.hpp"
#include "driver.Pll.hpp"
#include "driver.Register.hpp"
#include "driver.Interrupt.hpp"
#include "driver.Timer.hpp"

namespace driver
{
    class ProcessorController : public ::driver::ProcessorResource
    {
        typedef ::driver::ProcessorResource  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        ProcessorController() : Parent()
        {
            setConstruct( construct() );    
        }
        
        /** 
         * Destructor.
         */
        virtual ~ProcessorController()
        {
        }  
      
        /**
         * Initialization.
         *
         * @param config the operating system configuration.
         * @return true if no errors.
         */
        static bool initialize(const ::Configuration& config)
        {
            isInitialized_ = 0;        
            stage_ = 0;
            // Stage 1 
            stage_++;
            if( not ::driver::Pll::initialize(config) ) 
                return false;    
            // Stage 2 
            stage_++;
            if( not ::driver::Register::initialize(config) ) 
                return false;
            // Stage 3 
            stage_++;
            if( not ::driver::Interrupt::initialize(config) ) 
                return false;
            // Stage 4 
            stage_++;
            if( not ::driver::Timer::initialize(config) ) 
                return false;
            // Stage complete
            stage_ = -1;
            isInitialized_ = IS_INITIALIZED;      
            return true;
        }
      
        /**
         * Deinitialization.
         */
        static void deinitialize()
        {
            switch(stage_)
            {
                default:
                case  4: ::driver::Timer::deinitialize();
                case  3: ::driver::Interrupt::deinitialize();
                case  2: ::driver::Register::deinitialize();      
                case  1: ::driver::Pll::deinitialize();
                case  0: break;
            }
            isInitialized_ = 0;      
        }
      
    private:  
    
        /** 
         * Constructs the object.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            if(isInitialized_ != IS_INITIALIZED) return false;
            return true;
        }    
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        ProcessorController(const ProcessorController& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        ProcessorController& 
        operator =(const ProcessorController& obj);
        
        /**
         * The driver initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x65437165;    
        
        /**
         * Driver has been initialized successfully (no boot).
         */
        static int32 isInitialized_;    
        
        /**
         * The processor module initialization stage (no boot).
         */
        static int32 stage_;
      
    };
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    int32 ProcessorController::isInitialized_;    
    
    /**
     * The processor module initialization stage (no boot).
     */
    int32 ProcessorController::stage_; 
      
}
#endif // DRIVER_PROCESSOR_CONTROLLER_HPP_
