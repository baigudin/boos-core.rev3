/** 
 * TI TMS320C64x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_PLL_CONTROLLER_HPP_
#define MODULE_PLL_CONTROLLER_HPP_

#include "module.PllBase.hpp"

namespace module
{
    class PllController : public ::module::PllBase
    {
        typedef ::module::PllBase  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        PllController() : Parent()
        {
            setConstruct( construct() );    
        }
        
        /** 
         * Destructor.
         */
        virtual ~PllController()
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
            isInitialized_ = IS_INITIALIZED;                
            return true;
        }
      
        /**
         * Deinitialization.
         */
        static void deinitialize()
        {
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
        PllController(const PllController& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        PllController& operator =(const PllController& obj);
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x95633217;    
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;        
      
    };
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 PllController::isInitialized_;  
  
}
#endif // MODULE_PLL_CONTROLLER_HPP_
