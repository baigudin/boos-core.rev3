/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_SCHEDULER_HPP_
#define SYSTEM_SCHEDULER_HPP_

#include "system.System.hpp"
#include "system.TimerInterrupt.hpp"
#include "system.Thread.hpp"
#include "utility.LinkedList.hpp"
#include "driver.Interrupt.hpp"
#include "driver.Timer.hpp"
#include "driver.Register.hpp"
  
namespace system
{
    class Scheduler : public ::system::TimerInterrupt, public ::api::Task
    {
        typedef ::system::TimerInterrupt Parent;
        typedef ::system::Interrupt      ResInt;    
        typedef ::system::Timer          ResTim;
        typedef ::system::Thread         Task;
        using Parent::start;
  
    public:
  
        /** 
         * Constructor.
         */
        Scheduler() :
            global_    (global()),
            int_       (ResInt::getDriver()),
            tim_       (ResTim::getDriver()),
            list_      (NULL){
            setConstruct( construct() );
        }
      
        /** 
         * Destructor.
         */
        virtual ~Scheduler()
        {
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return this->Parent::isConstructed();
        }
      
        /** 
         * Hardware interrupt handler.
         */      
        virtual void main()
        {
            Task* task;
            // Test for completing execution
            if( list_.isEmpty() )
            {
                int_.restoreContext();
                tim_.stop();        
                tim_.setCount(0);
                tim_.setPeriod();
                return;
            }
            // Select next thread for executing
            while(true)
            {
                task = list_.peek();
                switch(task->status_)
                {
                    case Task::BLOCKED: 
                    {
                        if(!task->block_->isBlocked())
                            task->status_ = Task::RUNNABLE;
                    }
                    break;
                    case Task::SLEEPING: 
                    {
                        if(System::getTimeNs() >= task->sleep_)
                        {
                            task->sleep_ = 0;
                            task->status_ = Task::RUNNABLE;
                        }
                    }
                    break;             
                    case Task::RUNNING: 
                    {
                        task->status_ = Task::RUNNABLE;
                    }
                    break;
                    case Task::RUNNABLE: 
                    {
                        task->status_ = Task::RUNNING;
                        // Switch to the task
                        int_.setContext(*task->register_);
                        tim_.setCount(0);
                        tim_.setPeriod(task->priority_ * QUANT);
                        return;
                    }
                    default: break;
                }
                list_.remove();
                list_.add(task);
            }
        }
        
        /**
         * Returns size of stack.
         *
         * @return stack size in bytes.
         */  
        virtual int32 getStackSize() const
        {
            return 0x200;
        }
      
        /**
         * Begins to execute a task.
         *
         * @param task started task.
         */
        void start(Task& task)
        {
            if(!isConstructed()) return;
            if(!task.isConstructed()) return;
            bool is = global_.disable();
            if(task.status_ != Task::NEW) return global_.enable(is);        
            task.status_ = Task::RUNNABLE;
            // Set default registers value
            int32 entry = reinterpret_cast<int32>(runTask);
            int32 arg = reinterpret_cast<int32>(this);
            task.register_->setInitialization(*task.stack_, entry, arg, 0);
            // TODO: check that task has not been added to the list
            // ...
            // Link the task
            list_.add(&task);
            global_.enable(is);
        }
      
        /**
         * Removes the first occurrence of the specified task.
         *
         * @param task removing task.
         */
        void remove(Task& task)
        {
            if(!isConstructed()) return;
            bool is = global_.disable();
            list_.removeElement(&task);
            global_.enable(is);    
        }
      
        /**
         * Waits for this thread to die.
         *
         * @param task.
         */
        void join(Task& task)
        {
            if(!isConstructed()) return;    
            if(!task.isConstructed()) return;
            // TODO: check that task has been added to the list
            while(task.status_ != Task::DEAD) jump();    
        }
      
        /**
         * Blocks current task on given resourse and yeilds the task.
         *
         * @param res pointer to resource.
         */  
        void block(::api::Resource& block)
        {
            bool is = global_.disable();
            Task* task = list_.peek();
            if(task == NULL) return global_.enable(is);    
            task->status_ = Task::BLOCKED;
            task->block_ = &block;
            jump();
            global_.enable(is);    
        }
      
        /**
         * Causes the currently executing thread to sleep.
         *
         * @param millis a time to sleep in milliseconds.
         * @param nanos  an additional nanoseconds to sleep.
         */  
        void sleep(int64 millis, int64 nanos)
        {
            bool is = global_.disable();
            Task* task = list_.peek();
            if(task == NULL) return global_.enable(is);    
            task->status_ = Task::SLEEPING;            
            task->sleep_ = System::getTimeNs() + millis * 1000000 + nanos;
            jump();
            global_.enable(is);    
        }
      
        /**
         * Returns a pointer to the currently executing task.
         *
         * @return the executable task, or NULL if error has been occurred.
         */
        Task* currentTask()
        {
            bool is = global_.disable();    
            Task* task = list_.peek();
            global_.enable(is);
            return task;
        }
      
        /**
         * Initiates an execution of thread tasks.
         */  
        void execute()
        {
            if(list_.peek() == NULL) return;
            // Set timer counter to zero and clear interrupt flag,
            // because the timer might have been worked.
            tim_.setCount(0);      
            int_.clear();
            global_.enable(true);
            jump();
            global_.disable();    
        }
  
    private:
  
        /** 
         * Constructor.
         *
         * When first scheduler timer interrupt is occurred, 
         * default registers of parent interrupt class will be used
         * for storing the operating system context to it.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            if(!isConstructed()) return false;
            if(!list_.isConstructed()) return false;      
            int32 source = tim_.getInterrupSource();
            if(!int_.setHandler(*this, source)) return false;
            setCount(0);
            setPeriod(QUANT);
            start();
            enable(true);
            return true;      
        }
        
        /**
         * Runs a method of Runnable interface start vector.
         */  
        void run()
        {
            Task* current = list_.peek();
            // Start main method of user thread task
            current->task_->main();
            global_.disable();
            current->status_ = Task::DEAD;
            // Remova this executed task
            list_.remove();
            jump();
        }        
        
        /**
         * Runs a method of Runnable interface start vector.
         */  
        static void runTask(Scheduler* scheduler)
        {
            // Invoke the member function through the pointer
            void(Scheduler::*run)() = &Scheduler::run;
            (scheduler->*run)();
            // This PC is not allowable
            while(true);
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Scheduler(const Scheduler& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Scheduler& operator =(const Scheduler& obj);      
        
        /**
         * Process switch time in microseconds.
         */  
        static const int32 QUANT = 1000;
        
        /**
         * Global interrupt controller.
         */
        ::api::Toggle& global_;
      
        /**
         * Driver interrupt controller.
         */    
        ::driver::Interrupt& int_;
        
        /**
         * Driver timer controller.
         */    
        ::driver::Timer& tim_;
        
        /**
         * The tasks list.
         */    
        ::utility::LinkedList<Task*> list_;
  
    };
}
#endif // SYSTEM_SCHEDULER_HPP_
