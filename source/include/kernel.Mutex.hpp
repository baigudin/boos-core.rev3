/**
 * Mutex class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_MUTEX_HPP_
#define KERNEL_MUTEX_HPP_

#include "Object.hpp"
#include "api.Mutex.hpp"
#include "utility.LinkedList.hpp"

namespace kernel
{  
    class Thread;
    
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
         * The unlocked id.
         */
        static const int64 UNLOCKED_ID = -1;    
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_; 
        
        /**
         * The identifier of locked thread.
         */
        int64 id_;
        
        /**
         * The mutex counter.
         */
        int32 count_;
        
        /** 
         * Queue of locked threads.
         */     
        ::utility::LinkedList<Thread*> fifo_;    
  
    };
}
#endif // KERNEL_MUTEX_HPP_
