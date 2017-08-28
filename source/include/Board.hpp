/** 
 * Processor board initialization.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "Types.hpp"
#include "Configuration.hpp"

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
#endif // BOARD_HPP_ 
