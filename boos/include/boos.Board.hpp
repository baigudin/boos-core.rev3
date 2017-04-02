/** 
 * Processor board initialization.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_BOARD_HPP_
#define BOOS_BOARD_HPP_

#include "boos.Types.hpp"
#include "boos.Configuration.hpp"

class Board
{

public:

  /**
   * Initializes a processor board.
   *
   * @param config the operating system configuration.
   * @return true if no errors have been occurred.
   */   
  static bool init(const ::Configuration config);
  
  /**
   * Deinitializes a processor board.
   */
  static void deinit();
  
};
#endif // BOOS_BOARD_HPP_ 
