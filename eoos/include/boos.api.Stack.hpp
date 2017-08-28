/**
 * Stack interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_API_STACK_HPP_
#define BOOS_API_STACK_HPP_

#include "boos.api.Collection.hpp"

namespace api
{
    
  /** 
   * @param Type data type of default stack element.
   */ 
  template <typename Type>  
  class Stack : public ::api::Collection<Type>
  { 
  
  public:
  
    /**
     * Stack operations.
     *
     * Stack operations:
     * - Full stacks have stack pointers that point to the last used location.
     * - Empty stacks have stack pointers that point to the first unused location.
     * - Descending stacks grow towards decreasing memory addresses.
     * - Ascending stacks grow towards increasing memory addresses.
     */
    enum Operation
    {
      /**
       * Full Descending.
       */
      FD = 0,
      
      /**
       * Empty Descending.
       */
      ED = 1,
      
      /**
       * Full Ascending.
       */
      FA = 2,
      
      /**
       * Empty Ascending.
       */
      EA = 3

    };
  
    /** 
     * Destructor.
     */    
    virtual ~Stack(){}

    /** 
     * Returns an initial top of stack.
     *
     * @return a memory address to top of this stack when object was built.
     */    
    virtual const Type* tos() = 0;
    
    /** 
     * Returns an type of stack operation.
     *
     * @return the stack operation.
     */    
    virtual Operation type() const = 0;

  };
}
#endif // BOOS_API_STACK_HPP_
