/** 
 * Root class of the kernel class hierarchy.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_OBJECT_HPP_
#define KERNEL_OBJECT_HPP_

#include "Object.hpp"
#include "kernel.Allocator.hpp"

namespace kernel
{
    class Object : public ::Object<Allocator>
    {
        typedef ::Object<Allocator> Parent;        
      
    public:
    
        /** 
         * Constructor.
         */  
        Object() : Parent(),
            isConstructed_ (getConstruct()){
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        Object(const Object& obj) : Parent(obj),
            isConstructed_ (getConstruct()){
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        Object(const ::api::Object& obj) : Parent(obj),
            isConstructed_ (getConstruct()){
        }    
        
        /** 
         * Destructor.
         */    
        virtual ~Object()
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
    
    };
}
#endif // KERNEL_OBJECT_HPP_
