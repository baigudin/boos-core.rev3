/** 
 * Iterator interface. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_ITERATOR_HPP_
#define API_ITERATOR_HPP_

#include "api.IllegalValue.hpp"

namespace api
{
    /** 
     * @param Type data type of iterator element.
     */ 
    template <typename Type>
    class Iterator : public ::api::IllegalValue<Type>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~Iterator(){}
        
        /**
         * Returns next element and advances the cursor position.
         *
         * @return reference to element.
         */      
        virtual Type getNext() = 0;
        
        /**
         * Tests if this iteration may return a next element.
         *
         * @return true if next element is had.
         */      
        virtual bool hasNext() const = 0;
        
        /**
         * Removes the last element returned by this iterator.
         *
         * @return true if an element is removed successfully.
         */
        virtual bool remove() = 0;

    };
}
#endif // API_ITERATOR_HPP_
