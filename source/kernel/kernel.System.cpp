/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.System.hpp"
#include "kernel.Scheduler.hpp"
#include "kernel.SystemTimerInterrupt.hpp"
#include "driver.Interrupt.hpp"
#include "api.Toggle.hpp"

namespace kernel
{
    /**
     * Current value of the running system in milliseconds.
     *
     * @return time in milliseconds.
     */  
    int64 System::getTimeMs()
    {
        return getTimeNs() / 1000000;
    }
  
    /**
     * Current value of the running system in nanoseconds.
     *
     * @return time in nanoseconds.
     */  
    int64 System::getTimeNs()
    {
        return isInitialized() ? interrupt_->nanoTime() : 0;
    }
    
    /** 
     * Returns a kernel scheduler.
     *
     * @return a kernel scheduler.
     */      
    ::api::Scheduler& System::getScheduler()
    {
        if( not isInitialized() ) terminate();
        return *scheduler_;
    }
    
    /**
     * Terminates the operating system execution.
     */
    void System::terminate()
    {
        ::driver::Interrupt::disableAll();
        while(true);  
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool System::initialize()
    {
        isInitialized_ = 0;
        stage_ = 0;
        scheduler_ = NULL;
        interrupt_ = NULL;
        global_ = NULL;        
        // Stage 1: Create the operating system tick timer
        stage_++;        
        scheduler_ = new Scheduler();
        if(scheduler_ == NULL || not scheduler_->isConstructed()) return false;        
        // Stage 2: Create the operating system tick timer
        stage_++;        
        interrupt_ = new SystemTimerInterrupt();
        if(interrupt_ == NULL || not interrupt_->isConstructed()) return false;
        // Stage 3: Set heap interrupt controller
        stage_++;        
        ::api::Heap* heap = ::Allocator::getHeap();
        if(heap == NULL || not heap->isConstructed()) return false;
        global_ = &interrupt_->global();
        heap->setToggle(global_);
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;        
        return true;
    }
    
    /**
     * Deinitialization.
     */
    void System::deinitialize()
    {
        switch(stage_)
        {
            default:
            case 3:             
            {
                global_ = NULL;            
            }
            case 2: 
            {
                delete interrupt_;
                interrupt_ = NULL;                
            }          
            case 1: 
            {
                delete scheduler_;
                scheduler_ = NULL;                
            }          
            case 0: 
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
    bool System::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }    
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 System::isInitialized_;    
    
    /**
     * The module initialization stage (no boot).
     */
    int32 System::stage_;    
    
    /**
     * Scheduler interrupt resource (no boot).
     */
    ::api::Scheduler* System::scheduler_;
    
    /**
     * Hardware timer interrupt resource (no boot).
     */
    SystemTimerInterrupt* System::interrupt_;  
  
    /**
     * Global interrupt resource (no boot).
     */
    ::api::Toggle* System::global_;  
}
