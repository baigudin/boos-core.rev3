/** 
 * TI TMS320F28x3x CPU Timer Registers. 
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REG_TIMER_HPP_
#define MODULE_REG_TIMER_HPP_

#include "Types.hpp"

namespace module
{
    namespace reg
    {
        struct Timer
        {
      
        public:
          
            static const uint32 ADDRESS0 = 0x00000c00;
            static const uint32 ADDRESS1 = 0x00000c08;
            static const uint32 ADDRESS2 = 0x00000c10;
            
            /** 
             * Constructor.
             */  
            Timer() :
                tim  (0),
                timh (0),
                prd  (0),
                prdh (0),
                tcr  (0),
                tpr  (0),
                tprh (0){
            }
            
            /** 
             * Destructor.
             */  
           ~Timer(){}
           
            /**
             * Operator new.
             *
             * @param size unused.
             * @param ptr  address of memory.
             * @return address of memory.
             */
            void* operator new(uint32, uint32 ptr)
            {
                return reinterpret_cast<void*>(ptr);
            }
            
            /**
             * Counter Register.
             */
            union Tim
            {
                Tim(){}
                Tim(uint16 v){val = v;}          
               ~Tim(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 tim: 16;
                } bit;
            } tim;
            
            /**
             * Counter Register High.
             */
            union Timh
            {
                Timh(){}
                Timh(uint16 v){val = v;}          
               ~Timh(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 timh: 16;
                } bit;
            } timh;
            
            /**
             * Period Register.
             */
            union Prd
            {
                Prd(){}
                Prd(uint16 v){val = v;}          
               ~Prd(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 prd: 16;
                } bit;
            } prd;
          
            /**
             * Period Register High.
             */
            union Prdh
            {
                Prdh(){}
                Prdh(uint16 v){val = v;}          
               ~Prdh(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 prdh: 16;
                } bit;
            } prdh;
          
            /**
             * Control Register.
             */
            union Tcr
            {
                Tcr(){}
                Tcr(uint16 v){val = v;}          
               ~Tcr(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16      : 4;
                    uint16 tss  : 1;
                    uint16 trb  : 1;
                    uint16      : 4;
                    uint16 soft : 1;
                    uint16 free : 1;
                    uint16      : 2;
                    uint16 tie  : 1;
                    uint16 tif  : 1;
                } bit;
            } tcr;
          
        private:
          
            uint16 space0_[1];
            
        public:
          
            /**
             * Prescale Register.
             */
            union Tpr
            {
                Tpr(){}
                Tpr(uint16 v){val = v;}          
               ~Tpr(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 tddr : 8;
                    uint16 psc  : 8;
                } bit;
            } tpr;
          
            /**
             * Prescale Register High.
             */
            union Tprh
            {
                Tprh(){}
                Tprh(uint16 v){val = v;}          
               ~Tprh(){}    
              
                uint16 val;
                struct Val 
                {
                    uint16 tddrh : 8;
                    uint16 psch  : 8;
                } bit;
            } tprh;
                 
        };
    }
} 
#endif // MODULE_REG_TIMER_HPP_
