/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp"
#include "system.System.hpp"
#include "system.Semaphore.hpp"

/**
 * The user application entry method.
 *
 * The test results:
 *
 * EOOS RT 1.0 & TI TMS320C6457 @ 1000 MHz
 * 270_427_597 ns : unfair
 * 315_498_577 ns : fair
 * 
 * BOOS Core 2.2 & TI TMS320C6416 @ 720 MHz
 * 362_940_755 ns : unfair  
 * 413_002_644 ns : fair      
 * 
 * ZOSRT Hydra & TI TMS320C6416 @ 720 MHz
 * 417_114_355 ns
 *
 * Windows 7 & AMD Phenom II X4 B55 @ 3200 MHz
 * 499_000_000 ns  
 * 
 * Windows 7 & Intel Core i5-3570 @ 3400 MHz
 * 514_000_000 ns 
 *
 * Windows 7 & Intel Pentium Dual-Core E5400 @ 2700 MHz
 * 1_075_000_000 ns
 * 
 * Windows 10 & AMD FX-8150 Eight-Core Processor @ 3600 MHz
 * 1_234_000_000 ns
 * 
 * Windows XP & Intel Pentium 4 @ 3000 MHz
 * 1_750_000_000 ns 
 *
 * Out of the test results:
 * 
 * BOOS Core 2.2 & TI TMS320C6412 @ 500 MHz
 * 787_355_280 ns : unfair *old
 * 899_546_288 ns : fair   *old
 * 
 * BOOS Core 2.2 & TI AM1808 @ 375 MHz
 * 7_833_976_200 ns : unfair *old 
 * 8_511_705_080 ns : fair   *old
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
  // Create and check a semaphore
  ::system::Semaphore rsem(1, false);
  if(!rsem.isConstructed()) return 1;  
  // Create a semaphore interface of the semaphore,
  // because normally, semaphores are released 
  // by references or pointers
  ::api::Semaphore& isem = rsem;
  volatile int64 time[2], result;
  time[0] = ::system::System::nanoTime();
  for(int32 i=0; i<1000000; i++)
  {
    rsem.acquire(1);
    isem.release(1);
  }
  time[1] = ::system::System::nanoTime();
  result = time[1] - time[0];
  return result ? 0 : 1;
}
