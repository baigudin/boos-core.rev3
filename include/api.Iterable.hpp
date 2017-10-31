/** 
 * Iterable interface. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_ITERABLE_HPP_
#define API_ITERABLE_HPP_

#include "api.Object.hpp"
#include "api.Iterator.hpp"

namespace api
{
    /** 
     * @param Type data type of element.
     */ 
    template <typename Type>
    class Iterable : public ::api::Object
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~Iterable(){}
       
        /**
         * Returns an iterator of elements.
         *
         * You have to call the delete operator for returned iterator when 
         * it has been used, and you do not need to iterate a collection.
         *
         * @return pointer to new iterator.
         */
        virtual ::api::Iterator<Type>* getIterator() = 0;
  
    };
}
#endif // API_ITERABLE_HPP_
