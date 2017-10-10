/** 
 * List interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2016, Sergey Baigudin
 */
#ifndef API_LIST_HPP_
#define API_LIST_HPP_

#include "api.Collection.hpp"
#include "api.ListIterator.hpp"

namespace api
{
    /** 
     * @param Type data type of list element.
     */ 
    template <typename Type>
    class List : public ::api::Collection<Type>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~List(){}
        
        /**
         * Inserts new element to the end of this container.
         *
         * @param element inserting element.
         * @return true if element is added.
         */      
        virtual bool add(Type element) = 0;
        
        /**
         * Inserts new element to specified position.
         *
         * @param index   position in this container.  
         * @param element inserting element.
         * @return true if element is inserted.
         */
        virtual bool add(int32 index, Type element) = 0;
        
        /**
         * Removes all elements.
         */  
        virtual void clear() = 0;
        
        /**
         * Removes the element at specified position.
         *
         * @param index position in this container.
         * @return true if an element is removed successfully.
         */
        virtual bool remove(int32 index) = 0;
        
        /**
         * Removes the first element.
         *
         * @return true if an element is removed successfully.
         */
        virtual bool removeFirst() = 0;
        
        /**
         * Removes the last element.
         *
         * @return true if an element is removed successfully.
         */
        virtual bool removeLast() = 0;
        
        /**
         * Removes the first occurrence of specified element
         *
         * @param element reference to element.
         * @return true if an element is removed successfully.
         */
        virtual bool removeElement(const Type& element) = 0;
        
        /**
         * Returns an element by index.
         *
         * @param index position in this container.  
         * @return indexed element of this container.
         */
        virtual Type get(int32 index) const = 0;
        
        /**
         * Returns the first element.
         *
         * @return the first element in this container.
         */
        virtual Type getFirst() const = 0;
        
        /**
         * Returns the last element.
         *
         * @return the last element in this container.
         */
        virtual Type getLast() const = 0;
        
        /**
         * Returns a list iterator of elements.
         *
         * You have to call delete operator for returned iterator 
         * after it is used. Given index must not be out of 
         * bounds (index < 0 || index > length()).
         *
         * @param index start position.  
         * @return pointer to new list iterator.
         */
        virtual 
        ::api::ListIterator<Type>* getListIterator(int32 index) = 0;
        
        /**
         * Returns the first occurrenced specified element index.
         *
         * @param element reference to the element.
         * @return index or -1 if this container does not contain 
         *         the element.
         */
        virtual int32 getIndexOf(const Type& element) const = 0;
        
        /**
         * Tests if given index is available.
         *
         * @param index checking position in this container.
         * @return true if index is present.
         */  
        virtual bool isIndex(int32 index) const = 0;
    
    };
}
#endif // API_LIST_HPP_
