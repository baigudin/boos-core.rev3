/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.Main.hpp" 
#include "system.System.hpp"
#include "system.Interrupt.hpp"
#include "system.Thread.hpp"
#include "driver.Processor.hpp"
#include "Allocator.hpp"
#include "Board.hpp"

namespace system
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
    do{
      // Stage 1 
      stage++;
      if( not ::Allocator::init(config) ) break;        
      // Stage 2 
      stage++;
      if( not ::driver::Processor::init(config) ) break;    
      // Stage 3
      stage++;
      if( not ::Board::init(config) ) break;
      // Stage 4 
      stage++;
      if( not ::system::Interrupt::init() ) break;      
      // Stage 5
      stage++;
      if( not ::system::Thread::init() ) break;      
      // Stage 6
      stage++;
      if( not ::system::System::init() ) break;      
      // Stage complete
      stage = -1;
      {
        Thread main;
        if(main.isConstructed())
        {
          main.start();
          ::system::Thread::execute();
          error = main.error();
        }
      }
    }while(false);
    switch(stage)
    {
      default:
      case  6: ::system::System::deinit();
      case  5: ::system::Thread::deinit();
      case  4: ::system::Interrupt::deinit();
      case  3: ::Board::deinit();      
      case  2: ::driver::Processor::deinit();
      case  1: ::Allocator::deinit();      
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
  return ::system::Main::main() & 0x0000ffff;
}
#endif // EOOS_VENDOR_BOOT

/**
 * Pointer to constructed heap memory (no boot).
 */
::api::Heap* ::Allocator::heap_;
