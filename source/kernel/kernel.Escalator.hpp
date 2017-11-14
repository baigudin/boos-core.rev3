/**
 * Escalator class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_ESCALATOR_HPP_
#define KERNEL_ESCALATOR_HPP_

#include "Object.hpp"
#include "api.Semaphore.hpp"
#include "api.Thread.hpp"
#include "kernel.Kernel.hpp"
#include "library.LinkedList.hpp"

namespace kernel
{
    class Escalator : public ::Object<>, public ::api::Semaphore
    {
        typedef ::Object<> Parent;
     
    public:
  
        /** 
         * Constructor.
         *
         * @param permits the initial number of permits available.   
         */      
        Escalator(int32 permits) : Parent(),
            isConstructed_ (getConstruct()),        
            scheduler_     (NULL),
            thread_        (NULL),                    
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
        Escalator(int32 permits, bool fair) : Parent(),
            isConstructed_ (getConstruct()),        
            scheduler_     (NULL),
            thread_        (NULL),           
            permits_ (permits),
            isFair_  (fair),
            list_    (){
            setConstruct( construct() );  
        }
                                
        /** 
         * Destructor.
         */
        virtual ~Escalator()
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
         * Acquires one permit from this escalator.
         *
         * @return true if the escalator is acquired successfully.
         */  
        virtual bool acquire()
        {
            return acquire(1);
        }
        
        /**
         * Acquires the given number of permits from this escalator.
         *
         * @param permits the number of permits to acquire.
         * @return true if the escalator is acquired successfully.
         */  
        virtual bool acquire(int32 permits)
        {
            bool res, is;  
            if(!isConstructed()) return false;
            is = thread_->disable();
            ::api::Thread& thread = scheduler_->getCurrentThread();
            Node node(thread, permits);
            // Check about available space in the semaphoring critical section
            if( permits_ - permits >= 0 && list_.lock.isEmpty() )
            {
                // Add current thread to the executing queue
                res = isFair_ ? list_.exec.add(node) : true;
                // Decrement the number of available permits
                if(res == true) permits_ -= permits;
                // Go through the escalator to critical section
                return thread_->enable(is, res);      
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
            return thread_->enable(is, res);      
        }
        
        /**
         * Releases one permit.
         */
        virtual void release()
        {
            release(1);
        }    
        
        /**
         * Releases the given number of permits.
         *
         * @param permits the number of permits to release.
         */  
        virtual void release(int32 permits)
        {
            bool res, is;
            if(!isConstructed()) return;
            is = thread_->disable();
            Node node(scheduler_->getCurrentThread(), permits);
            // Remove current thread from executing list    
            res = isFair_ ? removeNode(list_.exec, node) : true;
            // Increment the number of available permits    
            if(res == true) permits_ += permits;
            // Signal the escalator has released permits
            thread_->enable(is);
        }
        
        /**
         * Tests if this escalator is fair.
         *
         * @return true if this escalator has fairness set true.
         */  
        virtual bool isFair() const
        {
            return isFair_;
        }
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked()
        {
            if(!isConstructed()) return false;
            bool is = thread_->disable();
            Node cur(scheduler_->getCurrentThread(), 0);
            Node res = list_.lock.peek();
            // Test if current thread is the first in FIFO
            if(cur != res) return thread_->enable(is, true);
            // Check about free permits of escalator
            if(permits_ - res.permits < 0) return thread_->enable(is, true);
            // Unblock thread
            permits_ -= res.permits;
            if(isFair_ == true) list_.exec.add( Node(scheduler_->getCurrentThread(), res.permits) );
            return thread_->enable(is, false);    
        }        
  
    private:
    
        /** 
         * Node for escalator lists.
         */  
        class Node
        {
        
        public:
        
            /** 
             * Constructor.
             *
             * @param ipermits number of permits to release.
             * @param thread   current executing thread.
             * @return true if the escalator is release successfully.
             */
            Node(::api::Thread& thread, int32 ipermits) :
                permits (ipermits),
                thread_ (&thread){
            }
          
            /** 
             * Copy constructor.
             *
             * @param obj reference to source node.       
             */    
            Node(const Node& obj) :
                permits (obj.permits),
                thread_ (obj.thread_){
            }
            
            /** 
             * Constructor.
             *
             * Constructs this object as illegal.
             *
             * @param ipermits number of permits to release.
             * @return true if the escalator is release successfully.
             */
            Node(int32 ipermits) :
                permits (ipermits),
                thread_ (NULL){
            }      
          
            /**
             * Destructor.
             */
           ~Node(){}
          
            /** 
             * Assignment operator.
             *
             * @param node reference to source node.
             * @return reference to this object.
             */  
            Node& operator =(const Node& node)
            {
                thread_ = node.thread_;
                permits = node.permits;
                return *this;
            }
            
            /**
             * Equality operator.
             *
             * @param obj1 reference first object.
             * @param obj2 reference second object.
             * @return true if object are equal.
             */
            friend bool operator ==(const Node& obj1, const Node& obj2);
            
            /**
             * Inequality operator.
             *
             * @param obj1 reference first object.
             * @param obj2 reference second object.
             * @return true if object are not equal.
             */      
            friend bool operator !=(const Node& obj1, const Node& obj2);
          
            /** 
             * Number of permits to release for this thread.
             */
            int32 permits;
          
        private:
        
            /** 
             * Executing thread.
             */
            ::api::Thread* thread_;
        
        };
        
        /** 
         * Contain lists for the escalator.
         */  
        class List
        {
        
        public:
        
            /** 
             * Constructor.
             */
            List() : 
                illegal_ (-1),
                exec     (illegal_), 
                lock     (illegal_){
            }
          
            /**
             * Destructor.
             */
           ~List(){}
            
            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */    
            bool isConstructed() const
            {
                if(!exec.isConstructed()) return false;
                if(!lock.isConstructed()) return false;        
                return true;
            }
        
        private:
        
            /**
             * Illegal value for all this lists.
             */
            Node illegal_;
        
        public:
          
            /**
             * List of executing threads for fair escalator.
             *
             * ::api::Queue interface of the list is only used by the escalator.
             */      
            library::LinkedList<Node> exec;
            
            /**
             * List of locked threads.
             *
             * ::api::Queue interface of the list is only used by the escalator.
             */      
            library::LinkedList<Node> lock;
         
        };
        
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            if(!isConstructed()) return false;      
            if(!list_.isConstructed()) return false;      
            scheduler_ = &Kernel::call().getScheduler();
            thread_ = &scheduler_->toggle();            
            return true;
        }        
        
        /**
         * Removes last element from list.
         *
         * @param list reference to a queue.
         * @param node reference to node.     
         */    
        bool removeNode(::api::Queue<Node>& list, Node& node)
        {
            while(true)
            {
                // Remove the head thread if it given thread of the node
                if(list.peek() == node) return list.remove();
                 scheduler_->yield();
            }      
        }         
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Escalator(const Escalator& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.
         */
        Escalator& operator =(const Escalator& obj);     
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;

        /**
         * The kernel threads scheduler.
         */        
        ::api::Scheduler* scheduler_;
        
        /**
         * The kernel threads switching toggle.
         */        
        ::api::Toggle* thread_;        
        
        /**
         * Number of permits for acquiring this escalator.
         */
        int32 permits_;
        
        /**
         * Escalator fair flag.
         */    
        bool isFair_;
        
        /** 
         * Lists of this escalator.
         */     
        List list_;
        
        friend bool operator ==(const Node& node1, const Node& node2);
        friend bool operator !=(const Node& node1, const Node& node2);    
    };
    
    /**
     * Equality operator.
     *
     * @param obj1 reference first object.
     * @param obj2 reference second object.
     * @return true if object are equal.
     */
    inline bool operator ==(const Escalator::Node& obj1, const Escalator::Node& obj2)
    {
        return obj1.thread_ == obj2.thread_ ? true : false;
    }
    
    /**
     * Inequality operator.
     *
     * @param obj1 reference first object.
     * @param obj2 reference second object.
     * @return true if object are not equal.
     */      
    inline bool operator !=(const Escalator::Node& obj1, const Escalator::Node& obj2)
    {
        return obj1.thread_ != obj2.thread_ ? true : false;
    }
    
}
#endif // KERNEL_ESCALATOR_HPP_
