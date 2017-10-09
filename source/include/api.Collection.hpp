/** 
 * The root interface of some collections.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_COLLECTION_HPP_
#define API_COLLECTION_HPP_

#include "api.IllegalValue.hpp"

namespace api
{
    /** 
     * @param Type data type of collection element.
     */ 
    template <typename Type>
    class Collection : public ::api::IllegalValue<Type>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~Collection(){}
       
        /**
         * Returns a number of elements in this container.
         *
         * @return number of elements.
         */
        virtual int32 getLength() const = 0;
       
        /**
         * Tests if this collection has elements.
         *
         * @return true if this collection does not contain any elements.
         */
        virtual bool isEmpty() const = 0;
  
    };
}
#endif // API_COLLECTION_HPP_
