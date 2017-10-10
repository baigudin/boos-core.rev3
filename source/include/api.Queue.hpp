/** 
 * Queue interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Sergey Baigudin
 */
#ifndef API_QUEUE_HPP_
#define API_QUEUE_HPP_

#include "api.Collection.hpp"

namespace api
{
    /** 
     * @param Type data type of queue element.
     */
    template <typename Type>
    class Queue : public ::api::Collection<Type>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~Queue(){}
        
        /**
         * Inserts new element to this container.
         *
         * @param element inserting element.
         * @return true if element is added.
         */      
        virtual bool add(Type element) = 0;
        
        /**
         * Removes the head element of this container.
         *
         * @return true if an element is removed successfully.
         */
        virtual bool remove() = 0;
        
        /**
         * Examines the head element of this container.
         *
         * @return the head element.
         */
        virtual Type peek() const = 0;
      
    };
}
#endif // API_QUEUE_HPP_
