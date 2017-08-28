/** 
 * Memory allocator.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef ALLOCATOR_HPP_
#define ALLOCATOR_HPP_

#include "utility.Heap.hpp"
#include "Configuration.hpp"

class Allocator
{

public:

  /**
   * Allocates memory.
   *
   * @param size number of bytes to allocate.
   * @return allocated memory address or a null pointer.
   */    
  static void* alloc(size_t size)
  {
    return heap_ != NULL ? heap_->alloc(size, NULL) : NULL;
  }

  /**
   * Frees an allocated memory.
   *
   * @param ptr address of allocated memory block or a null pointer.
   */      
  static void free(void* ptr)
  {
    if(heap_ != NULL && ptr != NULL) heap_->free(ptr);  
  }

  /**
   * Returns the heap memory.
   *
   * @return heap memory of the allocator, or NULL if it has not been initialized.
   */
  static ::api::Heap* getHeap()
  {
    return heap_;
  }
  
  /**
   * Initializes the driver.
   *
   * @param config the operating system configuration.
   * @return true if no errors have been occurred.
   */   
  static bool init(const ::Configuration config)
  {
    setHeap(config.heapAddr, config.heapSize);
    return heap_ != NULL ? true : false;
  }
  
  /**
   * Deinitializes the driver.
   */
  static void deinit() 
  {
  }
  
private:

  /**
   * Sets heap memory.
   *
   * @param add  address of heap memory.
   * @param size number of bytes of heap memory.   
   * @return true if no errors.
   */
  static void setHeap(void* addr, int64 size)
  {
    heap_ = addr != NULL && size > 0 ? new (addr) ::utility::Heap(size) : NULL;
    if(heap_ == NULL || !heap_->isConstructed()) heap_ = NULL;
  }

  /**
   * Pointer to constructed heap memory (no boot).
   *
   * The field has been determined in the operating system. 
   * If the allocator is being used independently, 
   * the field has to be determined by a programmer at someplace.
   */
  static ::api::Heap* heap_;  
  
};
#endif // ALLOCATOR_HPP_
