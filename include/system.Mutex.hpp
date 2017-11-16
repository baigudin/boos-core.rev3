/** 
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MUTEX_HPP_
#define SYSTEM_MUTEX_HPP_

#include "Object.hpp"
#include "api.Mutex.hpp"
#include "system.System.hpp"

namespace system
{
    class Mutex : public ::Object<>, public ::api::Mutex
    {
        typedef ::Object<> Parent;
  
    public:

        /** 
         * Constructor.
         */    
        Mutex() : Parent(),
            isConstructed_ (getConstruct()),
            mutex_         (NULL){
            setConstruct( construct() ); 
        }    
        
        /** 
         * Destructor.
         */      
        virtual ~Mutex()
        {
            delete mutex_;
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
         * Locks the mutex.
         *
         * @return true if the mutex is lock successfully.
         */      
        virtual bool lock()
        {
            if( not isConstructed_ ) return false;
            return mutex_->lock();
        }
        
        /**
         * Unlocks the mutex.
         */      
        virtual void unlock()
        {
            if( not isConstructed_ ) return ;
            mutex_->unlock();
        }
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked()
        {
            if( not isConstructed_ ) return false;
            return mutex_->isBlocked();
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
            ::api::Kernel& kernel = System::call().getKernel();
            mutex_ = kernel.createMutex();
            return mutex_ != NULL ? mutex_->isConstructed() : false;        
        }

        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Mutex(const Mutex& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Mutex& operator =(const Mutex& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;    
      
        /**
         * System mutex interface.
         */    
        ::api::Mutex* mutex_;
  
    };
}
#endif // SYSTEM_MUTEX_HPP_
