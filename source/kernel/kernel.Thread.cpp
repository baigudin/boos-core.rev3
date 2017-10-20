/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Thread.hpp"
#include "kernel.Scheduler.hpp"
#include "kernel.System.hpp"
#include "driver.Processor.hpp"
#include "driver.Register.hpp"
#include "utility.Stack.hpp"

namespace kernel
{
    typedef ::utility::Stack<int64>  Stack;
    
    /** 
     * Constructor.
     *
     * @param task an task interface whose main method is invoked when this thread is started.
     */
    Thread::Thread(::api::Task& task) : Parent(),
        task_     (NULL),
        block_    (NULL),
        register_ (NULL),
        stack_    (NULL),
        id_       (++idCount_),
        priority_ (0),
        sleep_    (0),
        status_   (NEW){
        setConstruct( construct(&task) );  
    }
    
    /** 
     * Destructor.
     */
    Thread::~Thread()
    {
        if( not isConstructed() ) return;
        scheduler_->remove(*this);
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
    bool Thread::isConstructed() const
    {
        return this->Parent::isConstructed();
    }
    
    /**
     * Causes this thread to begin execution.
     */
    void Thread::start()
    {
        if( not isConstructed() ) return;
        scheduler_->start(*this);
    }
    
    /**
     * Waits for this thread to die.
     */  
    void Thread::join()
    {
        if( not isConstructed() ) return;
        scheduler_->join(*this);
    }
    
    /**
     * Causes the currently executing thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    void Thread::sleep(int64 millis, int32 nanos)
    {
        if( not isInitialized() ) return;
        scheduler_->sleep(millis, nanos);
    }
    
    /**
     * Blocks current thread on given resource and yields the task.
     *
     * @param res pointer to resource.
     */  
    void Thread::block(::api::Resource& res)
    {
        if( not isInitialized() ) return;
        scheduler_->block(res);
    }
  
    /**
     * Returns a pointer to the currently executing thread.
     *
     * @return the executable thread.
     */
    Thread& Thread::getCurrent()
    {
        if( not isInitialized() ) System::terminate();
        Thread* thread = scheduler_->currentTask();
        if(thread == NULL) System::terminate();
        return *thread;
    }
  
    /**
     * Yields to next thread.
     */
    void Thread::yield()
    {
        if( not isInitialized() ) return;
        scheduler_->jump();
    }
    
    /**
     * Returns this thread priority.
     *
     * @return priority value.
     */  
    int32 Thread::getPriority() const
    {
        return priority_;
    }  
    
    /**
     * Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
     */  
    void Thread::setPriority(int32 priority)
    {
        if( not isConstructed() ) return;
        if(priority > MAX_PRIORITY) priority = MAX_PRIORITY;
        else if(priority < MIN_PRIORITY) priority = MIN_PRIORITY;
        else priority_ = priority;
    }
    
    /**
     * Returns the identifier of this thread.
     *
     * @return the thread identifier.
     */
    int64 Thread::getId()
    {
        return id_;
    }
    
    /** 
     * Returns the toggle interface for controlling global thread switch.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Thread::toggle()
    {
        if( not isInitialized() ) System::terminate();
        return *scheduler_;
    }
  
    /**
     * Initiates an execution of threads.
     */  
    void Thread::execute()
    {
        if( not isInitialized() ) return;
        scheduler_->execute();
    }
    
    /**
     * Constructor.
     *
     * @param task an interface whose run method is invoked when this thread is started.   
     */
    bool Thread::construct(::api::Task* task)
    {
        if( not isInitialized() ) return false;    
        if( not isConstructed() ) return false;  
        if( idCount_ < 0 ) return false;
        if( not task->isConstructed() ) return false;    
        const Thread* thread = scheduler_->currentTask();
        priority_ = thread != NULL ? thread->getPriority() : NORM_PRIORITY;
        // Set this thread CPU registers context 
        register_ = ::driver::Register::create();
        if(register_ == NULL || !register_->isConstructed()) return false;
        // Set this thread stack context 
        stack_ = new Stack( ::driver::Processor::getStackType(), task->getStackSize() >> 3 );    
        if(stack_ == NULL || !stack_->isConstructed()) return false;
        task_ = task;
        return true;
    }
    
    /**
     * Initializes the resource.
     *
     * @return true if no errors have been occurred.
     */   
    bool Thread::initialize()
    {
        isInitialized_ = 0;
        stage_ = 0; 
        scheduler_ = NULL;
        idCount_ = 0;               
        // Stage 1: Create the operating system scheduler
        stage_++;
        scheduler_ = new Scheduler();
        if(scheduler_ == NULL || !scheduler_->isConstructed()) return false;
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;        
        return true;    
    }
    
    /**
     * Deinitializes the resource.
     */
    void Thread::deinitialize()
    {
        switch(stage_)
        {
            default:    
            case  1: 
            {
                delete scheduler_;
                scheduler_ = NULL;
            }          
            case  0: 
            {
                break;
            }
        }
        isInitialized_ = 0; 
    }
    
    /**
     * Tests if the module has been initialized.
     *
     * @return true if the module has been initialized successfully.
     */    
    bool Thread::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }    
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 Thread::isInitialized_;    
    
    /**
     * The module initialization stage (no boot).
     */
    int32 Thread::stage_;         
    
    /**
     * Thread scheduler (no boot).
     */
    Scheduler* Thread::scheduler_;
    
    /**
     * Counter of thread identifiers (no boot).
     */    
    int64 Thread::idCount_;  
}
