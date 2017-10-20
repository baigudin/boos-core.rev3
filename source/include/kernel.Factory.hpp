/**
 * Factory of an operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_FACTORY_HPP_
#define KERNEL_FACTORY_HPP_

#include "Object.hpp"
#include "api.Kernel.hpp"

namespace kernel
{
    class Factory : public ::Object<>, public ::api::Kernel
    {
        typedef ::Object<> Parent;
      
    public:
    
        /** 
         * Constructor.
         */    
        Factory();    
  
        /** 
         * Destructor.
         */
        virtual ~Factory();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;        
        
        /**
         * Creates new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return new interrupt resource.
         */  
        virtual ::api::Interrupt* createInterrupt(::api::Task& handler, int32 source);
    
    private:
    
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct();
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Factory(const Factory& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Factory& operator =(const Factory& obj);            
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;          
 
    };
}
#endif // KERNEL_FACTORY_HPP_
