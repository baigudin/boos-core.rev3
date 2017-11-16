/** 
 * The operating system kernel main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Main.hpp" 
#include "kernel.Allocator.hpp"
#include "module.Processor.hpp"
#include "kernel.Resource.hpp"
#include "module.Interrupt.hpp" 
#include "system.Main.hpp"
#include "Configuration.hpp"

namespace kernel
{
    /**
     * The method which will be stated first.
     * 
     * @return error code or zero.
     */   
    int32 Main::main()
    {
        int32 stage = 0;
        int32 error = -1;
        kernel_ = NULL;        
        const ::Configuration config;
        do
        {
            // Stage 1: initialize the kernel heap allocator
            stage++;
            if( not ::kernel::Allocator::initialize(config) ) break;                   
            // Stage 2: initialize necessary modules of a processor
            stage++;
            if( not ::module::Processor::initialize(config) ) break;    
            // Stage 3: create the kernel resource factory
            stage++;
            Resource kernel(config);
            kernel_ = &kernel;
            if(kernel_ == NULL || not kernel_->isConstructed()) break;       
            // Stage complete: call the operating system main method
            stage = -1;
            error = ::system::Main::main( kernel );
        }
        while(false);
        switch(stage)
        {
            default:
            case 3:
                kernel_ = NULL;
                
            case 2: 
                ::module::Processor::deinitialize();
                
            case 1: 
                ::kernel::Allocator::deinitialize();      
                
            case 0: 
                break;
        }
        return error;
    }
    
    /**
     * Returns the kernel factory resource.
     *        
     * @return the kernel interface.
     */
    ::api::Kernel& Main::getKernel()
    {
        if(kernel_ == NULL) ::module::Interrupt::disableAll();
        return *kernel_;
    }            
    
    /**
     * The kernel factory resource (no boot).
     */
    ::api::Kernel* Main::kernel_;

    /**
     * Pointer to constructed heap memory (no boot).
     */
    ::api::Heap* Allocator::heap_;

}

/**
 * The main function.
 * 
 * The method should be called after default boot initialization, and
 * the following tasks must be:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 * 
 * @return error code or zero.
 */   
#ifdef EOOS_VENDOR_BOOT
int main()
{
    return static_cast<int>( ::kernel::Main::main() );
}
#endif // EOOS_VENDOR_BOOT

