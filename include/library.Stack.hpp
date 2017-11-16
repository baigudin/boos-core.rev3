/**
 * Stack.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef LIBRARY_STACK_HPP_
#define LIBRARY_STACK_HPP_

#include "Object.hpp"
#include "api.Stack.hpp"
#include "library.Buffer.hpp"

namespace library
{
    /** 
     * @param Type  data type of default stack element.
     * @param Alloc heap memory allocator class.
     */ 
    template <typename Type, class Alloc=::Allocator>
    class Stack : public ::Object<Alloc>, public ::api::Stack<Type>
    { 
        typedef ::Object<Alloc>    Parent;  
        typedef ::api::Stack<Type> StackIntf;
    
    public:
    
        /** 
         * Constructor.
         *
         * @param type  type of this stack.
         * @param count count of buffer elements.
         */    
        Stack(typename ::api::Stack<Type>::Operation type, int32 count) : Parent(),
            stack_ (count),
            type_  (type){
            this->setConstruct( construct() );
        }     
        
        /** 
         * Constructor.
         *
         * @param type  type of this stack.     
         * @param count   count of buffer elements.
         * @param illegal illegal value.
         */    
        Stack(typename ::api::Stack<Type>::Operation type, int32 count, const Type illegal) : Parent(),
            stack_ (count, illegal),
            type_  (type){
            this->setConstruct( construct() );
        }    
        
        /** 
         * Destructor.
         */    
        virtual ~Stack()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */
        virtual bool isConstructed() const
        {
            return this->Parent::isConstructed();
        }
      
        /** 
         * Returns an initial top of stack.
         *
         * @return pointer to TOS.
         */    
        virtual const Type* getTos()
        {
            if(!isConstructed()) return NULL;
            Type* stack = &stack_[0];
            switch(type_)
            {
                case StackIntf::FD: 
                    return &stack[stack_.getLength()];
                    
                case StackIntf::ED: 
                    return &stack[stack_.getLength() - 1];
                    
                case StackIntf::FA: 
                    return &stack[0] - 1;
                    
                case StackIntf::EA: 
                    return &stack[0];
                    
                default: 
                    return NULL;  
            }
        }
        
        /** 
         * Returns an type of stack operation.
         *
         * @return the stack operation.
         */    
        virtual typename ::api::Stack<Type>::Operation getType() const
        {
            return type_;
        }
        
        /**
         * Returns a number of elements.
         *
         * @return number of elements.
         */
        virtual int32 getLength() const
        {
            return stack_.getLength();
        }
      
        /**
         * Tests if this collection has elements.
         *
         * @return true if this collection does not contain any elements.
         */
        virtual bool isEmpty() const
        {
            return false;
        }
      
        /**
         * Returns illegal element which will be returned as error value.
         *
         * If illegal value is not set method returns uninitialized variable.
         *
         * @return reference to illegal element.
         */
        virtual Type getIllegal() const
        {
            return stack_.getIllegal();
        }
      
        /**
         * Sets illegal element which will be returned as error value.
         *
         * @param value illegal value.
         */
        virtual void setIllegal(const Type value)
        {
            return stack_.setIllegal(value);
        }
      
        /**
         * Tests if given value is an illegal.
         *
         * @param value testing value.
         * @param true if value is an illegal.
         */
        virtual bool isIllegal(const Type& value) const
        {
            return stack_.isIllegal(value);
        }
      
    private:
  
        /** 
         * Constructor.
         *
         * @return boolean result.
         */
        bool construct()
        {
            if(!isConstructed()) return false;
            if(!stack_.isConstructed()) return false;
            #ifdef EOOS_DEBUG
            stack_.fill(0);
            #endif
            return true;
        }
      
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Stack(const Stack& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Stack& operator =(const Stack& obj);
      
        /**
         * Stack memory buffer.
         */
        Buffer<Type,0,Alloc> stack_;
      
        /**
         * Stack type.
         */    
        const typename ::api::Stack<Type>::Operation type_;
  
    };
}
#endif // LIBRARY_STACK_HPP_
