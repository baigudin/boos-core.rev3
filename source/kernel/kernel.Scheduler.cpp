/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Scheduler.hpp" 
#include "kernel.SchedulerThread.hpp" 
#include "kernel.System.hpp"
#include "driver.Interrupt.hpp"
#include "driver.Timer.hpp"
/*

#include "driver.Register.hpp"
*/  
namespace kernel
{
    /** 
     * Constructor.
     */
    Scheduler::Scheduler() :
        isConstructed_ (getConstruct()),      
        global_    (global()),
        int_       (ResInt::getDriver()),
        tim_       (ResTim::getDriver()),
        list_      (NULL){
        setConstruct( construct() );
    }
  
    /** 
     * Destructor.
     */
    Scheduler::~Scheduler()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Scheduler::isConstructed() const
    {
        return isConstructed_;
    }
  
    /** 
     * Hardware interrupt handler.
     */      
    void Scheduler::main()
    {
/*    
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
*/            
    }
    
    /**
     * Returns size of stack.
     *
     * @return stack size in bytes.
     */  
    int32 Scheduler::getStackSize() const
    {
        return 0x200;
    }
    
    /**
     * Creates a new thread.
     *
     * @param task an user task which main method will be invoked when created thread is started.
     * @return a new thread.
     */
    ::api::Thread& Scheduler::createThread(::api::Task& task)
    {
    }
    
    /**
     * Removes the first occurrence of the specified thread.
     *
     * @param thread removing thread.
     */
    void Scheduler::removeThread(::api::Thread& thread)
    {
    }
    
    /**
     * Returns currently executing thread.
     *
     * @return executing thread.
     */
    ::api::Thread& Scheduler::getCurrentThread()
    {
        if( not isConstructed_ ) System::terminate();
        bool is = global_.disable();
        ::api::Thread* thread = list_.peek();
        global_.enable(is);
        if(thread == NULL) System::terminate();
        return *thread;
    }
    
    /**
     * Yields to next thread.
     */
    void Scheduler::yield()
    {
        if( not isConstructed_ ) return;
        jump();    
    }
    
    /** 
     * Returns the toggle interface for controlling global thread switching.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Scheduler::toggle()
    {
        return *this;
    }    

    /** 
     * Constructor.
     *
     * When first scheduler timer interrupt is occurred, 
     * default registers of parent interrupt class will be used
     * for storing the operating system context to it.
     *
     * @return true if object has been constructed successfully.
     */
    bool Scheduler::construct()
    {
        if( not isConstructed() ) return false;
        if( not list_.isConstructed() ) return false;      
        int32 source = tim_.getInterrupSource();
        if( not int_.setHandler(*this, source) ) return false;
        setCount(0);
        setPeriod(QUANT);
        start();
        enable(true);
        return true;      
    }
    
    /**
     * Runs a method of Runnable interface start vector.
     */  
    void Scheduler::run()
    {
/*
        Task* current = list_.peek();
        // Start main method of user thread task
        current->task_->main();
        global_.disable();
        current->status_ = Task::DEAD;
        // Remova this executed task
        list_.remove();
        jump();
*/
    }        
    
    /**
     * Runs a method of Runnable interface start vector.
     */  
    void Scheduler::runTask(Scheduler* scheduler)
    {
/*    
        // Invoke the member function through the pointer
        void(Scheduler::*run)() = &Scheduler::run;
        (scheduler->*run)();
        // This PC is not allowable
        while(true);
*/        
    }

}
    
