/** 
 * Escalator class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Escalator.hpp"
#include "system.Thread.hpp"
#include "module.Interrupt.hpp"

namespace kernel
{
    typedef ::module::Interrupt Int;

    /** 
     * Constructor.
     *
     * In this case the escalator will be constructed as unfair.
     *
     * @param permits the initial number of permits available.
     */      
    Escalator::Escalator(int32 permits) : Parent(),
        permits_ (permits),
        isFair_  (false),
        list_    (){
        setConstruct( construct() );  
    }    
    
    /** 
     * Constructor.
     *
     * @param permits the initial number of permits available.      
     * @param fair true if this escalator will guarantee FIFO granting of permits under contention.
     */      
    Escalator::Escalator(int32 permits, bool fair) : Parent(),
        permits_ (permits),
        isFair_  (fair),
        list_    (){
        setConstruct( construct() );  
    }
  
    /** 
     * Destructor.
     */
    Escalator::~Escalator()
    {
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Escalator::isConstructed() const
    {
        return this->Parent::isConstructed();
    }
  
    /**
     * Acquires one permit from this escalator.
     *
     * @return true if the escalator is acquired successfully.
     */
    bool Escalator::acquire()
    {
        return acquire(1);
    }    
  
    /**
     * Acquires the given number of permits from this escalator.
     *
     * @param permits the number of permits to acquire.
     * @return true if the escalator is acquired successfully.
     */   
    bool Escalator::acquire(int32 permits)
    {
        bool res, is;  
        if(!isConstructed()) return false;
        is = Int::disableAll();
        ::api::Thread& thread = ::system::Thread::getCurrent();
        Node node(thread, permits);
        // Check about available space in the semaphoring critical section
        if( permits_ - permits >= 0 && list_.lock.isEmpty() )
        {
            // Add current thread to the executing queue
            res = isFair_ ? list_.exec.add(node) : true;
            // Decrement the number of available permits
            if(res == true) permits_ -= permits;
            // Go through the escalator to critical section
            return Int::enableAll(is, res);      
        }
        // Add current thread to the locking queue
        res = list_.lock.add(node);
        if(res == true)
        {
            // Block current thread on the escalator and switch to another thread
            thread.block(*this);
            // This thread is unblocked by the scheduler called isBlocked method 
            res = removeNode(list_.lock, node);
        }
        // Go through the escalator to critical section
        return Int::enableAll(is, res);      
    }    
  
    /**
     * Releases one permit.
     *
     * @return true if the escalator is released successfully.
     */
    void Escalator::release()
    {
        release(1);
    }    
  
    /**
     * Releases the given number of permits.
     *
     * @param permits the number of permits to release.
     * @return true if the escalator is released successfully.
     */  
    void Escalator::release(int32 permits)
    {
        bool res, is;
        if(!isConstructed()) return;
        is = Int::disableAll();
        Node node(::system::Thread::getCurrent(), permits);
        // Remove current thread from executing list    
        res = isFair_ ? removeNode(list_.exec, node) : true;
        // Increment the number of available permits    
        if(res == true) permits_ += permits;
        // Signal the escalator has released permits
        Int::enableAll(is);
    }  
    
    /** 
     * Tests if this resource is blocked.
     *
     * @return true if this resource is blocked.
     */ 
    bool Escalator::isBlocked()
    {
        if(!isConstructed()) return false;
        bool is = Int::disableAll();
        Node cur(::system::Thread::getCurrent(), 0);
        Node res = list_.lock.peek();
        // Test if current thread is the first in FIFO
        if(cur != res) return Int::enableAll(is, true);
        // Check about free permits of escalator
        if(permits_ - res.permits < 0) return Int::enableAll(is, true);
        // Unblock thread
        permits_ -= res.permits;
        if(isFair_ == true) list_.exec.add( Node(::system::Thread::getCurrent(), res.permits) );
        return Int::enableAll(is, false);    
    }
    
    /**
     * Tests if this escalator is fair.
     *
     * @return true if this escalator has fairness set true.
     */  
    bool Escalator::isFair() const
    {
        return isFair_;
    }
    
    /**
     * Removes last element from list.
     *
     * @param list reference to SemaphoreList class.
     * @param node reference to node.     
     */  
    bool Escalator::removeNode(::api::Queue<Node>& list, Node& node)
    {
        while(true)
        {
            // Remove the head thread if it given thread of the node
            if(list.peek() == node) return list.remove();
            ::system::Thread::yield();
        }      
    }      
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.   
     */
    bool Escalator::construct()
    {
        if(!isConstructed()) return false;      
        if(!list_.isConstructed()) return false;      
        return true;
    }
}
