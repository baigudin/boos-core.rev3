/**
 * TI TMS320C64x+ Interrupt selector registers.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REG_INTC_HPP_
#define MODULE_REG_INTC_HPP_

#include "Types.hpp"

namespace module
{
    namespace reg
    {
        struct Intc
        {
        
        public:
          
            /**
             * Memory mapped address.
             */
            static const uint32 ADDRESS = 0x01800000;     
            
            /**
             * Number of interrupt controller event groups.
             */
            static const int32 EVENT_GROUPS = 4;
          
            /** 
             * Constructor.
             */  
            Intc() :
                intxstat (),
                intxclr  (),
                intdmask (){
            }
          
            /** 
             * Destructor.
             */    
           ~Intc(){}    
           
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
             * Event Flag Registers 0-3.
             */
            union Evtflag
            {
                Evtflag(){}
                Evtflag(uint32 v){value = v;}
               ~Evtflag(){}    
              
                uint32 value;
                struct 
                {
                    uint32 ef0  : 1;
                    uint32 ef1  : 1;
                    uint32 ef2  : 1;
                    uint32 ef3  : 1;
                    uint32 ef4  : 1;
                    uint32 ef5  : 1;
                    uint32 ef6  : 1;
                    uint32 ef7  : 1;          
                    uint32 ef8  : 1;
                    uint32 ef9  : 1;
                    uint32 ef10 : 1;
                    uint32 ef11 : 1;
                    uint32 ef12 : 1;
                    uint32 ef13 : 1;
                    uint32 ef14 : 1;
                    uint32 ef15 : 1;
                    uint32 ef16 : 1;
                    uint32 ef17 : 1;
                    uint32 ef18 : 1;
                    uint32 ef19 : 1;
                    uint32 ef20 : 1;
                    uint32 ef21 : 1;
                    uint32 ef22 : 1;
                    uint32 ef23 : 1;
                    uint32 ef24 : 1;
                    uint32 ef25 : 1;
                    uint32 ef26 : 1;
                    uint32 ef27 : 1;
                    uint32 ef28 : 1;
                    uint32 ef29 : 1;
                    uint32 ef30 : 1;
                    uint32 ef31 : 1;          
                } bit;
            };
            
            /**
             * Event Set Registers 0-3.
             */
            union Evtset
            {
                Evtset(){}
                Evtset(uint32 v){value = v;}
               ~Evtset(){}    
              
                uint32 value;
                struct 
                {
                    uint32 es0  : 1;
                    uint32 es1  : 1;
                    uint32 es2  : 1;
                    uint32 es3  : 1;
                    uint32 es4  : 1;
                    uint32 es5  : 1;
                    uint32 es6  : 1;
                    uint32 es7  : 1;          
                    uint32 es8  : 1;
                    uint32 es9  : 1;
                    uint32 es10 : 1;
                    uint32 es11 : 1;
                    uint32 es12 : 1;
                    uint32 es13 : 1;
                    uint32 es14 : 1;
                    uint32 es15 : 1;
                    uint32 es16 : 1;
                    uint32 es17 : 1;
                    uint32 es18 : 1;
                    uint32 es19 : 1;
                    uint32 es20 : 1;
                    uint32 es21 : 1;
                    uint32 es22 : 1;
                    uint32 es23 : 1;
                    uint32 es24 : 1;
                    uint32 es25 : 1;
                    uint32 es26 : 1;
                    uint32 es27 : 1;
                    uint32 es28 : 1;
                    uint32 es29 : 1;
                    uint32 es30 : 1;
                    uint32 es31 : 1;          
                } bit;
            };
            
            /**
             * Event Clear Registers 0-3.
             */
            union Evtclr
            {
                Evtclr(){}
                Evtclr(uint32 v){value = v;}
               ~Evtclr(){}    
              
                uint32 value;
                struct 
                {
                    uint32 ec0  : 1;
                    uint32 ec1  : 1;
                    uint32 ec2  : 1;
                    uint32 ec3  : 1;
                    uint32 ec4  : 1;
                    uint32 ec5  : 1;
                    uint32 ec6  : 1;
                    uint32 ec7  : 1;          
                    uint32 ec8  : 1;
                    uint32 ec9  : 1;
                    uint32 ec10 : 1;
                    uint32 ec11 : 1;
                    uint32 ec12 : 1;
                    uint32 ec13 : 1;
                    uint32 ec14 : 1;
                    uint32 ec15 : 1;
                    uint32 ec16 : 1;
                    uint32 ec17 : 1;
                    uint32 ec18 : 1;
                    uint32 ec19 : 1;
                    uint32 ec20 : 1;
                    uint32 ec21 : 1;
                    uint32 ec22 : 1;
                    uint32 ec23 : 1;
                    uint32 ec24 : 1;
                    uint32 ec25 : 1;
                    uint32 ec26 : 1;
                    uint32 ec27 : 1;
                    uint32 ec28 : 1;
                    uint32 ec29 : 1;
                    uint32 ec30 : 1;
                    uint32 ec31 : 1;          
                } bit;
            };
          
            /**
             * Event Mask Registers 0-3.
             */
            union Evtmask
            {
                Evtmask(){}
                Evtmask(uint32 v){value = v;}
               ~Evtmask(){}    
              
                uint32 value;
                struct 
                {
                    uint32 em0  : 1;
                    uint32 em1  : 1;
                    uint32 em2  : 1;
                    uint32 em3  : 1;
                    uint32 em4  : 1;
                    uint32 em5  : 1;
                    uint32 em6  : 1;
                    uint32 em7  : 1;          
                    uint32 em8  : 1;
                    uint32 em9  : 1;
                    uint32 em10 : 1;
                    uint32 em11 : 1;
                    uint32 em12 : 1;
                    uint32 em13 : 1;
                    uint32 em14 : 1;
                    uint32 em15 : 1;
                    uint32 em16 : 1;
                    uint32 em17 : 1;
                    uint32 em18 : 1;
                    uint32 em19 : 1;
                    uint32 em20 : 1;
                    uint32 em21 : 1;
                    uint32 em22 : 1;
                    uint32 em23 : 1;
                    uint32 em24 : 1;
                    uint32 em25 : 1;
                    uint32 em26 : 1;
                    uint32 em27 : 1;
                    uint32 em28 : 1;
                    uint32 em29 : 1;
                    uint32 em30 : 1;
                    uint32 em31 : 1;          
                } bit;
            };
          
            /**
             * Masked Event Flag Registers 0-3.
             */
            union Mevtflag
            {
                Mevtflag(){}
                Mevtflag(uint32 v){value = v;}
               ~Mevtflag(){}    
              
                uint32 value;
                struct 
                {
                    uint32 mef0  : 1;
                    uint32 mef1  : 1;
                    uint32 mef2  : 1;
                    uint32 mef3  : 1;
                    uint32 mef4  : 1;
                    uint32 mef5  : 1;
                    uint32 mef6  : 1;
                    uint32 mef7  : 1;
                    uint32 mef8  : 1;
                    uint32 mef9  : 1;
                    uint32 mef10 : 1;
                    uint32 mef11 : 1;
                    uint32 mef12 : 1;
                    uint32 mef13 : 1;
                    uint32 mef14 : 1;
                    uint32 mef15 : 1;
                    uint32 mef16 : 1;
                    uint32 mef17 : 1;
                    uint32 mef18 : 1;
                    uint32 mef19 : 1;
                    uint32 mef20 : 1;
                    uint32 mef21 : 1;
                    uint32 mef22 : 1;
                    uint32 mef23 : 1;
                    uint32 mef24 : 1;
                    uint32 mef25 : 1;
                    uint32 mef26 : 1;
                    uint32 mef27 : 1;
                    uint32 mef28 : 1;
                    uint32 mef29 : 1;
                    uint32 mef30 : 1;
                    uint32 mef31 : 1;
                } bit;
            }; 
          
            /**
             * Interrupt Mux Registers 1-3.
             */
            union Intmux
            {
                Intmux(){}
                Intmux(uint32 v){value = v;}
               ~Intmux(){}    
              
                uint32 value;
                struct 
                {
                    uint32 intsel0 : 7;
                    uint32         : 1;
                    uint32 intsel1 : 7;
                    uint32         : 1;
                    uint32 intsel2 : 7;
                    uint32         : 1;
                    uint32 intsel3 : 7;
                    uint32         : 1;
                } bit;
            };       
            
            /**
             * Advanced Event Generator Mux Register 0-1.
             */
            union Aegmux
            {
                Aegmux(){}
                Aegmux(uint32 v){value = v;}
               ~Aegmux(){}    
              
                uint32 value;
                struct 
                {
                    uint32 aegsel0 : 8;
                    uint32 aegsel1 : 8;
                    uint32 aegsel2 : 8;
                    uint32 aegsel3 : 8;
                } bit;
            };
          
            /**
             * CPU Exception Combiner Mask Registers 0-3.
             */
            union Expmask
            {
                Expmask(){}
                Expmask(uint32 v){value = v;}
               ~Expmask(){}    
              
                uint32 value;
                struct 
                {
                    uint32 xm0  : 1;
                    uint32 xm1  : 1;
                    uint32 xm2  : 1;
                    uint32 xm3  : 1;
                    uint32 xm4  : 1;
                    uint32 xm5  : 1;
                    uint32 xm6  : 1;
                    uint32 xm7  : 1;
                    uint32 xm8  : 1;
                    uint32 xm9  : 1;
                    uint32 xm10 : 1;
                    uint32 xm11 : 1;
                    uint32 xm12 : 1;
                    uint32 xm13 : 1;
                    uint32 xm14 : 1;
                    uint32 xm15 : 1;
                    uint32 xm16 : 1;
                    uint32 xm17 : 1;
                    uint32 xm18 : 1;
                    uint32 xm19 : 1;
                    uint32 xm20 : 1;
                    uint32 xm21 : 1;
                    uint32 xm22 : 1;
                    uint32 xm23 : 1;
                    uint32 xm24 : 1;
                    uint32 xm25 : 1;
                    uint32 xm26 : 1;
                    uint32 xm27 : 1;
                    uint32 xm28 : 1;
                    uint32 xm29 : 1;
                    uint32 xm30 : 1;
                    uint32 xm31 : 1;
                } bit;
            }; 
          
            /**
             * Masked Exception Flag Registers 0-3.
             */
            union Mexpflag
            {
                Mexpflag(){}
                Mexpflag(uint32 v){value = v;}
               ~Mexpflag(){}    
              
                uint32 value;
                struct 
                {
                    uint32 mxf0  : 1;
                    uint32 mxf1  : 1;
                    uint32 mxf2  : 1;
                    uint32 mxf3  : 1;
                    uint32 mxf4  : 1;
                    uint32 mxf5  : 1;
                    uint32 mxf6  : 1;
                    uint32 mxf7  : 1;
                    uint32 mxf8  : 1;
                    uint32 mxf9  : 1;
                    uint32 mxf10 : 1;
                    uint32 mxf11 : 1;
                    uint32 mxf12 : 1;
                    uint32 mxf13 : 1;
                    uint32 mxf14 : 1;
                    uint32 mxf15 : 1;
                    uint32 mxf16 : 1;
                    uint32 mxf17 : 1;
                    uint32 mxf18 : 1;
                    uint32 mxf19 : 1;
                    uint32 mxf20 : 1;
                    uint32 mxf21 : 1;
                    uint32 mxf22 : 1;
                    uint32 mxf23 : 1;
                    uint32 mxf24 : 1;
                    uint32 mxf25 : 1;
                    uint32 mxf26 : 1;
                    uint32 mxf27 : 1;
                    uint32 mxf28 : 1;
                    uint32 mxf29 : 1;
                    uint32 mxf30 : 1;
                    uint32 mxf31 : 1;
                } bit;
            };
            
            /**
             * Event Flag Registers 0-3.
             */
            Evtflag evtflag[EVENT_GROUPS];
            
        private:
          
            uint32 space0_[0x4];
            
        public:
            
            /**
             * Event Set Registers 0-3.
             */
            Evtset evtset[EVENT_GROUPS];
            
        private:
          
            uint32 space1_[0x4];
            
        public:      
            
            /**
             * Event Clear Registers 0-3.
             */
            Evtclr evtclr[EVENT_GROUPS];
            
        private:
          
            uint32 space2_[0xC];
            
        public:      
          
            /**
             * Event Mask Registers 0-3.
             */
            Evtmask evtmask[EVENT_GROUPS];
            
        private:
          
            uint32 space3_[0x4];
            
        public:
          
            /**
             * Masked Event Flag Registers 0-3.
             */
            Mevtflag mevtflag[EVENT_GROUPS];
            
        private:
          
            uint32 space4_[0x4];
            
        public:      
            
            /**
             * CPU Exception Combiner Mask Registers 0-3.
             */
            Expmask expmask[EVENT_GROUPS];
            
        private:
          
            uint32 space5_[0x4];
            
        public:      
          
            /**
             * Masked Exception Flag Registers 0-3.
             */
            Mexpflag mexpflag[EVENT_GROUPS];
            
        private:
          
            uint32 space6_[0x4];
            
        public:      
          
            /**
             * Interrupt Mux Registers 1-3.
             *
             * NOTE: The zero indexed element is not used, 
             * as it replaces at no register HW area.
             */
            Intmux intmux[4];
            
        private:
          
            uint32 space7_[0xC];
            
        public:
                 
            /**
             * Advanced Event Generator Mux Register 0-1.
             */
            Aegmux aegmux[2];
            
        private:
          
            uint32 space8_[0xE];
            
        public:
            
            /**
             * Interrupt exception status register.
             */
            union Intxstat
            {
                Intxstat(){}
                Intxstat(uint32 v){value = v;}
               ~Intxstat(){}    
              
                uint32 value;
                struct 
                {
                    uint32 drop   : 1;
                    uint32        : 15;
                    uint32 cpuint : 8;
                    uint32 sysint : 8;
                } bit;
            } intxstat;
            
            /**
             * Interrupt exception clear register.
             */
            union Intxclr
            {
                Intxclr(){}
                Intxclr(uint32 v){value = v;}
               ~Intxclr(){}    
              
                uint32 value;
                struct 
                {
                    uint32 clear : 16;
                    uint32       : 16;
                } bit;
            } intxclr;
          
            /**
             * Dropped interrupt mask register.
             */
            union Intdmask
            {
                Intdmask(){}
                Intdmask(uint32 v){value = v;}
               ~Intdmask(){}    
              
                uint32 value;
                struct 
                {
                    uint32       : 4;
                    uint32 idm4  : 1;
                    uint32 idm5  : 1;
                    uint32 idm6  : 1;
                    uint32 idm7  : 1;
                    uint32 idm8  : 1;
                    uint32 idm9  : 1;
                    uint32 idm10 : 1;
                    uint32 idm11 : 1;
                    uint32 idm12 : 1;
                    uint32 idm13 : 1;
                    uint32 idm14 : 1;
                    uint32 idm15 : 1;          
                    uint32       : 16;
                } bit;
            } intdmask;
      
        };
    }
}
#endif // MODULE_REG_INTC_HPP_

