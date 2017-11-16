/** 
 * TI AM18x processor family.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_PROCESSOR_CONTROLLER_HPP_
#define MODULE_PROCESSOR_CONTROLLER_HPP_

#include "module.ProcessorBase.hpp"
#include "module.Pll.hpp"
#include "module.Register.hpp"
#include "module.Interrupt.hpp"
#include "module.Timer.hpp"

namespace module
{
    class ProcessorController : public ::module::ProcessorBase
    {
        typedef ::module::ProcessorBase  Parent;
      
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
            if( not ::module::Pll::initialize(config) ) return false;    
            // Stage 2 
            stage_++;
            if( not ::module::Register::initialize(config) ) return false;
            // Stage 3 
            stage_++;
            if( not ::module::Interrupt::initialize(config) ) return false;
            // Stage 4 
            stage_++;
            if( not ::module::Timer::initialize(config) ) return false;
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
                case 4: 
                    ::module::Timer::deinitialize();
                    
                case 3: 
                    ::module::Interrupt::deinitialize();
                    
                case 2: 
                    ::module::Register::deinitialize();      
                case 1: 
                    ::module::Pll::deinitialize();
                    
                case 0: 
                    break;
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
        ProcessorController& operator =(const ProcessorController& obj);
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x65437165;    
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;    
        
        /**
         * The processor internal module initialization stage (no boot).
         */
        static int32 stage_;
      
    };
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 ProcessorController::isInitialized_;    
    
    /**
     * The processor internal module initialization stage (no boot).
     */
    int32 ProcessorController::stage_; 
      
}
#endif // MODULE_PROCESSOR_CONTROLLER_HPP_
