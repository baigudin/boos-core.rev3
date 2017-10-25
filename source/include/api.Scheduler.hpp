/**
 * Threads scheduler interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_SCHEDULER_HPP_
#define API_SCHEDULER_HPP_

#include "api.Object.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "api.Toggle.hpp"

namespace api
{
    class Scheduler : public ::api::Object
    {
      
    public:
  
        /** 
         * Destructor.
         */
        virtual ~Scheduler(){}
        
        /**
         * Creates a new thread.
         *
         * @param task an user task which main method will be invoked when created thread is started.
         * @return a new thread.
         */
        virtual ::api::Thread& createThread(::api::Task& task) = 0;
        
        /**
         * Removes the first occurrence of the specified thread.
         *
         * @param thread removing thread.
         */
        virtual void removeThread(::api::Thread& thread) = 0;
        
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        virtual ::api::Thread& getCurrentThread() = 0;
        
        /**
         * Yields to next thread.
         */
        virtual void yield() = 0;
        
        /** 
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */ 
        virtual ::api::Toggle& toggle() = 0;

    };
}
#endif // API_SCHEDULER_HPP_
