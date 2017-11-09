/** 
 * The configuration of a target processor.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Configuration.hpp"
 
/** 
 * Constructor.
 */     
Configuration::Configuration() :
    sourceClock (50000000),
    cpuClock    (1000000000),
    heapAddr    (reinterpret_cast<void*>(0x00881000)),
    heapSize    (0x0007f000),
    stackSize   (0x00000800){
}
