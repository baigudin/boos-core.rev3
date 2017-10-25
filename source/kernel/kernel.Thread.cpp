/**
 * Thread class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Thread.hpp"

namespace kernel
{
    /** 
     * Constructor.
     *
     * @param task an task interface whose main method is invoked when this thread is started.
     */
    Thread::Thread(::api::Task& task) : Parent(),
        isConstructed_ (getConstruct()){    
        setConstruct( construct() );  
    }
    
    /** 
     * Destructor.
     */
    Thread::~Thread()
    {
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
     * Causes this thread to begin execution.
     */
    void Thread::start()
    {
    }
    
    /**
     * Waits for this thread to die.
     */  
    void Thread::join()
    {
    }
    
    /**
     * Causes this thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    void Thread::sleep(int64 millis, int32 nanos)
    {
    }
    
    /**
     * Blocks this thread on given resource and yields the task.
     *
     * @param res reference to resource.
     */  
    void Thread::block(::api::Resource& res)
    {
    }        
    
    /**
     * Returns the identifier of this thread.
     *
     * @return the thread identifier.
     */
    int64 Thread::getId() const
    {
    }

    /**
     * Causes the currently executing thread to sleep.
     *
     * @param millis a time to sleep in milliseconds.
     * @param nanos  an additional nanoseconds to sleep.
     */  
    ::api::Thread::Status Thread::getStatus() const
    {
    }        
    
    /**
     * Returns this thread priority.
     *
     * @return priority value.
     */  
    int32 Thread::getPriority() const
    {
    }
    
    /**
     * Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY].
     */  
    void Thread::setPriority(int32 priority)
    {
    }
    
    /**
     * Returns currently executing thread.
     *
     * @return executing thread.
     */
    ::api::Thread& Thread::getCurrent()
    {
    }
    
    /**
     * Yields to next thread.
     */
    void Thread::yield()
    {
    }
    
    /** 
     * Returns the toggle interface for controlling global thread switching.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Thread::toggle()
    {
    }
    
    /**
     * Constructor.
     */
    bool Thread::construct()
    {
    }
    

}
