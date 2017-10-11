/** 
 * TI TMS320F28x3x DSC Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Sergey Baigudin
 */
#ifndef DRIVER_PLL_CONTROLLER_HPP_
#define DRIVER_PLL_CONTROLLER_HPP_

#include "driver.PllResource.hpp"
#include "driver.Register.hpp"
#include "driver.reg.System.hpp"

namespace driver
{
    class PllController : public ::driver::PllResource
    {
        typedef ::driver::PllResource Parent;      
      
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
            isInitialized_ = 0;    
            cpuClock_ = config.cpuClock;
            sourceClock_ = config.sourceClock;      
            reg::System* regSys = 
                new (reg::System::ADDRESS) reg::System();
            int32 sel = 0x2;
            // Multiply desired CPU clock by 2, as PLLSTS[DIVSEL] is 2
            int32 mul = ( cpuClock_ * 2 / sourceClock_ ) & 0xffffffff;
            // Output frequency of the PLL (VCOCLK) 
            // does not exceed 300 MHz
            if(sourceClock_ * mul > 300000000) return false;
            // Multipliers more than 10 are reserved
            if(mul > 10) return false;
            // Test the oscillator is not off
            if(regSys->pllsts.bit.oscoff == 1) return false;
            // Test the PLL is set correctly
            if(regSys->pllsts.bit.plloff == 1 
                && regSys->pllcr.bit.div > 0) return false;
            // Start changing procedure
            if(regSys->pllsts.bit.mclksts == 1) return false;    
            Register::allow();
            // Set division to four
            if(regSys->pllsts.bit.divsel != 0) 
                regSys->pllsts.bit.divsel = 0;
            // Disable failed oscillator detect logic
            regSys->pllsts.bit.mclkoff = 1;
            // Set new PLL
            regSys->pllcr.bit.div = mul;
            // Test PLL is locked
            while(regSys->pllsts.bit.plllocks != 1);
            // Enable failed oscillator detect logic
            regSys->pllsts.bit.mclkoff = 0;
            // Set divider
            regSys->pllsts.bit.divsel = sel;
            Register::protect();
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
         * The driver initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x95633217;    
        
        /**
         * Driver has been initialized successfully (no boot).
         */
        static int32 isInitialized_;    
        
        /**
         * Reference clock rate in Hz (no boot).
         */      
        static int64 sourceClock_;
        
        /**
         * ARM clock rate in Hz (no boot).
         */      
        static int64 cpuClock_;
      
    };
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    int32 PllController::isInitialized_;  
    
    /**
     * Reference clock rate in Hz (no boot).
     */      
    int64 PllController::sourceClock_;
    
    /**
     * ARM clock rate in Hz (no boot).
     */      
    int64 PllController::cpuClock_;

}
#endif // DRIVER_PLL_CONTROLLER_HPP_
