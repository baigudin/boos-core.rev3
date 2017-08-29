/** 
 * Processor board initialization.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Board.hpp"

/**
 * Initializes a processor board.
 *
 * @param config the operating system configuration.
 * @return true if no errors have been occurred.
 */
bool Board::init(const ::Configuration config)
{
  // The simplest example for doing something
  return config.cpuClock > 0 ? true : false;
}

/**
 * Deinitializes a processor board.
 */
void Board::deinit()
{
}
