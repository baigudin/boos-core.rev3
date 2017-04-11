/**
 * System memory configuration for TI TMS320F28335/F28333/F28235 DSCs.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
-heap  0x100
-stack 0x100

MEMORY
{
  /** Program Memory */
PAGE 0:    

  CODE        : origin = 0x008000, length = 0x006000
  FLASHH      : origin = 0x300000, length = 0x008000
  FLASHG      : origin = 0x308000, length = 0x008000
  FLASHF      : origin = 0x310000, length = 0x008000
  FLASHE      : origin = 0x318000, length = 0x008000
  FLASHD      : origin = 0x320000, length = 0x008000
  FLASHC      : origin = 0x328000, length = 0x008000
  FLASHB      : origin = 0x330000, length = 0x008000
  FLASHA      : origin = 0x338000, length = 0x007F80
  BROM        : origin = 0x3fffc0, length = 0x000040

  /** Data Memory */
PAGE 1:

  M0          : origin = 0x000000, length = 0x000400
  M1          : origin = 0x000400, length = 0x000400   /** User heap of BOOS */
  PIE         : origin = 0x000d00, length = 0x000100     
  DATA        : origin = 0x00e000, length = 0x002000   

}

SECTIONS
{
   /** Hardware interrupts */    
   .hwi                : > PIE,     PAGE = 1

   /** Allocate program areas */
   .cinit              : > CODE,    PAGE = 0
   .pinit              : > CODE,    PAGE = 0
   .text               : > FLASHA,  PAGE = 0

   /** Initalized data sections */
   .cio                : > DATA,    PAGE = 1
   .switch             : > DATA,    PAGE = 1
   .econst             : > DATA,    PAGE = 1

   /** Uninitalized data sections */
   .ebss               : > DATA,    PAGE = 1, fill = 0xffff
   .esysmem            : > DATA,    PAGE = 1, fill = 0xffff
   .stack              : > M0,      PAGE = 1, fill = 0xffff
   .bss                : > M0,      PAGE = 1, fill = 0xffff
   
}
