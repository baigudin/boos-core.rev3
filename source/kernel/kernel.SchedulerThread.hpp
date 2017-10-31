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
#include "kernel.Kernel.hpp"
#include "module.Interrupt.hpp"
#include "module.Processor.hpp"
#include "module.Register.hpp"
#include "library.Stack.hpp"

namespace kernel
{      
    class SchedulerThread : public ::Object<>, public ::api::Thread
    {
        typedef ::Object<>               Parent;
        typedef ::library::Stack<int64>  Stack;
        typedef ::module::Interrupt      Int;
    
    public:
    
        /** 
         * Constructor of not constructed object.
         *
         * @param task an task interface whose main method is invoked when this thread is started.
         */
        SchedulerThread() : Parent(),
            isConstructed_ (getConstruct()),
            register_  (NULL),
            stack_     (NULL),            
            task_      (NULL),
            scheduler_ (NULL),            
            block_     (NULL),
            id_        (-1),
            priority_  (NORM_PRIORITY),
            sleep_     (0),
            status_    (DEAD){
            setConstruct( false );
        }    
    
        /** 
         * Constructor.
         *
         * @param task     an task interface whose main method is invoked when this thread is started.
         * @param id       this thread ID.
         * @param schInt   the scheduler interrupt resource.
         * @param entry    router entry point.
         * @param argument first router argument.         
         */
        SchedulerThread(::api::Task& task, int64 id, void (*entry)(::kernel::Scheduler*), Scheduler* scheduler) : Parent(),
            isConstructed_ (getConstruct()),
            register_  (NULL),
            stack_     (NULL),            
            task_      (&task),
            scheduler_ (scheduler),
            block_     (NULL),
            id_        (id),
            priority_  (NORM_PRIORITY),
            sleep_     (0),
            status_    (NEW){
            setConstruct( construct(entry, scheduler) );
        }
        
        /** 
         * Destructor.
         */
        virtual ~SchedulerThread()
        {
            scheduler_->removeThread(this);
            delete stack_;    
            stack_ = NULL;
            delete register_;
            register_ = NULL;        
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
            if( not isConstructed_ ) return;
            if( status_ != NEW ) return;
            bool is = Int::disableAll();
            scheduler_->addThread(this);
            status_ = RUNNABLE;  
            Int::enableAll(is);              
        }       
        
        /**
         * Waits for this thread to die.
         */  
        virtual void join()
        {
            if( not isConstructed_ ) return; 
            bool is = Int::disableAll();
            // TODO: check that task has been added to the list
            while(status_ != DEAD) scheduler_->yield();        
            Int::enableAll(is);                
        }
        
        /**
         * Causes this thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        virtual void sleep(int64 millis, int32 nanos)
        {
            bool is = Int::disableAll();
            status_ = SLEEPING;            
            sleep_ = Kernel::getKernel().getExecutionTime().getValue() + millis * 1000000 + nanos;
            scheduler_->yield();
            Int::enableAll(is);        
        }
        
        /**
         * Blocks this thread on given resource and yields the task.
         *
         * @param res a resource.
         */  
        virtual void block(::api::Resource& res)
        {
            if( not isConstructed_ ) return;            
            bool is = Int::disableAll();
            status_ = BLOCKED;
            block_ = &res;
            scheduler_->yield();
            Int::enableAll(is);                
        }        
        
        /**
         * Returns the identifier of this thread.
         *
         * @return the thread identifier, or -1 if error has been occurred.
         */
        virtual int64 getId() const
        {
            return isConstructed_ ? id_ : -1;
        }
        
        /**
         * Returns this thread priority.
         *
         * @return priority value, or -1 if error has been occurred.
         */  
        virtual int32 getPriority() const
        {
            return isConstructed_ ? priority_ : -1;        
        }
        
        /**
         * Sets this thread priority.
         *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
         */  
        virtual void setPriority(int32 priority)
        {
            if( not isConstructed_ ) return;
            if(priority == LOCK_PRIORITY)
                priority_ = LOCK_PRIORITY;
            else if(priority > MAX_PRIORITY) 
                priority_ = MAX_PRIORITY;
            else if(priority < MIN_PRIORITY) 
                priority_ = MIN_PRIORITY;
            else 
                priority_ = priority;        
        }
        

        /**
         * Returns a status of this thread.
         *
         * @return this thread status.
         */  
        virtual Status getStatus() const
        {
            return isConstructed_ ? status_ : DEAD;
        }
        
        /**
         * Sets new status of this thread.
         *
         * @param new thread status.
         */  
        void setStatus(Status status)
        {
            status_ = status;
        } 
        
        /**
         * Return wake up time in nanoseconds.
         *
         * @return this thread wake up.
         */        
        int64 getSleep()
        {
            return sleep_;
        }
        
        /**
         * Sets new status of this thread.
         *
         * @param new wake up time.
         */        
        void setSleep(int64 sleep)
        {
            sleep_ = sleep;
        }        

        /**
         * Return blocked resource.
         *
         * NOTE: Never call delete operation for returned value!
         * 
         * @return this thread blocked resource.         
         */        
        ::api::Resource* getBlock()
        {
            return block_;
        }
        
        /**
         * Returns registers of this thread.
         *
         * NOTE: Never call delete operation for returned value!         
         *
         * @return this thread registers.     
         */        
        ::module::Register* getRegister()
        {
            return register_;
        }

        /**
         * Returns user executing runnable interface of this thread.
         *
         * NOTE: Never call delete operation for returned value!         
         *
         * @return this thread user executing runnable interface.     
         */    
        ::api::Task* getTask()
        {
            return task_;                 
        }
        
        
    private:
    
        /** 
         * Constructor.
         *
         * @param entry    router entry point.
         * @param argument first router argument.                  
         * @return true if object has been constructed successfully.
         */
        bool construct(void (*entry)(::kernel::Scheduler*), Scheduler* argument)
        {
            if( not isConstructed_ ) return false;  
            if( not task_->isConstructed() ) return false;    
            // Set this thread CPU registers context 
            register_ = ::module::Register::create();
            if(register_ == NULL || not register_->isConstructed()) return false;
            // Set this thread stack context 
            stack_ = new Stack( ::module::Processor::getStackType(), task_->getStackSize() >> 3 );    
            if(stack_ == NULL || not stack_->isConstructed()) return false;
            // Set default registers value
            int32 foo = reinterpret_cast<int32>(entry);
            int32 arg = reinterpret_cast<int32>(argument);
            register_->setInitialization(*stack_, foo, arg, 0);            
            return true;
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
         * CPU state registers.
         */        
        ::module::Register* register_;
        
        /**
         * Thread stack.
         */        
        ::api::Stack<int64>* stack_;
        
        /**
         * User executing runnable interface.
         */        
        ::api::Task* task_;

        /**
         * The scheduler resource.
         */
        Scheduler* scheduler_;
        
        /**
         * Given blocked resource.
         */        
        ::api::Resource* block_;        
        
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
