/**
 * Thread tasks scheduler.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef KERNEL_SCHEDULER_HPP_
#define KERNEL_SCHEDULER_HPP_

#include "kernel.TimerInterrupt.hpp"
#include "api.Scheduler.hpp"
#include "api.Task.hpp"
#include "utility.LinkedList.hpp"

namespace kernel
{
    class SchedulerThread;
    
    class Scheduler : public ::kernel::TimerInterrupt, public ::api::Scheduler, public ::api::Task
    {
        typedef ::kernel::TimerInterrupt Parent;
        typedef ::kernel::Interrupt      ResInt;    
        typedef ::kernel::Timer          ResTim;        
  
    public:
  
        /** 
         * Constructor.
         */
        Scheduler();
      
        /** 
         * Destructor.
         */
        virtual ~Scheduler();
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const;
      
        /** 
         * Hardware interrupt handler.
         */      
        virtual void main();
        
        /**
         * Returns size of stack.
         *
         * @return stack size in bytes.
         */  
        virtual int32 getStackSize() const;
      
        /**
         * Creates a new thread.
         *
         * @param task an user task which main method will be invoked when created thread is started.
         * @return a new thread.
         */
        virtual ::api::Thread& createThread(::api::Task& task);
        
        /**
         * Removes the first occurrence of the specified thread.
         *
         * @param thread removing thread.
         */
        virtual void removeThread(::api::Thread& thread);
        
        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        virtual ::api::Thread& getCurrentThread();
        
        /**
         * Yields to next thread.
         */
        virtual void yield();
        
        /** 
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */ 
        virtual ::api::Toggle& toggle();
  
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
        bool construct();

        
        /**
         * Runs a method of Runnable interface start vector.
         */  
        void run();
        
        /**
         * Runs a method of Runnable interface start vector.
         */  
        static void runTask(Scheduler* scheduler);
        
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
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
        
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
        ::utility::LinkedList< SchedulerThread* > list_;
  
    };
}
#endif // KERNEL_SCHEDULER_HPP_
