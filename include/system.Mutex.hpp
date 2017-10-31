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

namespace system
{
    class Mutex : public ::Object<>, public ::api::Mutex
    {
        typedef ::Object<> Parent;
  
    public:

        /** 
         * Constructor.
         */    
        Mutex();
        
        /** 
         * Destructor.
         */      
        virtual ~Mutex();
            
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;  
        
        /**
         * Locks the mutex.
         *
         * @return true if the mutex is lock successfully.
         */      
        virtual bool lock();
        
        /**
         * Unlocks the mutex.
         */      
        virtual void unlock();
        
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
         * @return true if object has been constructed successfully.   
         */
        bool construct();

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
         * Kernel mutex interface.
         */    
        ::api::Mutex* kernel_;
  
    };
}
#endif // SYSTEM_MUTEX_HPP_
