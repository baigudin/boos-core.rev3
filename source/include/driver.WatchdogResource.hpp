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
#ifndef DRIVER_WATCHDOG_RESOURCE_HPP_
#define DRIVER_WATCHDOG_RESOURCE_HPP_

#include "Object.hpp"
#include "driver.Watchdog.hpp"

namespace driver
{
    class WatchdogResource : public ::Object<>, public ::driver::Watchdog
    {
        typedef ::Object<>  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        WatchdogResource() : Parent(),
            isConstructed_ (getConstruct()){
        }    
      
        /** 
         * Destructor.
         */                               
        virtual ~WatchdogResource()
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
        WatchdogResource(const WatchdogResource& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        WatchdogResource& operator =(const WatchdogResource& obj);      
  
    };
}
#endif // DRIVER_WATCHDOG_RESOURCE_HPP_
