/**
 * the factory of the operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_FACTORY_CREATOR_HPP_
#define KERNEL_FACTORY_CREATOR_HPP_

#include "kernel.FactoryBase.hpp"
#include "kernel.Semaphore.hpp"
#include "kernel.Interrupt.hpp"

namespace kernel
{
    class FactoryCreator : public ::kernel::FactoryBase
    {
        typedef ::kernel::FactoryBase Parent;
      
    public:
    
        /** 
         * Constructor.
         */    
        FactoryCreator() : Parent(){    
            setConstruct( construct() );    
        }        
  
        /** 
         * Destructor.
         */
        virtual ~FactoryCreator(){}
        
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.   
         * @return new semaphore resource, or NULL if error has been occurred.
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits)
        {
            ::api::Semaphore* res = new Semaphore(permits);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL;   
        }
        
        /** 
         * Creates new semaphore resource.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         * @return new semaphore resource, or NULL if error has been occurred.         
         */      
        virtual ::api::Semaphore* createSemaphore(int32 permits, bool isFair)
        {
            ::api::Semaphore* res = new Semaphore(permits, isFair);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL; 
        }        
        
        /**
         * Creates new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return new interrupt resource.
         */
        virtual ::api::Interrupt* createInterrupt(::api::Task& handler, int32 source)
        {
            ::api::Interrupt* res = new Interrupt(handler, source);
            if(res == NULL) return NULL; 
            if(res->isConstructed()) return res;       
            delete res;
            return NULL;       
        }
        
    private:
    
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            if( not isConstructed_ ) return false;
            return true;
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        FactoryCreator(const FactoryCreator& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        FactoryCreator& operator =(const FactoryCreator& obj);            
        
    };
}
#endif // KERNEL_FACTORY_CREATOR_HPP_
