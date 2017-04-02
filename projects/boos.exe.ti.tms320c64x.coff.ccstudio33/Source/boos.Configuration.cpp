/** 
 * The configuration of a target processor.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#include "boos.Configuration.hpp"
 
/** 
 * Constructor.
 */     
Configuration::Configuration() :
  sourceClock        (36000000),
  cpuClock           (720000000),
  heapAddr           (reinterpret_cast<void*>(0x00031000)),
  heapSize           (0x0000f000){
}
