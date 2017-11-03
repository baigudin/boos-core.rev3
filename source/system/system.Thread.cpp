/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Thread.hpp"
#include "system.System.hpp"

namespace system
{
    /** 
     * Constructor.
     */
    Thread::Thread() : Parent(),
        isConstructed_ ( getConstruct() ),
        thread_        ( NULL ){
        setConstruct( construct(*this) );
    }

    /** 
     * Constructor.
     *
     * @param task an task interface whose main method is invoked when this thread is started.
     */
    Thread::Thread(::api::Task& task) : Parent(),
        isConstructed_ ( getConstruct() ),
        thread_        ( NULL ){
        setConstruct( construct(task) );
    }
    
    /** 
     * Destructor.
     */
    Thread::~Thread()
    {
        delete thread_;
    }

    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */   
    bool Thread::isConstructed() const
    {
        return isConstructed_;
    } 
    
    /**
     * The method with self context which will be executed by default.
     */  
    void Thread::main()
    {
    }        
    
    /**
     * Causes this thread to begin execution.
     */
    void Thread::start()
    {
        if( not isConstructed_ ) return; 
        return thread_->start();    
    }
    
    /**
     * Waits for this thread to die.
     */  
    void Thread::join()
    {
        if( not isConstructed_ ) return; 
        return thread_->join();
    }
    
    /**
     * Causes this thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    void Thread::sleep(int64 millis, int32 nanos)
    {
        if( not isConstructed_ ) return; 
        return thread_->sleep(millis, nanos);    
    }
    
    /**
     * Blocks this thread on given resource and yields the task.
     *
     * @param res reference to resource.
     */  
    void Thread::block(::api::Resource& res)
    {
        if( not isConstructed_ ) return; 
        return thread_->block(res);    
    }        
    
    /**
     * Returns the identifier of this thread.
     *
     * @return the thread identifier.
     */
    int64 Thread::getId() const
    {
        if( not isConstructed_ ) return -1; 
        return thread_->getId();
    }

    /**
         * Returns a status of this thread.
         *
         * @return this thread status.
     */  
    ::api::Thread::Status Thread::getStatus() const
    {
        if( not isConstructed_ ) return DEAD; 
        return thread_->getStatus();    
    }        
    
    /**
     * Returns this thread priority.
     *
     * @return priority value.
     */  
    int32 Thread::getPriority() const
    {
        if( not isConstructed_ ) return -1; 
        return thread_->getPriority();    
    }
    
    /**
     * Sets this thread priority.
     *
         * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
     */  
    void Thread::setPriority(int32 priority)
    {
        if( not isConstructed_ ) return; 
        return thread_->setPriority(priority);
    }
    
    /**
     * Returns currently executing thread.
     *
     * @return executing thread.
     */
    ::api::Thread& Thread::getCurrent()
    {
        if( not isInitialized() ) System::terminate();
        return scheduler_->getCurrentThread();
    }
    
    /**
     * Causes current thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    void Thread::sleepCurrent(int64 millis, int32 nanos)
    {
        getCurrent().sleep(millis, nanos);
    }   
    
    /**
     * Yields to next thread.
     */
    void Thread::yield()
    {
        if( not isInitialized() ) System::terminate();
        return scheduler_->yield();     
    }
    
    /** 
     * Returns the toggle interface for controlling global thread switching.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Thread::toggle()
    {
        if( not isInitialized() ) System::terminate();
        return scheduler_->toggle();    
    }
    
    /**
     * Constructor.
     *
     * @param task an task interface whose main method is invoked when this thread is started.     
     * @return true if object has been constructed successfully.   
     */
    bool Thread::construct(::api::Task& task)
    {
        if( not isInitialized() ) return false; 
        if( not isConstructed_ ) return false; 
        thread_ = scheduler_->createThread(task);
        if( thread_ == NULL || not thread_->isConstructed() ) return false; 
        return true;
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Thread::initialize()
    {
        isInitialized_ = 0;
        stage_ = 0;
        // Stage 1: Create global interrupt class switching
        stage_++;
        ::api::Scheduler& scheduler = System::getKernel().getScheduler();
        if( not scheduler.isConstructed() ) return false;
        scheduler_ = &scheduler;
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;
        return true;
    }
  
    /**
     * Deinitialization.
     */
    void Thread::deinitialize()
    {
        switch(stage_)
        {
            default:
            case  1: 
            {

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
     * A kernel scheduler (no boot).
     */          
    ::api::Scheduler* Thread::scheduler_;    

}
