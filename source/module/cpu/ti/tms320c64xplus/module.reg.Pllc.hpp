/** 
 * TI TMS320C645x Phase-Locked Loop Controller (PLLC).
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REG_PLLC_HPP_
#define MODULE_REG_PLLC_HPP_

#include "Types.hpp"

namespace module
{
    namespace reg
    {
        struct Pllc
        {
      
        public:
          
            /**
             * PLL1 Controller (including Reset Controller) Registers .
             */    
            static const uint32 ADDRESS1 = 0x029A0000;
            
            /**
             * PLL2 Controller Registers.
             */      
            static const uint32 ADDRESS2 = 0x029C0000;      
            
            /** 
             * Constructor.
             */  
            Pllc() :
                pllctl   (),
                pllm     (),
                prediv   (),
                plldiv1  (),
                plldiv2  (),
                plldiv3  (),
                postdiv  (),
                pllcmd   (),
                pllstat  (),
                alnctl   (),
                dchange  (),
                cken     (),
                ckstat   (),
                systat   (),
                plldiv4  (),
                plldiv5  (),
                plldiv6  (),
                plldiv7  (),
                plldiv8  (),
                plldiv9  (),
                plldiv10 (),
                plldiv11 (),
                plldiv12 (),
                plldiv13 (),
                plldiv14 (),
                plldiv15 (),
                plldiv16 (){
            }
          
            /** 
             * Destructor.
             */  
           ~Pllc(){}
           
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
             * PLL controller divider register 1 - 16.
             */
            union Plldiv
            {
                Plldiv(){}
                Plldiv(uint32 v){value = v;}
               ~Plldiv(){}    
              
                uint32 value;
                struct 
                {
                    uint32 ratio  : 5;
                    uint32        : 10;          
                    uint32 den    : 1;
                    uint32        : 16;
                } bit;
            };      
            
        private:        
          
            uint32 space0_[64];
            
        public:
          
            /**
             * PLL control register.
             */
            union Pllctl
            {
                Pllctl(){}
                Pllctl(uint32 v){value = v;}
               ~Pllctl(){}    
              
                uint32 value;
                struct 
                {
                    uint32 pllen    : 1;
                    uint32 pllpwrdn : 1;
                    uint32          : 1;
                    uint32 pllrst   : 1;
                    uint32          : 1;
                    uint32 pllensrc : 1;
                    uint32          : 26;
                } bit;
            } pllctl;
            
        private:
          
            uint32 space1_[3];
            
        public:
            
            /**
             * PLL multiplier control register.
             */
            union Pllm
            {
                Pllm(){}
                Pllm(uint32 v){value = v;}
               ~Pllm(){}    
              
                uint32 value;
                struct 
                {
                    uint32 pllm : 6;
                    uint32      : 26;
                } bit;
            } pllm;
            
            /**
             * PLL pre-divider control register.
             */
            union Prediv
            {
                Prediv(){}
                Prediv(uint32 v){value = v;}
               ~Prediv(){}    
              
                uint32 value;
                struct 
                {
                    uint32 ratio  : 5;
                    uint32        : 10;          
                    uint32 preden : 1;
                    uint32        : 16;
                } bit;
            } prediv;
            
            /**
             * PLL controller divider register 1.
             */      
            Plldiv plldiv1;
            
            /**
             * PLL controller divider register 2.
             */      
            Plldiv plldiv2;
            
            /**
             * PLL controller divider register 3.
             */      
            Plldiv plldiv3;
            
        private:
          
            uint32 space2_[1];
            
        public:
          
            /**
             * PLL post-divider control register.
             */
            union Postdiv
            {
                Postdiv(){}
                Postdiv(uint32 v){value = v;}
               ~Postdiv(){}    
              
                uint32 value;
                struct 
                {
                    uint32 ratio  : 5;
                    uint32        : 10;          
                    uint32 preden : 1;
                    uint32        : 16;
                } bit;
            } postdiv;          
            
        private:
          
            uint32 space3_[3];
            
        public:
            
            /**
             * PLL controller command register.
             */
            union Pllcmd
            {
                Pllcmd(){}
                Pllcmd(uint32 v){value = v;}
               ~Pllcmd(){}    
              
                uint32 value;
                struct 
                {
                    uint32 goset : 1;
                    uint32       : 31;
                } bit;
            } pllcmd;
            
            /**
             * PLL controller status register.
             */
            union Pllstat
            {
                Pllstat(){}
                Pllstat(uint32 v){value = v;}
               ~Pllstat(){}    
              
                uint32 value;
                struct 
                {
                    uint32 : 0;
                    uint32 : 0;
                    uint32 : 0;
                } bit;
            } pllstat;
            
            /**
             * PLL controller clock align control register.
             */
            union Alnctl
            {
                Alnctl(){}
                Alnctl(uint32 v){value = v;}
               ~Alnctl(){}    
              
                uint32 value;
                struct 
                {
                    uint32 al1  : 1;
                    uint32 al2  : 1;
                    uint32 al3  : 1;
                    uint32 al4  : 1;
                    uint32 al5  : 1;
                    uint32 al6  : 1;
                    uint32 al7  : 1;
                    uint32 al8  : 1;
                    uint32 al9  : 1;
                    uint32 al10 : 1;
                    uint32 al11 : 1;
                    uint32 al12 : 1;
                    uint32 al13 : 1;
                    uint32 al14 : 1;
                    uint32 al15 : 1;
                    uint32 al16 : 1;          
                    uint32      : 16;
                } bit;
            } alnctl;
            
            /**
             * PLLDIV divider ratio change status register.
             */
            union Dchange
            {
                Dchange(){}
                Dchange(uint32 v){value = v;}
               ~Dchange(){}    
              
                uint32 value;
                struct 
                {
                    uint32 sys1  : 1;
                    uint32 sys2  : 1;
                    uint32 sys3  : 1;
                    uint32 sys4  : 1;
                    uint32 sys5  : 1;
                    uint32 sys6  : 1;
                    uint32 sys7  : 1;
                    uint32 sys8  : 1;
                    uint32 sys9  : 1;
                    uint32 sys10 : 1;
                    uint32 sys11 : 1;
                    uint32 sys12 : 1;
                    uint32 sys13 : 1;
                    uint32 sys14 : 1;
                    uint32 sys15 : 1;
                    uint32 sys16 : 1;
                    uint32       : 16;
                } bit;
            } dchange;
            
            /**
             * Clock enable control register.
             */
            union Cken
            {
                Cken(){}
                Cken(uint32 v){value = v;}
               ~Cken(){}    
              
                uint32 value;
                struct 
                {
                    uint32 auxen : 1;
                    uint32       : 31;
                } bit;
            } cken;
            
            /**
             * Clock status register.
             */
            union Ckstat
            {
                Ckstat(){}
                Ckstat(uint32 v){value = v;}
               ~Ckstat(){}    
              
                uint32 value;
                struct 
                {
                    uint32 auxon : 1;
                    uint32       : 31;
                } bit;
            } ckstat;
            
            /**
             * SYSCLK status register.
             */
            union Systat
            {
                Systat(){}
                Systat(uint32 v){value = v;}
               ~Systat(){}    
              
                uint32 value;
                struct 
                {
                    uint32 sys1on  : 1;
                    uint32 sys2on  : 1;
                    uint32 sys3on  : 1;
                    uint32 sys4on  : 1;
                    uint32 sys5on  : 1;
                    uint32 sys6on  : 1;
                    uint32 sys7on  : 1;
                    uint32 sys8on  : 1;
                    uint32 sys9on : 1;
                    uint32 sys10on : 1;
                    uint32 sys11on : 1;
                    uint32 sys12on : 1;
                    uint32 sys13on : 1;
                    uint32 sys14on : 1;
                    uint32 sys15on : 1;
                    uint32 sys16on : 1; 
                    uint32         : 16;
                } bit;
            } systat;
            
        private:
          
            uint32 space4_[3];
            
        public:
            
            /**
             * PLL controller divider register 4.
             */      
            Plldiv plldiv4;
          
            /**
             * PLL controller divider register 5.
             */      
            Plldiv plldiv5;
          
            /**
             * PLL controller divider register 6.
             */      
            Plldiv plldiv6;
          
            /**
             * PLL controller divider register 7.
             */      
            Plldiv plldiv7;
          
            /**
             * PLL controller divider register 8.
             */      
            Plldiv plldiv8;
          
            /**
             * PLL controller divider register 9.
             */      
            Plldiv plldiv9;
          
            /**
             * PLL controller divider register 10.
             */      
            Plldiv plldiv10;
          
            /**
             * PLL controller divider register 11.
             */      
            Plldiv plldiv11;
          
            /**
             * PLL controller divider register 12.
             */      
            Plldiv plldiv12;
          
            /**
             * PLL controller divider register 13.
             */      
            Plldiv plldiv13;
          
            /**
             * PLL controller divider register 14.
             */      
            Plldiv plldiv14;
          
            /**
             * PLL controller divider register 15.
             */      
            Plldiv plldiv15;
          
            /**
             * PLL controller divider register 16.
             */      
            Plldiv plldiv16;
      
        };
    }
} 
#endif // MODULE_REG_PLLC_HPP_
