/** 
 * Illegal value interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Sergey Baigudin
 */
#ifndef API_ILLEGAL_VALUE_HPP_
#define API_ILLEGAL_VALUE_HPP_

#include "api.Object.hpp"

namespace api
{
    /** 
     * @param Type data type of illegal value.
     */ 
    template <typename Type>
    class IllegalValue  : public ::api::Object
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~IllegalValue(){}
        
        /**
         * Returns illegal element returning as error value.
         *
         * @return illegal element.
         */
        virtual Type getIllegal() const = 0;
        
        /**
         * Sets illegal element returning as error value.
         *
         * @param value illegal value.
         */
        virtual void setIllegal(Type value) = 0;
        
        /**
         * Tests if given value is an illegal.
         *
         * @param value testing value.
         * @param true if value is an illegal.
         */
        virtual bool isIllegal(const Type& value) const = 0;
  
    };
}
#endif // API_ILLEGAL_VALUE_HPP_
