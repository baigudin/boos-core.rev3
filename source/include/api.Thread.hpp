/**
 * Thread interface.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_THREAD_HPP_
#define API_THREAD_HPP_

#include "api.Object.hpp"
#include "api.Resource.hpp"

namespace api
{
    class Thread : public ::api::Object
    {
      
    public:
    
        /** 
         * Maximum thead priority.
         */
        static const int32 MAX_PRIORITY  = 10;
        
        /** 
         * Minimum thead priority.
         */        
        static const int32 MIN_PRIORITY  = 1;        
        
        /** 
         * Normal thead priority.
         */        
        static const int32 NORM_PRIORITY = 5;        
        
        /** 
         * Thead locked on executing priority.
         */        
        static const int32 LOCK_PRIORITY  = 0;        

        /** 
         * Thread available statuses.
         */
        enum Status
        {
            NEW      = 0,
            RUNNABLE = 1,
            RUNNING  = 2,
            WAITING  = 3,
            BLOCKED  = 4,
            SLEEPING = 5,
            DEAD     = 6
        };        
  
        /** 
         * Destructor.
         */
        virtual ~Thread(){}
        
        /**
         * Causes this thread to begin execution.
         */
        virtual void start() = 0;       
        
        /**
         * Waits for this thread to die.
         */  
        virtual void join() = 0;
      
        /**
         * Causes this thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual void sleep(int64 millis, int32 nanos=0) = 0;
        
        /**
         * Blocks this thread on given resource and yields the task.
         *
         * @param res reference to resource.
         */  
        virtual void block(::api::Resource& res) = 0;        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier.
         */
        virtual int64 getId() const = 0;

        /**
         * Causes the currently executing thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual Status getStatus() const = 0;        
      
        /**
         * Returns this thread priority.
         *
         * @return priority value.
         */  
        virtual int32 getPriority() const = 0;
      
        /**
         * Sets this thread priority.
         *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
         */  
        virtual void setPriority(int32 priority) = 0;
         
    };
}
#endif // API_THREAD_HPP_
