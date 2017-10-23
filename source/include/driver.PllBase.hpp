/** 
 * Target processor phase-locked loop controller resource. 
 *
 * The class describes a skeleton implementation of a phase-locked loop resource.
 * It should be inherited by all classes, which aim expanding the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_PLL_BASE_HPP_
#define DRIVER_PLL_BASE_HPP_

#include "Object.hpp"
#include "driver.Pll.hpp"

namespace driver
{
    class PllBase : public ::Object<>, public ::driver::Pll
    {
        typedef ::Object<>  Parent;
      
    public:
    
        /** 
         * Constructor.
         */     
        PllBase() : Parent(),
            isConstructed_ (getConstruct()){
        }    
        
        /** 
         * Destructor.
         */                               
        virtual ~PllBase()
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
        PllBase(const PllBase& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        PllBase& operator =(const PllBase& obj);      
  
    };
}
#endif // DRIVER_PLL_BASE_HPP_
