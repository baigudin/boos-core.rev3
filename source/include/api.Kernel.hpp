/**
 * Interface of an operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_KERNEL_HPP_
#define API_KERNEL_HPP_

#include "api.Object.hpp"
#include "api.Interrupt.hpp"
#include "api.Task.hpp"

namespace api
{
    class Kernel : public ::api::Object
    {
      
    public:
  
        /** 
         * Destructor.
         */
        virtual ~Kernel(){}
        
        /**
         * Creates new interrupt resource.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source number.
         * @return new interrupt resource.
         */  
        virtual ::api::Interrupt* createInterrupt(::api::Task& handler, int32 source) = 0;
 
    };
}
#endif // API_KERNEL_HPP_
