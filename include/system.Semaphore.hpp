/** 
 * Semaphore class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SEMAPHORE_HPP_
#define SYSTEM_SEMAPHORE_HPP_

#include "Object.hpp"
#include "api.Semaphore.hpp"
#include "system.System.hpp"

namespace system
{
    class Semaphore : public ::Object<>, public ::api::Semaphore
    {
        typedef ::Object<> Parent;
  
    public:

        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.   
         */      
        Semaphore(int32 permits) : Parent(),
            isConstructed_ (getConstruct()),
            semaphore_     (NULL){
            setConstruct( construct(permits, NULL) ); 
        }    
        
        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         */      
        Semaphore(int32 permits, bool isFair) : Parent(),
            isConstructed_ (getConstruct()),
            semaphore_     (NULL){
            setConstruct( construct(permits, &isFair) );   
        }

        /** 
         * Destructor.
         */
        virtual ~Semaphore()
        {
            delete semaphore_;
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
         * Acquires one permit from this semaphore.
         *
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire()
        {
            if( not isConstructed_ ) return false;
            return semaphore_->acquire();    
        }        
        
        /**
         * Acquires the given number of permits from this semaphore.
         *
         * @param permits the number of permits to acquire.
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire(int32 permits)
        {
            if( not isConstructed_ ) return false;
            return semaphore_->acquire(permits);        
        }    
        
        /**
         * Releases one permit.
         */
        virtual void release()
        {
            if( not isConstructed_ ) return;
            semaphore_->release();        
        }            
        
        /**
         * Releases the given number of permits.
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits)
        {
            if( not isConstructed_ ) return;
            semaphore_->release(permits);            
        }
        
        /**
         * Tests if this semaphore is fair.
         *
         * @return true if this semaphore has fairness set true.
         */  
        virtual bool isFair() const
        {
            if( not isConstructed_ ) return false;    
            return semaphore_->isFair(); 
        }        
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked()
        {
            if( not isConstructed_ ) return false;
            return semaphore_->isBlocked();        
        }        
  
    private:
      
        /**
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.     
         * @return true if object has been constructed successfully.   
         */
        bool construct(int32 permits, bool* isFair)
        {
            if( not isConstructed_ ) return false;
            ::api::Kernel& kernel = System::call().getKernel();
            if( isFair == NULL )
            {
                semaphore_ = kernel.createSemaphore(permits);
            }
            else
            {
                semaphore_ = kernel.createSemaphore(permits, *isFair);
            }
            return semaphore_ != NULL ? semaphore_->isConstructed() : false;        
        }        

        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Semaphore(const Semaphore& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Semaphore& operator =(const Semaphore& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;    
      
        /**
         * System semaphore interface.
         */    
        ::api::Semaphore* semaphore_;
  
    };
}
#endif // SYSTEM_SEMAPHORE_HPP_
