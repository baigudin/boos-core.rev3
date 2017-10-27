/**
 * Runtime program execution interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_RUNTIME_HPP_
#define API_RUNTIME_HPP_

#include "api.Object.hpp"

namespace api
{
    class Runtime : public ::api::Object    
    {
      
    public:
  
        /** 
         * Destructor.
         */
        virtual ~Runtime(){}
        
        /**
         * Terminates a program execution.
         *
         * @param status a termination status.
         */    
        virtual void terminate(int32 status) = 0;

    };
}
#endif // API_RUNTIME_HPP_
