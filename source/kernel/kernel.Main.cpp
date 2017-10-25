/** 
 * The operating system kernel main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Main.hpp" 
#include "kernel.System.hpp"
#include "kernel.Interrupt.hpp"
#include "kernel.Thread.hpp"
#include "driver.Processor.hpp"
#include "Allocator.hpp"
#include "Board.hpp"
#include "system.Main.hpp" 

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
        const ::Configuration config = ::Configuration();
        do
        {
            // Stage 1
            stage++;
            if( not ::Allocator::initialize(config) ) break;        
            // Stage 2
            stage++;
            if( not ::driver::Processor::initialize(config) ) break;    
            // Stage 3
            stage++;
            if( not ::Board::initialize(config) ) break;
            // Stage 4
            stage++;
            if( not ::kernel::Interrupt::initialize() ) break;      
            // Stage 5
            stage++;
            if( not ::kernel::System::initialize() ) break;      
            // Stage complete
            stage = -1;
            error = ::system::Main::main();
        }
        while(false);
        switch(stage)
        {
            default:
            case  5: ::kernel::System::deinitialize();
            case  4: ::kernel::Interrupt::deinitialize();
            case  3: ::Board::deinitialize();      
            case  2: ::driver::Processor::deinitialize();
            case  1: ::Allocator::deinitialize();      
            case  0: break;
        }
        return error;
    }
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
    return ::kernel::Main::main() & 0x0000ffff;
}
#endif // EOOS_VENDOR_BOOT

/**
 * Pointer to constructed heap memory (no boot).
 */
::api::Heap* ::Allocator::heap_;
