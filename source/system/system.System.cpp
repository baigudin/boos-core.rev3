/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"
#include "system.SystemTimerInterrupt.hpp"
#include "driver.Interrupt.hpp"
#include "api.Toggle.hpp"

namespace system
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
        return interrupt_ != NULL ? interrupt_->nanoTime() : 0;
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
        // Create the operating system system tick timer
        interrupt_ = new SystemTimerInterrupt();
        if(interrupt_ == NULL || !interrupt_->isConstructed()) return false;
        // Set heap interrupt controller
        global_ = NULL;
        ::api::Heap* heap = ::Allocator::getHeap();
        if(heap == NULL || !heap->isConstructed()) return false;
        global_ = &interrupt_->global();
        heap->setToggle(global_);
        return true;
    }
    
    /**
     * Deinitialization.
     */
    void System::deinitialize()
    {
        global_ = NULL;
        if(interrupt_ != NULL)
        {
            delete interrupt_;
            interrupt_ = NULL;
        }
    }
    
    /**
     * Hardware timer interrupt resource (no boot).
     */
    SystemTimerInterrupt* System::interrupt_;  
  
    /**
     * Global interrupt resource (no boot).
     */
    ::api::Toggle* System::global_;  
}
