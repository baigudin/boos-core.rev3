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
    static void* allocate(size_t size)
    {
        return heap_ != NULL ? heap_->allocate(size, NULL) : NULL;
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
    static bool initialize(const ::Configuration config)
    {
        heap_ = NULL;
        void* addr = config.heapAddr;
        int64 size = config.heapSize;
        if(addr == NULL || size <= 0) return false;
        heap_ = new (addr) ::utility::Heap(size);
        if(heap_ == NULL || not heap_->isConstructed()) heap_ = NULL;        
        return heap_ != NULL ? true : false;
    }
    
    /**
     * Deinitializes the driver.
     */
    static void deinitialize() 
    {
    }
  
private:
  
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
