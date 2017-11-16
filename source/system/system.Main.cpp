/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Main.hpp" 
#include "system.TaskMain.hpp"
#include "system.Thread.hpp"
#include "system.Resource.hpp"
#include "Allocator.hpp" 

namespace system
{
    /**
     * The method which will be stated first.
     * 
     * @param config the operating system configuration.         
     * @param kernel a kernel resources factory.
     * @return error code or zero.
     */
    int32 Main::main(::api::Kernel& kernel)
    {
        int32 stage = 0;
        int32 error = -1;
        system_ = NULL;
        global_ = NULL;
        kernel_ = &kernel;
        do
        {
            // Stage 1: Create the system resource factory
            stage++;
            system_ = new Resource(kernel);
            if(system_ == NULL || not system_->isConstructed()) break; 
            // Stage 2: Set heap interrupt controller
            stage++;        
            ::api::Heap* heap = NULL;
            if(heap == NULL || not heap->isConstructed()) break;
            global_ = &kernel.getGlobalInterrupt();
            heap->setToggle(global_);
            // Stage complete
            stage = -1;
            int32 stack = kernel.getStackSize();
            TaskMain task(stack);
            Thread thread(task);
            if( not thread.isConstructed() ) break; 
            thread.start();
            thread.yield();
            thread.join();
            error = task.error();
        }
        while(false);
        switch(stage)
        {
            default:
            case 2: 
                global_ = NULL;
                            
            case 1: 
                delete system_;
                
            case 0: 
                break;
        }
        return error;
    }
    
    /**
     * Returns the operating system factory resource.
     *        
     * @return the operating system interface.
     */
    ::api::System& Main::getSystem()
    {
        if(system_ == NULL) kernel_->getGlobalInterrupt().disable();
        return *system_;
    }
    
    /**
     * The operating system factory resource (no boot).
     */
    ::api::System* Main::system_;
    
    /**
     * The operating system global interrupt resource (no boot).
     */
    ::api::Toggle* Main::global_;
    
    /**
     * The operating system kernel factory resource (no boot).
     */
    ::api::Kernel* Main::kernel_;

}

