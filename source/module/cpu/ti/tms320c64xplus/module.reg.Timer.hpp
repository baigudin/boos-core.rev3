/**
 * TI TMS320C64x+ 64-Bit Timer registers.
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
          
            /**
             * Timer 0 memory mapped address.
             */    
            static const uint32 ADDRESS0 = 0x02940000;
            
            /**
             * Timer 1 memory mapped address.
             */          
            static const uint32 ADDRESS1 = 0x02980000;
          
            /** 
             * Constructor.
             */  
            Timer() :
                emumgtClkspd (),
                cntlo        (),
                cnthi        (),
                prdlo        (),
                prdhi        (),
                tcr          (),
                tgcr         (),
                wdtcr        (){
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
          
        private:
          
            uint32 space0_[0x1];
            
        public:
            
            /**
             * Emulation management and clock speed register.
             */
            union EmumgtClkspd
            {
                EmumgtClkspd(){}
                EmumgtClkspd(uint32 v){value = v;}
               ~EmumgtClkspd(){}    
              
                uint32 value;
                struct 
                {
                    uint32 free   : 1;
                    uint32 soft   : 1;
                    uint32        : 14;          
                    uint32 clkdiv : 4;
                    uint32        : 12;          
                } bit;
            } emumgtClkspd;
            
        private:
          
            uint32 space1_[0x2];
            
        public:      
          
            /**
             * Counter register low.
             */
            union Cntlo
            {
                Cntlo(){}
                Cntlo(uint32 v){value = v;}
               ~Cntlo(){}    
              
                uint32 value;
                struct 
                {
                    uint32 cnt : 32;
                } bit;
            } cntlo;
          
            /**
             * Counter register high.
             */
            union Cnthi
            {
                Cnthi(){}
                Cnthi(uint32 v){value = v;}
               ~Cnthi(){}    
              
                uint32 value;
                struct 
                {
                    uint32 cnt : 32;
                } bit;
            } cnthi;
          
            /**
             * Period register low.
             */
            union Prdlo
            {
                Prdlo(){}
                Prdlo(uint32 v){value = v;}
               ~Prdlo(){}    
              
                uint32 value;
                struct 
                {
                    uint32 prd : 32;
                } bit;
            } prdlo;
          
            /**
             * Period register high.
             */
            union Prdhi
            {
                Prdhi(){}
                Prdhi(uint32 v){value = v;}
               ~Prdhi(){}    
              
                uint32 value;
                struct 
                {
                    uint32 prd : 32;
                } bit;
            } prdhi;
          
            /**
             * Timer control register.
             */
            union Tcr
            {
                Tcr(){}
                Tcr(uint32 v){value = v;}
               ~Tcr(){}    
              
                uint32 value;
                struct 
                {
                    uint32 tstatLo   : 1;
                    uint32 invoutpLo : 1;
                    uint32 invinpLo  : 1;
                    uint32 cpLo      : 1;
                    uint32 pwidLo    : 2;
                    uint32 enamodeLo : 2;
                    uint32 clksrcLo  : 1;
                    uint32 tienLo    : 1;
                    uint32           : 6;
                    uint32 tstatHi   : 1;
                    uint32 invoutpHi : 1;
                    uint32           : 1;
                    uint32 cpHi      : 1;
                    uint32 pwidHi    : 2;
                    uint32 enamodeHi : 2;
                    uint32           : 8;
                } bit;
            } tcr;
          
            /**
             * Timer global control register.
             */
            union Tgcr
            {
                Tgcr(){}
                Tgcr(uint32 v){value = v;}
               ~Tgcr(){}    
              
                uint32 value;
                struct 
                {
                    uint32 timlors : 1;
                    uint32 timhirs : 1; 
                    uint32 timmode : 2; 
                    uint32         : 4;
                    uint32 pschi   : 4;
                    uint32 tddrhi  : 4;
                    uint32         : 8;
                } bit;
            } tgcr;
          
            /**
             * Watchdog timer control register.
             */
            union Wdtcr
            {
                Wdtcr(){}
                Wdtcr(uint32 v){value = v;}
               ~Wdtcr(){}    
              
                uint32 value;
                struct 
                {
                    uint32         : 12;
                    uint32 wdiekey : 2;
                    uint32 wden    : 1;
                    uint32 wdflag  : 1;
                    uint32 wdkey   : 16;
                } bit;
            } wdtcr;
      
        };    
    }
}
#endif // MODULE_REG_TIMER_HPP_
