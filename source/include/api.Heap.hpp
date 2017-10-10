/**
 * Heap memory interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Sergey Baigudin
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
        virtual void* allocate(size_t size, void* ptr) = 0;
          
        /**
         * Frees an allocated memory.
         *
         * @param ptr pointer to allocated memory.
         */      
        virtual void free(void* ptr) = 0;
        
        /**
         * Sets an allocated memory.
         *
         * The method allows disabling and enabling thread context 
         * switching when memory is being allocated or freed. 
         * Thus, the best way is to pass an interface of global 
         * interrupt toggling. The parameter type is reference to 
         * pointer, as when referenced pointer equals to NULL, 
         * no blocks are happening.
         *
         * @param toggle reference to pointer to some controller.
         */      
        virtual void setToggle(::api::Toggle*& toggle) = 0;
  
    };
}
#endif // API_HEAP_HPP_
