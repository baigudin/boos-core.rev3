/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Scheduler.hpp" 
#include "kernel.SchedulerThread.hpp" 
#include "kernel.Kernel.hpp"
#include "module.Interrupt.hpp"
#include "module.Timer.hpp"

typedef ::module::Interrupt Int;

namespace kernel
{
    /** 
     * Constructor.
     */
    Scheduler::Scheduler() : Parent(),
        isConstructed_ (getConstruct()),      
        int_           (ResInt::getDriver()),
        tim_           (ResTim::getDriver()),
        list_          (NULL),
        idCount_       (0){
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
        SchedulerThread* thread;
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
            thread = list_.peek();
            switch( thread->getStatus() )
            {
                case ::api::Thread::BLOCKED: 
                    if( not thread->getBlock()->isBlocked() )
                    {
                        thread->setStatus( ::api::Thread::RUNNABLE );
                    }
                    break;
                    
                case ::api::Thread::SLEEPING: 
                    if( Kernel::call().getExecutionTime().getValue() >= thread->getSleep() )
                    {
                        thread->setSleep(0);
                        thread->setStatus( ::api::Thread::RUNNABLE );
                    }
                    break;             
                    
                case ::api::Thread::RUNNING: 
                    thread->setStatus( ::api::Thread::RUNNABLE );
                    break;
                    
                case ::api::Thread::RUNNABLE:
                {
                    thread->setStatus( ::api::Thread::RUNNING );
                    // Switch to the task
                    int32 priority = thread->getPriority();
                    int_.setContext( *thread->getRegister() );                    
                    if(priority == ::api::Thread::LOCK_PRIORITY)
                    {
                        tim_.stop();        
                    }
                    else
                    {
                        tim_.start();
                    }
                    tim_.setCount(0);
                    tim_.setPeriod(priority * QUANT);
                    return;
                }
                
                default:
                    break;
            }
            list_.remove();
            list_.add(thread);
        }    
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
    ::api::Thread* Scheduler::createThread(::api::Task& task)
    {
        if( not isConstructed_ ) return NULL;
        SchedulerThread* thread = new SchedulerThread(task, ++idCount_, &mainThread, this);
        if(thread == NULL) return NULL; 
        if(thread->isConstructed()) return thread;  
        delete thread;
        return NULL;
    }
    
    /**
     * Returns currently executing thread.
     *
     * @return executing thread.
     */
    ::api::Thread& Scheduler::getCurrentThread()
    {
        ::api::Runtime& runtime = Kernel::call().getRuntime();
        if( not isConstructed_ ) runtime.terminate(-1);
        bool is = Int::disableAll();
        ::api::Thread* thread = list_.peek();
        Int::enableAll(is);
        if(thread == NULL) runtime.terminate(-1);
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
     * Adds a thread to execution list
     *
     * @return true if thread has been added successfully.
     */
    bool Scheduler::addThread(SchedulerThread* thread)
    {
        if( not isConstructed_ ) return false;
        bool is = Int::disableAll();
        bool res = list_.add(thread);
        Int::enableAll(is);    
        return res;
    }    
    
    /**
     * Removes the first occurrence of the specified thread.
     *
     * @param thread removing thread.
     */
    void Scheduler::removeThread(SchedulerThread* thread)
    {
        if( not isConstructed_ ) return;
        bool is = Int::disableAll();
        list_.removeElement(thread);
        Int::enableAll(is);
    }
    
    /**
     * Runs a method of Runnable interface start vector.
     */  
    void Scheduler::run()
    {
        SchedulerThread* current = list_.peek();
        // Start main method of user thread task
        current->getTask()->main();
        Int::disableAll();
        current->setStatus( ::api::Thread::DEAD );
        // Remove this executed task
        list_.remove();
        yield();
    }        
    
    /**
     * Runs a method of Runnable interface start vector.
     */  
    void Scheduler::mainThread(Scheduler* scheduler)
    {
        // Invoke the member function through the pointer
        void(Scheduler::*run)() = &Scheduler::run;
        (scheduler->*run)();
        // This PC is not allowable
        while(true);
    }

}
    
