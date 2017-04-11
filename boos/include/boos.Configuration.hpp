/** 
 * The configuration of a target processor.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_CONFIGURATION_HPP_
#define BOOS_CONFIGURATION_HPP_

#include "boos.Types.hpp"

struct Configuration
{

public:

  /**
   * Source clock of CPU oscillator in Hz.
   */      
  int64 sourceClock;
  
  /**
   * CPU clock in Hz.
   */  
  int64 cpuClock;

  /**
   * Start address of heap page.
   */      
  void* heapAddr;    
  
  /**
   * Size of heap page in bytes.
   */
  int64 heapSize;   

  /** 
   * Constructor.
   */     
  Configuration();
  
  /** 
   * Copy constructor.
   */     
  Configuration(const Configuration& obj) :
    sourceClock (obj.sourceClock),
    cpuClock    (obj.cpuClock),
    heapAddr    (obj.heapAddr),
    heapSize    (obj.heapSize){
  }
      
  /** 
   * Destructor.
   */
 ~Configuration()
  {
  }

  /**
   * Assignment operator.
   *
   * @param obj reference to source object.
   * @return reference to this object.     
   */
  Configuration& operator =(const Configuration& obj)
  {
    sourceClock = obj.sourceClock;
    cpuClock    = obj.cpuClock;
    heapAddr    = obj.heapAddr;
    heapSize    = obj.heapSize;
    return *this;
  }
     
};
#endif // BOOS_CONFIGURATION_HPP_
