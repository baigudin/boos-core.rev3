/**
 * TI TMS320F2833x Analog-to-Digital Converter registers.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_REG_ADC_HPP_
#define MODULE_REG_ADC_HPP_

#include "Types.hpp"

namespace module
{
    namespace reg
    {
        /**
         * Analog-to-Digital Converter registers.
         */
        struct Adc
        {
        
        public:
          
            /**
             * Default configuration addresses.
             */
            static const uint32 ADDRESS = 0x00007100;
            
            /** 
             * Constructor.
             */  
            Adc() :
                adctrl1    (),
                adctrl2    (),
                adcmaxconv (),
                adcaseqsr  (),
                adctrl3    (),
                adcst      (),
                adcrefsel  (),
                adcofftrim (){
            }
            
            /** 
             * Destructor.
             */    
           ~Adc(){}    
            
            /**
             * Operator new.
             *
             * @param size unused.
             * @param ptr  address of memory.
             * @return address of memory.
             */     
            void* operator new(size_t, uint32 ptr)
            {
                return reinterpret_cast<void*>(ptr);
            }
            
            /**
             * ADC Control Register 1.
             */
            union Adctrl1
            {
                Adctrl1(){}
                Adctrl1(uint16 v){val = v;}          
               ~Adctrl1(){}    
               
                uint16 val;
                struct Val
                {
                    uint16          : 4;
                    uint16 seqCasc  : 1;
                    uint16 seqOvrd  : 1;
                    uint16 contRun  : 1;
                    uint16 cps      : 1;
                    uint16 acqPs    : 4;
                    uint16 susmod   : 2;
                    uint16 reset    : 1;
                    uint16          : 1;
                } bit;
            } adctrl1;  
          
            /**
             * ADC Control Register 2.
             */
            union Adctrl2
            {
                Adctrl2(){}
                Adctrl2(uint16 v){val = v;}          
               ~Adctrl2(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 ePwmSocbSeq2 : 1;
                    uint16              : 1;
                    uint16 intModSeq2   : 1;
                    uint16 intEnaSeq2   : 1;
                    uint16              : 1;
                    uint16 socSeq2      : 1;
                    uint16 rstSeq2      : 1;
                    uint16 extSocSeq1   : 1;
                    uint16 epwmSocaSeq1 : 1;
                    uint16              : 1;
                    uint16 intModSeq1   : 1;
                    uint16 intEnaSeq1   : 1;
                    uint16              : 1;
                    uint16 socSeq1      : 1;
                    uint16 rstSeq1      : 1;
                    uint16 epwmSocbSeq  : 1;
                } bit;
            } adctrl2;
          
            /**
             * ADC Maximum Conversion Channels Register.
             */
            union Adcmaxconv
            {
                Adcmaxconv(){}
                Adcmaxconv(uint16 v){val = v;}          
               ~Adcmaxconv(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 maxConv1 : 4;
                    uint16 maxConv2 : 3;
                    uint16          : 9;
                } bit;
            } adcmaxconv;
          
            /**
             * ADC Channel Select Sequencing Control Register 1-4.
             */
            union Adcchselseq
            {
                Adcchselseq(){}
                Adcchselseq(uint16 v){val = v;}          
               ~Adcchselseq(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 conv0 : 4;
                    uint16 conv1 : 4; 
                    uint16 conv2 : 4;
                    uint16 conv3 : 4; 
                } bit;
            } adcchselseq[4];
          
            /**
             * ADC Auto-Sequence Status Register.
             */
            union Adcaseqsr
            {
                Adcaseqsr(){}
                Adcaseqsr(uint16 v){val = v;}          
               ~Adcaseqsr(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 seq1State : 4;
                    uint16 seq2State : 3;
                    uint16           : 1;
                    uint16 seqCntr   : 4;
                    uint16           : 4;
                } bit;
            } adcaseqsr;
          
            /**
             * ADC Conversion Result Buffer Register 0-15.
             */
            union Adcresult
            {
                Adcresult(){}
                Adcresult(uint16 v){val = v;}          
               ~Adcresult(){}    
               
                uint16 val;
                struct Val
                {
                    uint16     : 4;
                    uint16 d0  : 1;
                    uint16 d1  : 1;
                    uint16 d2  : 1;
                    uint16 d3  : 1;
                    uint16 d4  : 1;
                    uint16 d5  : 1;
                    uint16 d6  : 1;
                    uint16 d7  : 1;
                    uint16 d8  : 1;
                    uint16 d9  : 1;
                    uint16 d10 : 1;
                    uint16 d11 : 1;
                } bit;
            } adcresult[16];
          
            /**
             * ADC Control Register 3.
             */
            union Adctrl3
            {
                Adctrl3(){}
                Adctrl3(uint16 v){val = v;}          
               ~Adctrl3(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 smodeSel  : 1;
                    uint16 adcclkps  : 4;
                    uint16 adcpwdn   : 1;
                    uint16 adcbgrfdn : 2;
                    uint16           : 8;
                } bit;
            } adctrl3;
          
            /**
             * ADC Status and Flag Register.
             */
            union Adcst
            {
                Adcst(){}
                Adcst(uint16 v){val = v;}          
               ~Adcst(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 intSeq1      : 1;
                    uint16 intSeq2      : 1;
                    uint16 seq1Bsy      : 1;
                    uint16 seq2Bsy      : 1;
                    uint16 intSeq1Clr   : 1;
                    uint16 intSeq2Clr   : 1;
                    uint16 eosBuf1      : 1;
                    uint16 eosBuf2      : 1;
                    uint16              : 8;
                } bit;
            } adcst;
          
          
        private:
          
            uint16 space0_[2];
            
        public:
          
            /**
             * ADC Reference Select Register.
             */
            union Adcrefsel
            {
                Adcrefsel(){}
                Adcrefsel(uint16 v){val = v;}          
               ~Adcrefsel(){}    
               
                uint16 val;
                struct Val
                {
                    uint16        : 14;
                    uint16 refSel : 2;
                } bit;
            } adcrefsel;
          
            /**
             * ADC Offset Trim Register.
             */
            union Adcofftrim
            {
                Adcofftrim(){}
                Adcofftrim(uint16 v){val = v;}          
               ~Adcofftrim(){}    
               
                uint16 val;
                struct Val
                {
                    uint16 offsetTrim : 8;    
                    uint16            : 8;
                } bit;
            } adcofftrim;
          
        private:        
          
            uint16 space1_[2];
            
        public:
          
        };
          
        /**
         * Analog-to-Digital Converter registers for DMA and CPU fast access.
         */
        struct AdcDma
        {
          
        public:
            
            /**
             * Remapped configuration addresses.
             */
            static const uint32 ADDRESS = 0x00000B00;
            
            /** 
             * Constructor.
             */  
            AdcDma(){}
            
            /** 
             * Destructor.
             */    
           ~AdcDma(){}    
            
            /**
             * Operator new.
             *
             * @param size unused.
             * @param ptr  address of memory.
             * @return address of memory.
             */     
            void* operator new(size_t, uint32 ptr)
            {
                return reinterpret_cast<void*>(ptr);
            }
          
            /**
             * ADC Conversion Result Buffer Register 0-15.
             */
            union Adcresult
            {
                Adcresult(){}
                Adcresult(uint16 v){val = v;}          
               ~Adcresult(){}    
               
                uint16 val;
                struct Val
                {
                    uint16     : 4;
                    uint16 d0  : 1;
                    uint16 d1  : 1;
                    uint16 d2  : 1;
                    uint16 d3  : 1;
                    uint16 d4  : 1;
                    uint16 d5  : 1;
                    uint16 d6  : 1;
                    uint16 d7  : 1;
                    uint16 d8  : 1;
                    uint16 d9  : 1;
                    uint16 d10 : 1;
                    uint16 d11 : 1;
                } bit;
            } adcresult[16];
        
        };
    }
}
#endif // MODULE_REG_ADC_HPP_
