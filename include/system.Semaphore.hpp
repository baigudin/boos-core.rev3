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
        Semaphore(int32 permits);
        
        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.
         */      
        Semaphore(int32 permits, bool isFair);

        /** 
         * Destructor.
         */
        virtual ~Semaphore();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;
        
        /**
         * Acquires one permit from this semaphore.
         *
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire();
        
        /**
         * Acquires the given number of permits from this semaphore.
         *
         * @param permits the number of permits to acquire.
         * @return true if the semaphore is acquired successfully.
         */  
        virtual bool acquire(int32 permits);
        
        /**
         * Releases one permit.
         */
        virtual void release();
        
        /**
         * Releases the given number of permits.
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits);
        
        /**
         * Tests if this semaphore is fair.
         *
         * @return true if this semaphore has fairness set true.
         */  
        virtual bool isFair() const;
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked();
  
    private:
      
        /**
         * Constructor.
         *
         * @param permits the initial number of permits available.      
         * @param isFair  true if this semaphore will guarantee FIFO granting of permits under contention.     
         * @return true if object has been constructed successfully.   
         */
        bool construct(int32 permits, bool* isFair);

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
         * Kernel semaphore interface.
         */    
        ::api::Semaphore* kernel_;
  
    };
}
#endif // SYSTEM_SEMAPHORE_HPP_
