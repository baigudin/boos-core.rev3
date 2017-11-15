/** 
 * Memory allocator.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef ALLOCATOR_HPP_
#define ALLOCATOR_HPP_

#include "api.Heap.hpp"

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
        return NULL;
    }
  
    /**
     * Frees an allocated memory.
     *
     * @param ptr address of allocated memory block or a null pointer.
     */      
    static void free(void* ptr)
    {
    }

};
#endif // ALLOCATOR_HPP_
