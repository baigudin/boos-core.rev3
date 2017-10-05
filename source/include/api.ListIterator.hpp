/** 
 * List iterator interface. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_LIST_ITERATOR_HPP_
#define API_LIST_ITERATOR_HPP_

#include "api.Iterator.hpp"

namespace api
{
    /** 
     * @param Type data type of list iterator element.
     */
    template <typename Type>
    class ListIterator : public ::api::Iterator<Type>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~ListIterator(){}
        
        /**
         * Inserts the specified element into the list.
         *
         * Method inserts given element before the element 
         * that will be returned by next method.
         * Therefore subsequent call to next will be unaffected, 
         * and a subsequent call to prev will return the inserted element. 
         *
         * @param element inserting element.
         * @return true if element is added.
         */      
        virtual bool add(Type element) = 0;
        
        /**
         * Returns previous element and advances the cursor backwards.
         *
         * @return reference to element.
         */      
        virtual Type getPrevious() = 0;
        
        /**
         * Tests if this iteration may return a previous element.
         *
         * @return true if previous element is had.
         */      
        virtual bool hasPrevious() const = 0;
        
        /**
         * Returns the index of the element that would be returned by a subsequent call to next().
         *
         * @return index of the next element or list size if the list iterator is at the end of the list.
         */      
        virtual int32 getNextIndex() const = 0;
        
        /**
         * Returns the index of the element that would be returned by a subsequent call to prev().
         *
         * @return index of the previous element or -1 if the list iterator is at the beginning of the list.
         */      
        virtual int32 getPreviousIndex() const = 0;
    
    };
}
#endif // API_LIST_ITERATOR_HPP_
