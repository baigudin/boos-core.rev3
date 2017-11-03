/**
 * The operating system thread.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_THREAD_HPP_
#define SYSTEM_THREAD_HPP_

#include "system.TaskBase.hpp"
#include "api.Thread.hpp"

namespace api { class Scheduler; }

namespace system
{
    class Thread : public ::system::TaskBase, public ::api::Thread
    {
        typedef ::system::TaskBase Parent;
      
    public:
    
        /** 
         * Constructor.
         */
        Thread();    
  
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
         * The method with self context which will be executed by default.
         */  
        virtual void main();               
        
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
         * @param res a resource.
         */  
        virtual void block(::api::Resource& res);        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier.
         */
        virtual int64 getId() const;

        /**
         * Returns a status of this thread.
         *
         * @return this thread status.
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
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
         */  
        virtual void setPriority(int32 priority);
      
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        static ::api::Thread& getCurrent();
        
        /**
         * Causes current thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        static void sleepCurrent(int64 millis, int32 nanos=0);
        
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
            
    private:
        
        /**
         * Constructor.
         *
         * @param task an task interface whose main method is invoked when this thread is started.     
         * @return true if object has been constructed successfully.   
         */
        bool construct(::api::Task& task);
        
        /**
         * Tests if the module has been initialized.
         *
         * @return true if the module has been initialized successfully.
         */    
        static bool isInitialized();        
        
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
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x54298742;
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;
                  
        /**
         * The module initialization stage (no boot).
         */
        static int32 stage_;                
        
        /** 
         * A kernel scheduler (no boot).
         */          
        static ::api::Scheduler* scheduler_;
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
        
        /** 
         * A kernel scheduler thread.
         */          
        ::api::Thread* thread_;
  
    };
}
#endif // SYSTEM_THREAD_HPP_
