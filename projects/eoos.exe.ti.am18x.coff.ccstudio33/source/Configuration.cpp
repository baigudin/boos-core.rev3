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
    sourceClock        (25000000),
    cpuClock           (375000000),
    heapAddr           (reinterpret_cast<void*>(0xffff0800)),
    heapSize           (0x00001800){
}
