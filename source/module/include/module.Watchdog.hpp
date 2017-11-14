/** 
 * Target processor watchdog controller factory. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_WATCHDOG_HPP_
#define MODULE_WATCHDOG_HPP_

#include "Configuration.hpp"

namespace module
{
    class Watchdog : public ::api::Object
    {
    
    public:

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
#endif // MODULE_WATCHDOG_HPP_
