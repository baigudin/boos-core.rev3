/**
 * System memory configuration for TI TMS320F28335/F28333/F28235 DSCs.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
-heap  0x100
-stack 0x100

MEMORY
{
    /** Program Memory */
PAGE 0:    

    RAM         : origin = 0x008000, length = 0x004000   
    FLASHH      : origin = 0x300000, length = 0x008000
    FLASHG      : origin = 0x308000, length = 0x008000
    FLASHF      : origin = 0x310000, length = 0x008000
    FLASHE      : origin = 0x318000, length = 0x008000
    FLASHD      : origin = 0x320000, length = 0x008000
    FLASHC      : origin = 0x328000, length = 0x008000
    FLASHA      : origin = 0x338000, length = 0x007F80
    BROM        : origin = 0x3fffc0, length = 0x000040
  
    /** Data Memory */
PAGE 1:

    M0          : origin = 0x000000, length = 0x000400
    M1          : origin = 0x000400, length = 0x000400
    PIE         : origin = 0x000d00, length = 0x000100     
    RAM         : origin = 0x00c000, length = 0x003000
    HEAP        : origin = 0x00f000, length = 0x001000
    FLASHB      : origin = 0x330000, length = 0x008000  
}

SECTIONS
{
    /** Hardware interrupts */    
    .pie       : > PIE,     PAGE = 1, type = NOLOAD
  
    /** Allocate program areas */
    .text      : > RAM,     PAGE = 0
    .special   : {
                   ./Debug/Board.obj            (.text)               
                   ./Debug/Configuration.obj    (.text)
                   ./Debug/module.Boot.obj      (.text)
                   ./Debug/module.Pll.obj       (.text)
                   ./Debug/module.Processor.obj (.text)
                   ./Debug/module.Watchdog.obj  (.text)
                   ./Debug/module.Interrupt.obj (.text)                   
                   ./Debug/module.Timer.obj     (.text)                                      
                   ./Debug/kernel.Interrupt.obj (.text)                   
                   ./Debug/kernel.Mutex.obj     (.text)
                   ./Debug/kernel.Semaphore.obj (.text)
                   ./Debug/kernel.Kernel.obj    (.text)                   
                   ./Debug/system.Mutex.obj     (.text)
                   ./Debug/system.Semaphore.obj (.text)
                   ./Debug/system.System.obj    (.text)                   
                   ./Debug/system.Thread.obj    (.text)
                 } 
                 > FLASHA,  PAGE = 0   
    .cinit     : > FLASHA,  PAGE = 0
    .pinit     : > FLASHA,  PAGE = 0
                 
  
    /** Initalized data sections */
    .data      : > FLASHB,  PAGE = 1  
    .econst    : > FLASHB,  PAGE = 1
  
    /** Uninitalized data sections */
    .stack     : > RAM,     PAGE = 1, fill = 0xffff
    .bss       : > RAM,     PAGE = 1, fill = 0xffff      
    .sysmem    : > RAM,     PAGE = 1, fill = 0xffff      
    .ebss      : > RAM,     PAGE = 1, fill = 0xffff
    .esysmem   : > RAM,     PAGE = 1, fill = 0xffff
}
