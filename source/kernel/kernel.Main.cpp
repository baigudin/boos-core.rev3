/** 
 * The operating system kernel main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Main.hpp" 
#include "kernel.Resource.hpp"
#include "module.Processor.hpp"
#include "module.Interrupt.hpp" 
#include "system.Main.hpp"
#include "Configuration.hpp"
#include "Allocator.hpp"
#include "Board.hpp"

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
        const ::Configuration config = ::Configuration();
        do
        {
            // Stage 1
            stage++;
            if( not ::Allocator::initialize(config) ) break;                   
            // Stage 2
            stage++;
            if( not ::module::Processor::initialize(config) ) break;    
            // Stage 3: Create the kernel resource factory
            stage++;
            kernel_ = new Resource(config);
            if(kernel_ == NULL || not kernel_->isConstructed()) break;       
            // Stage complete
            stage = -1;
            error = ::system::Main::main( *kernel_ );
        }
        while(false);
        switch(stage)
        {
            default:
            case 3: 
                delete kernel_;
                
            case 2: 
                ::module::Processor::deinitialize();
                
            case 1: 
                ::Allocator::deinitialize();      
                
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

