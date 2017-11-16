/** 
 * Target processor watchdog controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Watchdog.hpp"
#include "module.Register.hpp"
#include "module.reg.System.hpp"

namespace module
{
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    ::module::Watchdog* Watchdog::create()
    {
        return NULL;  
    }
    
    /**
     * Initializes the module.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    bool Watchdog::initialize(const ::Configuration config)
    {
        reg::System* regSys = new (reg::System::ADDRESS) reg::System();  
        Register::allow();
        // Disable watchdog
        uint16 val = regSys->wdcr.val;
        val &= ~(reg::System::WDCR_M_WDDIS|reg::System::WDCR_M_WDCHK);
        val |=   reg::System::WDCR_V_WDDIS|reg::System::WDCR_V_WDCHK;
        regSys->wdcr.val = val;  
        Register::protect();    
        return true;
    }
  
    /**
     * Deinitializes the module.
     */
    void Watchdog::deinitialize()
    {
    }  
}
