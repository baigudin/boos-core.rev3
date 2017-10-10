/** 
 * Resource interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2015, Sergey Baigudin
 */
#ifndef API_RESOURCE_HPP_
#define API_RESOURCE_HPP_

#include "api.Object.hpp"

namespace api
{
    class Resource : public ::api::Object
    {
  
    public:
    
        /** 
         * Destructor.
         */
        virtual ~Resource(){}
        
        /** 
         * Tests if this resource is blocked.
         *
         * @return true if this resource is blocked.
         */ 
        virtual bool isBlocked() = 0;
  
    };
}
#endif // API_RESOURCE_HPP_
