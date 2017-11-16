/**
 * Interface of setting and getting a value.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_VALUE_HPP_
#define API_VALUE_HPP_

#include "api.IllegalValue.hpp"

namespace api
{
    /** 
     * @param Type data type of list element.
     */ 
    template <typename Type>    
    class Value : public ::api::IllegalValue<Type>
    {
      
    public:
  
        /** 
         * Destructor.
         */
        virtual ~Value(){}
        
        /**
         * Sets a value.
         *
         * @param value a value for setting.
         */    
        virtual void setValue(Type value) = 0;
          
        /**
         * Returns set value.
         *
         * @return the set value.
         */      
        virtual Type getValue() const = 0;

    };
}
#endif // API_VALUE_HPP_
