/**
 * Thread class of this scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SCHEDULER_THREAD_HPP_
#define KERNEL_SCHEDULER_THREAD_HPP_

#include "Object.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "driver.Processor.hpp"
#include "driver.Register.hpp"
#include "utility.Stack.hpp"

namespace kernel
{      
    class SchedulerThread : public ::Object<>, public ::api::Thread
    {
        typedef ::Object<> Parent;
    
    public:
    
        /** 
         * Constructor.
         *
         * @param task an task interface whose main method is invoked when this thread is started.
         */
        SchedulerThread(::api::Task& task) : Parent(),
            isConstructed_ (getConstruct()){
            setConstruct( construct() );
        }
        
        /** 
         * Destructor.
         */
        virtual ~SchedulerThread()
        {
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
         * Causes this thread to begin execution.
         */
        virtual void start()
        {
        }       
        
        /**
         * Waits for this thread to die.
         */  
        virtual void join()
        {
        }
        
        /**
         * Causes this thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual void sleep(int64 millis, int32 nanos)
        {
        }
        
        /**
         * Blocks this thread on given resource and yields the task.
         *
         * @param res reference to resource.
         */  
        virtual void block(::api::Resource& res)
        {
        }        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier.
         */
        virtual int64 getId() const
        {
        }

        /**
         * Causes the currently executing thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual Status getStatus() const
        {
        }        
        
        /**
         * Returns this thread priority.
         *
         * @return priority value.
         */  
        virtual int32 getPriority() const
        {
        }
        
        /**
         * Sets this thread priority.
         *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
         */  
        virtual void setPriority(int32 priority)
        {
        }
        
    private:
    
        /** 
         * Constructor.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        SchedulerThread(const SchedulerThread& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        SchedulerThread& operator =(const SchedulerThread& obj);        
    
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;         
        
        /**
         * User executing runnable interface.
         */        
        ::api::Task* task_;
        
        /**
         * Given blocked resource.
         */        
        ::api::Resource* block_;
        
        /**
         * CPU state registers.
         */        
        ::driver::Register* register_;
        
        /**
         * Thread stack.
         */        
        ::api::Stack<int64>* stack_;
        
        /**
         * Current identifier.
         */        
        int64 id_;
        
        /**
         * Current priority.
         */        
        int32 priority_;
        
        /**
         * Wake up time in nanoseconds.
         */        
        int64 sleep_;    
        
        /**
         * Current status.
         */        
        Status status_;            

    };
}
#endif // KERNEL_SCHEDULER_THREAD_HPP_
