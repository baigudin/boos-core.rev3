/**
 * Heap memory interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_HEAP_HPP_
#define API_HEAP_HPP_

#include "api.Toggle.hpp"

namespace api
{
  class Heap : public ::api::Object
  {
    
  public:

    /** 
     * Destructor.
     */
    virtual ~Heap(){}
    
    /**
     * Allocates memory.
     *
     * @param size required memory size in byte.
     * @param ptr  NULL value becomes to allocate memory, and 
     *             other given values are simply returned 
     *             as memory address.
     * @return pointer to allocated memory or NULL.
     */    
    virtual void* alloc(size_t size, void* ptr) = 0;
      
    /**
     * Frees an allocated memory.
     *
     * @param ptr pointer to allocated memory.
     */      
    virtual void free(void* ptr) = 0;
    
    /**
     * Frees an allocated memory.
     *
     * The argument toggle interface disables and enables thread context switching. 
     * The most useful case is to give a global interrupts toggle interface. 
     * Reference to pointer is passed for using or no using a toggle. 
     * When referenced pointer equals null, toggling is not used, and 
     * when referenced pointer equals a value, toggling is used, accordantly.
     *
     * @param toggle reference to pointer to some controller.
     */      
    virtual void toggle(::api::Toggle*& toggle) = 0;

  };
}
#endif // API_HEAP_HPP_
