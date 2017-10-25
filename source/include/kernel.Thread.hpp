/**
 * The kernel thread.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_THREAD_HPP_
#define KERNEL_THREAD_HPP_

#include "Object.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"

namespace kernel
{
    class Thread : public ::Object<>, public ::api::Thread
    {
        typedef ::Object<> Parent;
      
    public:
  
        /** 
         * Constructor.
         *
         * @param task an task interface whose main method is invoked when this thread is started.
         */
        Thread(::api::Task& task);
        
        /** 
         * Destructor.
         */
        virtual ~Thread();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;        
        
        /**
         * Causes this thread to begin execution.
         */
        virtual void start();       
        
        /**
         * Waits for this thread to die.
         */  
        virtual void join();
      
        /**
         * Causes this thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual void sleep(int64 millis, int32 nanos=0);
        
        /**
         * Blocks this thread on given resource and yields the task.
         *
         * @param res reference to resource.
         */  
        virtual void block(::api::Resource& res);        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier.
         */
        virtual int64 getId() const;

        /**
         * Causes the currently executing thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual ::api::Thread::Status getStatus() const;        
      
        /**
         * Returns this thread priority.
         *
         * @return priority value.
         */  
        virtual int32 getPriority() const;
      
        /**
         * Sets this thread priority.
         *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
         */  
        virtual void setPriority(int32 priority);
      
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        static ::api::Thread& getCurrent();
        
        /**
         * Yields to next thread.
         */
        static void yield();
        
        /** 
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */ 
        static ::api::Toggle& toggle();
            
    private:
        
        /**
         * Constructor.
         */
        bool construct();
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Thread(const Thread& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Thread& operator =(const Thread& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
  
    };
}
#endif // KERNEL_THREAD_HPP_
