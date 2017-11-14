/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_INTERRUPT_HPP_
#define KERNEL_INTERRUPT_HPP_

#include "Object.hpp"
#include "api.ProcessorInterrupt.hpp"
#include "module.Interrupt.hpp"

namespace module { class Interrupt; }

namespace kernel
{
    class Interrupt : public ::Object<>, public ::api::ProcessorInterrupt
    {
        typedef ::Object<> Parent;
  
    public:
      
        /** 
         * Constructor.
         */    
        Interrupt() : Parent(),
            isConstructed_ (getConstruct()),  
            module_        (NULL){
            setConstruct( construct(NULL, 0) );
        }        
        
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         */     
        Interrupt(::api::Task& handler, int32 source) : Parent(),
            isConstructed_ (getConstruct()),
            module_        (NULL){
            setConstruct( construct(&handler, source) );
        }
        
        /** 
         * Destructor.
         */
        virtual ~Interrupt()
        {
            delete module_;
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
        
        /**
         * Jumps to interrupt hardware vector.
         */      
        virtual void jump()
        {
            if( not isConstructed_ ) return;
            module_->jump();
        }
        
        /**
         * Clears an interrupt status of this source.
         */     
        virtual void clear()
        {
            if( not isConstructed_ ) return;
            module_->clear();  
        }
        
        /**
         * Sets an interrupt status of this source.
         */    
        virtual void set()
        {
            if( not isConstructed_ ) return;
            module_->set();  
        }  
        
        /**
         * Locks this interrupt source.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        virtual bool disable()
        {
            if( not isConstructed_ ) return false;  
            return module_->disable();
        }
        
        /**
         * Unlocks this interrupt source.
         *
         * @param status returned status by lock method.
         */
        virtual void enable(bool status)
        {
            if( not isConstructed_ ) return;
            module_->enable(status);  
        }        
        
        /**
         * Sets interrupt source handler.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         * @return true if handler is set successfully.
         */      
        virtual bool setHandler(::api::Task& handler, int32 source)
        {
            if( not isConstructed_ ) return false;
            return module_->setHandler(handler, source);  
        }         
        
        /**
         * Removes this interrupt source handler.
         */        
        virtual void removeHandler()
        {
            if( not isConstructed_ ) return;
            module_->removeHandler();
        }         
        
        /**
         * Sets new registers context for storing.
         * 
         * @param reg new registers context.
         */
        virtual void setContext(::api::ProcessorRegisters& reg)
        {
            if( not isConstructed_ ) return;
            module_->setContext(reg);        
        }        

        /**
         * Restores registers context for storing to the default.
         */
        virtual void restoreContext()
        {
            if( not isConstructed_ ) return;
            module_->restoreContext();        
        }               
  
    private:
      
        /**
         * Constructor.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.   
         * @param source  available interrupt source.     
         * @return true if object has been constructed successfully.     
         */    
        bool construct(::api::Task* handler, int32 source)
        {
            if( not isConstructed_ ) return false;
            ::module::Interrupt::Resource res;
            if(handler != NULL) 
            {
                res.handler = handler;
                res.source = source;    
            }
            else 
            {
                res.handler = NULL;
                res.source = 0;
            }
            module_ = ::module::Interrupt::create(res);    
            return module_ != NULL ? module_->isConstructed() : false;
        }        
                
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Interrupt(const Interrupt& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Interrupt& operator =(const Interrupt& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;    
      
        /**
         * Extended interrupt controller interface.
         */    
        ::api::ProcessorInterrupt* module_;
  
    };
}
#endif // KERNEL_INTERRUPT_HPP_
