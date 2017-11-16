/**
 * System memory configuration for TI TMS320C64x DSPs.
 * 
 * This is an example of command linker file which represents 
 * 256K internal L2 RAM memory map for TI TMS320C64x DSPs.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
-heap  0x1000
-stack 0x100

MEMORY
{
    /** Hardware interrupts */
    HWI        : origin = 0x00000000, len = 0x00000200
    /** Programme memory */
    CODE       : origin = 0x00000200, len = 0x0002fe00
    /** Heap of TI RTS Library */
    TI_HEAP    : origin = 0x00030000, len = 0x00001000    
    /** Heap of OS */
    OS_HEAP    : origin = 0x00031000, len = 0x0000f000
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
    .template  : load = CODE /* IS ILLEGAL FOR 7.2 CCS COMPILER */
    .sysmem    : load = TI_HEAP
}
