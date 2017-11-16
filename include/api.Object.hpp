/**
 * Root interface of the system class hierarchy.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015-2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_OBJECT_HPP_
#define API_OBJECT_HPP_

#include "Types.hpp"

namespace api
{  
    class Object
    {
  
    public:
  
        /** 
         * Destructor.
         */
        virtual ~Object(){}
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const = 0;
        
        /**
         * Tests if given object has been constructed object.
         *
         * @param obj pointer to object.
         * @return true if object has been constructed successfully.
         */
        template<class Type>
        static inline bool isObject(const Type* obj)
        {
          return obj != NULL ? obj->isConstructed() : false;    
        }
      
    };
}
#endif // API_OBJECT_HPP_
