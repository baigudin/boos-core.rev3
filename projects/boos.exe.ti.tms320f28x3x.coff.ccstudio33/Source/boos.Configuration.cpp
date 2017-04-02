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
  sourceClock        (30000000),
  cpuClock           (150000000),
  heapAddr           (reinterpret_cast<void*>(0x00000400)),
  heapSize           (0x00000400){
}
