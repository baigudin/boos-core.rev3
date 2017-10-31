/** 
 * Target processor watchdog controller resource. 
 *
 * The class describes a skeleton implementation of a phase-locked loop resource.
 * It should be inherited by all classes, which aim expanding the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_WATCHDOG_BASE_HPP_
#define MODULE_WATCHDOG_BASE_HPP_

#include "Object.hpp"
#include "module.Watchdog.hpp"

namespace module
{
    class WatchdogBase : public ::Object<>, public ::module::Watchdog
    {
        typedef ::Object<>  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        WatchdogBase() : Parent(),
            isConstructed_ (getConstruct()){
        }    
      
        /** 
         * Destructor.
         */                               
        virtual ~WatchdogBase()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }
      
    protected:
      
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
      
    private:
    
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        WatchdogBase(const WatchdogBase& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        WatchdogBase& operator =(const WatchdogBase& obj);      
  
    };
}
#endif // MODULE_WATCHDOG_BASE_HPP_
