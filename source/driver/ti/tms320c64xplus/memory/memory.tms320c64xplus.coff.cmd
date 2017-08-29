/**
 * System memory configuration for TI TMS320C64x+ DSPs.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
-heap  0x1000
-stack 0x100

MEMORY
{
  /** Hardware interrupts */
  HWI        : origin = 0x00900000, len = 0x00000200
  /** Programme memory */
  CODE       : origin = 0x00900200, len = 0x0002fe00
  /** Heap of TI RTS Library */
  HEAP       : origin = 0x00930000, len = 0x00001000    
  /** User heap of OS */
  MEMORY     : origin = 0x00031000, len = 0x0000f000
}

SECTIONS
{
  .hwi       : load = HWI
  .text      : load = CODE
  .data      : load = CODE
  .bss       : load = CODE, fill = 0x00000000
  .far       : load = CODE, fill = 0x00000000
  .cinit     : load = CODE
  .pinit     : load = CODE
  .const     : load = CODE
  .cio       : load = CODE
  .switch    : load = CODE
  .stack     : load = CODE
/*.template  : load = CODE IS ILLEGAL FOR 7.2 CCS COMPILER.*/
  .sysmem    : load = HEAP
}
