/** 
 * A central processing unit phase-locked loop controller resource interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_PROCESSOR_PLL_HPP_
#define API_PROCESSOR_PLL_HPP_

#include "api.Object.hpp"

namespace api
{
    class ProcessorPll : public ::api::Object
    {

    public:
    
        /**
         * Destructor.
         */                               
        virtual ~ProcessorPll(){}

        /**
         * Returns source clock of CPU oscillator in Hz.
         *
         * @return frequency value in Hz.         
         */      
        virtual int64 getSourceClock() = 0;
    
        /**
         * Returns source clock of CPU in Hz.
         *
         * @return frequency value in Hz.
         */  
        virtual int64 getCpuClock() = 0;

    };
}
#endif // API_PROCESSOR_PLL_HPP_
