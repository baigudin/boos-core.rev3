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
#include "api.Task.hpp"
#include "api.Stack.hpp"
#include "api.Resource.hpp"
#include "api.Toggle.hpp"

namespace driver { class Register; }

namespace kernel
{
    class Scheduler;
  
    class Thread : public ::Object<>
    {
        friend class ::kernel::Scheduler;
        
        typedef ::Object<> Parent;
      
    public:
  
        /** 
         * Thead priority constants.
         */
        static const int32 MAX_PRIORITY  = 10;
        static const int32 MIN_PRIORITY  = 1;
        static const int32 NORM_PRIORITY = 5;
      
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
         * Waits for this thread to die.
         */  
        virtual void join();
      
        /**
         * Causes this thread to begin execution.
         */
        virtual void start();
      
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
         * Returns the identifier of this thread.
         *
         * @return the thread identifier.
         */
        virtual int64 getId();
      
        /**
         * Causes the currently executing thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        static void sleep(int64 millis, int32 nanos=0);
      
        /**
         * Yields to next thread.
         */
        static void yield();
      
        /**
         * Blocks current thread on given resource and yields the task.
         *
         * @param res reference to resource.
         */  
        static void block(::api::Resource& res);
      
        /**
         * Returns the currently executing thread.
         *
         * @return the executable thread.
         */
        static ::kernel::Thread& getCurrent();
      
        /** 
         * Returns the toggle interface for controlling global thread switch.
         *
         * @return toggle interface.
         */ 
        static ::api::Toggle& toggle();
        
        /**
         * Initializes the resource.
         *
         * @return true if no errors have been occurred.
         */   
        static bool initialize();
        
        /**
         * Deinitializes the resource.
         */
        static void deinitialize();
        
        /**
         * Initiates an execution of threads.
         */
        static void execute();        
            
    private:
    
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
         * Constructor.
         *
         * @param task an interface whose run method is invoked when this thread is started.       
         */
        bool construct(::api::Task* task);
        
        /**
         * Tests if the module has been initialized.
         *
         * @return true if the module has been initialized successfully.
         */    
        static bool isInitialized();    
    
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x75211568;    
        
        /**
         * the module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;           
        
        /**
         * The module initialization stage (no boot).
         */
        static int32 stage_;        
        
        /**
         * Counter of thread identifiers (no boot).
         */    
        static int64 idCount_;
        
        /**
         * Thread scheduler (no boot).
         */
        static Scheduler* scheduler_;
        
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
#endif // KERNEL_THREAD_HPP_
