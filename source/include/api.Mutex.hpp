/**
 * Mutex interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2016 Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_MUTEX_HPP_
#define API_MUTEX_HPP_

#include "api.Resource.hpp"

namespace api
{  
    class Mutex : public ::api::Resource
    {
  
    public:
    
        /** 
         * Destructor.
         */
        virtual ~Mutex(){}
        
        /**
         * Locks this mutex.
         *
         * @return true if this mutex is locked successfully.
         */
        virtual bool lock() = 0;
        
        /**
         * Unlocks this mutex.
         */
        virtual void unlock() = 0;   
        
        /**
         * Unlocks this mutex.       
         *
         * @param value a value which will be returned.
         * @return given argument value.
         */
        template<typename Type> 
        Type unlock(Type value)
        {
          unlock();
          return value;
        }
  
    };
}
#endif // API_MUTEX_HPP_
