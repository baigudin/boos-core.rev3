/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_INTERRUPT_CONTROLLER_HPP_
#define MODULE_INTERRUPT_CONTROLLER_HPP_

#include "module.InterruptBase.hpp"
#include "module.Processor.hpp"
#include "module.Register.hpp"
#include "module.reg.Pie.hpp"
#include "library.Stack.hpp"

namespace module
{
    class InterruptController : public ::module::InterruptBase
    {
        typedef ::module::InterruptBase            Parent;
        typedef ::library::Stack<int64,Allocator>  Stack;
  
    public:
    
        /**
         * Available interrupt sources.
         */
        enum Source 
        {
            // PIE Group 1 Vectors - MUXed into CPU INT1
            ADC_SEQ1INT          = 0x0000,
            ADC_SEQ2INT          = 0x0010,
            XINT1                = 0x0030,
            XINT2                = 0x0040,
            ADC_ADCINT           = 0x0050,
            CPU_TIMER0_TINT0     = 0x0060,
            LPM_WD_WAKEINT       = 0x0070,
            // PIE Group 2 Vectors - MUXed into CPU INT2
            EPWM1_TZINT          = 0x0001,
            EPWM2_TZINT          = 0x0011,
            EPWM3_TZINT          = 0x0021,
            EPWM4_TZINT          = 0x0031,
            EPWM5_TZINT          = 0x0041,
            EPWM6_TZINT          = 0x0051,
            // PIE Group 3 Vectors - MUXed into CPU INT3
            EPWM1_INT            = 0x0002,
            EPWM2_INT            = 0x0012,
            EPWM3_INT            = 0x0022,
            EPWM4_INT            = 0x0032,
            EPWM5_INT            = 0x0042,
            EPWM6_INT            = 0x0052,     
            // PIE Group 4 Vectors - MUXed into CPU INT4
            ECAP1_INT            = 0x0003,
            ECAP2_INT            = 0x0013,
            ECAP3_INT            = 0x0023,
            ECAP4_INT            = 0x0033,
            ECAP5_INT            = 0x0043,
            ECAP6_INT            = 0x0053,
            // PIE Group 5 Vectors - MUXed into CPU INT5
            EQEP1_INT            = 0x0004,
            EQEP2_INT            = 0x0014,
            // PIE Group 6 Vectors - MUXed into CPU INT6
            SPI_A_SPIRXINTA      = 0x0005,
            SPI_A_SPITXINTA      = 0x0015,
            McBSP_B_MRINTB       = 0x0025,
            McBSP_B_SPI_B_MXINTB = 0x0035,
            McBSP_A_MRINTA       = 0x0045,
            McBSP_A_MXINTA       = 0x0055,
            // PIE Group 7 Vectors - MUXed into CPU INT7
            DMA_CHANNEL1_DINTCH1 = 0x0006, 
            DMA_CHANNEL2_DINTCH2 = 0x0016, 
            DMA_CHANNEL3_DINTCH3 = 0x0026, 
            DMA_CHANNEL4_DINTCH4 = 0x0036, 
            DMA_CHANNEL5_DINTCH5 = 0x0046, 
            DMA_CHANNEL6_DINTCH6 = 0x0056,
            // PIE Group 8 Vectors - MUXed into CPU INT8
            I2C_A_I2CINT1A       = 0x0007,  
            I2C_A_I2CINT2A       = 0x0017,
            SCI_C_SCIRXINTC      = 0x0047,
            SCI_C_SCITXINTC      = 0x0057,
            // PIE Group 9 Vectors - MUXed into CPU INT9
            SCI_A_SCIRXINTA      = 0x0008,
            SCI_A_SCITXINTA      = 0x0018,
            SCI_B_SCIRXINTB      = 0x0028,
            SCI_B_SCITXINTB      = 0x0038,
            ECAN_A_ECAN0INTA     = 0x0048,
            ECAN_A_ECAN1INTA     = 0x0058,
            ECAN_B_ECAN0INTB     = 0x0068,
            ECAN_B_ECAN1INTB     = 0x0078,
            // PIE Group 12 Vectors - Muxed into CPU INT12
            XINT3                = 0x000b,
            XINT4                = 0x001b,
            XINT5                = 0x002b,
            XINT6                = 0x003b,
            XINT7                = 0x004b,
            FPU_LVF              = 0x006b,
            FPU_LUF              = 0x007b,
            // CPU Sources
            GPIO0_INT            = 0x000c,
            GPIO1_INT            = 0x001c,
            GPIO2_INT            = 0x002c,
            GPIO3_INT            = 0x003c,
            GPIO4_INT            = 0x004c,
            GPIO5_INT            = 0x005c,
            GPIO6_INT            = 0x006c,
            GPIO7_INT            = 0x007c,
            GPIO8_INT            = 0x008c,
            GPIO9_INT            = 0x009c,
            GPIO10_INT           = 0x00ac,
            GPIO11_INT           = 0x00bc,
            GPIO12_INT           = 0x00cc,
            GPIO13_INT           = 0x00dc,
            GPIO14_INT           = 0x00ec,
            GPIO15_INT           = 0x00fc,
            GPIO16_INT           = 0x010c,
            GPIO17_INT           = 0x011c,
            GPIO18_INT           = 0x012c,
            GPIO19_INT           = 0x013c,
            GPIO20_INT           = 0x014c,
            GPIO21_INT           = 0x015c,
            GPIO22_INT           = 0x016c,
            GPIO23_INT           = 0x017c,
            GPIO24_INT           = 0x018c,
            GPIO25_INT           = 0x019c,
            GPIO26_INT           = 0x01ac,
            GPIO27_INT           = 0x01bc,
            GPIO28_INT           = 0x01cc,
            GPIO29_INT           = 0x01dc,
            GPIO30_INT           = 0x01ec,
            GPIO31_INT           = 0x01fc,
            CPU_TIMER1_TINT1     = 0x020c,
            CPU_TIMER2_TINT2     = 0x021c
        };
      
        /** 
         * Constructor.
         */    
        InterruptController() : Parent(),
            ctx_ (NULL){
            setConstruct( construct() );
        }
      
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         */     
        InterruptController(::api::Task* handler, int32 source) : Parent(),
            ctx_ (NULL){
            setConstruct( construct(*handler, source) );
        }
      
        /** 
         * Destructor.
         */
        virtual ~InterruptController()
        {
            if(ctx_ != NULL) delete ctx_;
        }
        
        /**
         * Jumps to interrupt hardware vector.
         */      
        virtual void jump()
        {
            if( not isAllocated() ) return;
            jumpLow(0xffffffff);    
        }
        
        /**
         * Clears an interrupt status of this source.
         */     
        virtual void clear()
        {
            if( not isAllocated() ) return;    
            bool is = Interrupt::disableAll();      
            if(ctx_->pie == NULL)
                clearLow(ctx_->maskCpuIer);
            else
                ctx_->pie->ifr.val &= ~ctx_->maskPieIer;
            return Interrupt::enableAll(is);
        }
        
        /**
         * Sets an interrupt status of this source.
         */    
        virtual void set()
        {
            if( not isAllocated() ) return;
            bool is = Interrupt::disableAll();      
            if(ctx_->pie == NULL)
                setLow(ctx_->maskCpuIer);
            else
                ctx_->pie->ifr.val |= ctx_->maskPieIer;
            return Interrupt::enableAll(is);
        }  
        
        /**
         * Locks this interrupt source.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        virtual bool disable()
        {
            if( not isAllocated() ) return false;
            bool res;
            bool is = Interrupt::disableAll();      
            if(ctx_->pie == NULL)
                res = disableLow(ctx_->maskCpuIer);
            else
            {
                res = ctx_->pie->ier.val & ctx_->maskPieIer ? true : false;
                ctx_->pie->ier.val &= ~ctx_->maskPieIer;      
            }
            return Interrupt::enableAll(is, res);
        }
        
        /**
         * Unlocks this interrupt source.
         *
         * @param status returned status by lock method.
         */
        virtual void enable(bool status)
        {
            if( not isAllocated() ) return;
            bool is = Interrupt::disableAll();
            if(ctx_->pie == NULL)
                enableLow(ctx_->maskCpuIer, status);
            else if(status)
                ctx_->pie->ier.val |= ctx_->maskPieIer;
            Interrupt::enableAll(is);      
        }
        
        /**
         * Sets interrupt source handler.
         *
         * @param handler pointer to user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         * @return true if handler is set successfully.
         */      
        virtual bool setHandler(::api::Task& handler, int32 source)
        {
            bool res = false;
            bool is = Interrupt::disableAll();
            do{
                if( not isConstructed_ ) break;
                if( not isSource(source) ) break;
                if( isAllocated() ) break;        
                Source src = static_cast<Source>(source);
                Context* ctx = new Context(handler, src);
                if(ctx == NULL || not ctx->isConstructed()) break;
                ctx_ = ctx;
                table_.ctx[ctx_->grp][ctx_->num] = ctx_;
                res = true;
            }while(false);
            return Interrupt::enableAll(is, res);
        }
      
        /**
         * Removes this interrupt source.
         */        
        virtual void removeHandler()
        {
        }
        
        /**
         * Sets new registers context for storing.
         *
         * @param reg new registers context.
         */
        virtual void setContext(::module::Register& reg)
        {
        }
        
        /**
         * Restores registers context for storing to the default.
         */
        virtual void restoreContext()
        {
        }        
        
        /**
         * Disables all maskable interrupts.
         *
         * @return global interrupts enable bit value before method was called.
         */
        static bool disableAll();
      
        /**
         * Enables all maskable interrupts.
         *
         * @param status the returned status by disable method.
         */
        static void enableAll(bool status);
        
        /**
         * Initialization.
         *
         * @param config the operating system configuration.
         * @return true if no errors.
         */
        static bool initialize(const Configuration& config)
        {
            isInitialized_ = 0;   
            if(config.sourceClock == 0) return false;
            regPie_ = new (reg::Pie::ADDRESS) reg::Pie();
            // Init context table
            for(int32 g=0; g<12; g++)
                for(int32 n=0; n<8; n++)
                    table_.ctx[g][n] = NULL;
            for(int32 n=0; n<32; n++)           
                 table_.ctx[12][n] = NULL;           
            // CPU and PIE vectors table initialization
            uint32* dst = reinterpret_cast<uint32*>(CPU_PIE_ADDR);
            const uint32* src = getVectorsLow();
            Register::allow();
            for(int32 i=0; i<CPU_PIE_VETS; i++) dst[i] = src[i];
            Register::protect();
            // Enable vector fetching from PIE vector table
            regPie_->ctrl.bit.enpie = 1;
            // Set base value
            for(int32 i=0; i<12; i++)
            {
                regPie_->pie[i].ier.val = 0x0000;
                regPie_->pie[i].ifr.val = 0x0000;
            }
            for(int32 i=0; i<16; i++) disableLow(0x1 << i);
            for(int32 i=0; i<16; i++) clearLow(0x1 << i);
            for(int32 i=0; i<12; i++) enableLow(0x1 << i, true);
            isInitialized_ = IS_INITIALIZED;
            return true;
        }
        
        /**
         * Deinitialization.
         */
        static void deinitialize()
        {
            isInitialized_ = 0;
        }    
      
    private:
    
        /** 
         * Constructs the object.
         *
         * @return true if object has been constructed successfully.
         */
        bool construct()
        {
            if(isInitialized_ != IS_INITIALIZED) return false;
            return true;
        }
        
        /** 
         * Constructs the object.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.     
         * @return true if object has been constructed successfully.
         */
        bool construct(::api::Task& handler, int32 source)
        {
            if(isInitialized_ != IS_INITIALIZED) return false;
            return setHandler(handler, source);
        }  
      
        /**
         * Current object has HW interrupt.
         *
         * @return true if object has interrupt source.
         */
        bool isAllocated()
        {
            if( not isConstructed_ ) return false;
            return ctx_ == NULL ? false : true;
        }
        
        /**
         * Tests if given source is available.
         *
         * @param source interrupt source.
         * @return true if the source is available.
         */      
        static bool isSource(int32 source)
        {
            union Src
            {
                Src(){}
                Src(uint32 v){val = v;}          
               ~Src(){}    
               
                uint32 val;
                struct Val
                {
                    uint32 grp : 4;
                    uint32 num : 8;
                    uint32     : 4;          
                } bit;
            } vec = source;
            if(vec.bit.grp > 0xc) return false;
            // CPU interrupt vector 
            if(vec.bit.grp > 0xb)
            {
                // Drop GPIO interrupt sources
                if(vec.bit.num < 0x20) return false;
            }
            // PIE interrupt vector       
            else
            {
                if(vec.bit.num > 7) return false;      
            }
            return true;      
        }
        
        /**
         * HW interrupt handle routing.
         *
         * @param n index of HW interrupt vector
         * @param g index of HW interrupt vectors group
         */  
        static void handler(register int16 n, register int16 g);
        
        /**
         * Returns address of PIE vectors table copy.
         *
         * @return vectors table address.
         */
        static const uint32* getVectorsLow();
        
        /**
         * Locks maskable interrupt source.
         *
         * @param bit a register bit mask.
         * @return an interrupt enable source bit in low bit before method was called.
         */
        static bool disableLow(uint32 bit);
        
        /**
         * Unlocks maskable interrupt source.
         *
         * @param bit a register bit mask.
         * @param is the returned status by disable method.
         */
        static void enableLow(uint32 bit, bool is);
        
        /**
         * Sets a maskable interrupt status.
         *
         * @param bit a register bit mask.
         */    
        static void setLow(uint32 bit);
        
        /**
         * Clears a maskable interrupt status.
         *
         * @param bit a register bit mask.
         */    
        static void clearLow(uint32 bit);
        
        /**
         * Jumps to interrupt HW vector.
         *
         * @param vn hardware interrupt vector number.
         */    
        static void jumpLow(uint32 vn);    
      
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        InterruptController(const InterruptController& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        InterruptController& operator =(const InterruptController& obj);
        
        /**
         * Hi level interrupt context.
         */
        struct Context : public ::Object<>
        {
            typedef ::Object<> Parent;
          
        public:
        
            /**
             * Index of CPU or PIE group
             */
            int32 grp;
           
            /**
             * Index of vector in CPU or PIE group
             */
            int32 num;
            
            /**
             * Interrupt source.
             */
            Source source;
           
            /**
             * This user interrupt handler.
             */
            ::api::Task& handler;
            
            /**
             * ACK bit mask of PIE.
             */
            uint16 maskPieAck;            
            
            /**
             * IER or IFR bit mask of PIE.
             */
            uint16 maskPieIer;
            
            /**
             * IER or IFR bit mask of CPU.
             */
            uint16 maskCpuIer;
           
            /**
             * Mask for IER or IFR bit mask.
             */      
            ::module::reg::Pie::Group* pie;
           
            /**
             * CPU register state of interrupt source handler.
             */
            ::module::Register* reg;
            
            /**
             * Stack of interrupt source handler.
             */         
            ::api::Stack<int64>* stack;        
        
            /** 
             * Constructor.
             *
             * @param handler pointer to user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             */    
            Context(::api::Task& hndl, Source src) : Parent(),
                grp        ((static_cast<int32>(src) & 0x0000000f) >> 0),
                num        ((static_cast<int32>(src) & 0x00000ff0) >> 4),
                source     (src),
                handler    (hndl),
                maskPieAck (0x00000000),
                maskPieIer (0x00000000),
                maskCpuIer (0x00000000),
                pie        (NULL),
                reg        (NULL),
                stack      (NULL){
                setConstruct( construct() );      
            }
            
            /** 
             * Destructor.
             */
            virtual ~Context()
            {
                if(stack != NULL) delete stack;              
                if(reg != NULL) delete reg;
            }
          
        private:
          
            /** 
             * Constructor.
             *
             * @return boolean result.
             */
            bool construct()
            {
                if( not isConstructed() ) return false;
                // Set pointer to group
                ::module::reg::Pie* regPie = new (reg::Pie::ADDRESS) reg::Pie();
                // The source is CPU source
                if(grp == 12)
                {
                    switch(source)
                    {
                        case CPU_TIMER1_TINT1: 
                            num = 12; 
                            break;
                            
                        case CPU_TIMER2_TINT2: 
                            num = 13; 
                            break;
                            
                        default: 
                            return false;
                    }
                    maskPieAck = 0x0;
                    maskPieIer = 0x0;
                    maskCpuIer = 0x1 << num;
                }
                // The source is PIE source
                else
                {
                    pie = &regPie->pie[grp];
                    maskPieAck = 0x1 << grp;
                    maskPieIer = 0x1 << num;
                    maskCpuIer = 0x1 << grp;
                }
                // Create context CPU registers
                reg = ::module::Register::create();
                if(reg == NULL) return false;
                // Create context stack
                stack = new Stack(::module::Processor::getStackType(), handler.getStackSize() >> 2);
                if(stack == NULL || not stack->isConstructed()) return false;
                return true;
            }
      
        };
        
        struct Contexts
        {
        
        public:
        
            /**
             * 11 x 8 PIE contexts and 8 CPU contexts.
             */         
            Context* ctx[13][8];
          
        private:
        
            /**
             * 24 CPU contexts added.
             */
            Context* ctx_[24];
                
        };
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x98753af7;
      
        /**
         * PIE 32-bit vectors number.
         */    
        static const int32 CPU_PIE_VETS = 0x0000080;
      
        /**
         * PIE vectors address.
         */
        static const uint32 CPU_PIE_ADDR = 0x00000d00;
        
        /**
         * Peripheral Interrupt Expansion (no boot).
         */  
        static reg::Pie* regPie_;
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;
        
        /**
         * The interrupt source contexs table (no boot).
         */    
        static Contexts table_;
        
        /**
         * The interrupt source contex.
         */    
        Context* ctx_;
      
    };
    
    /**
     * HW interrupt handle routing.
     *
     * @param n index of HW interrupt vector
     * @param g index of HW interrupt vectors group
     */  
    void InterruptController::handler(int16 n, int16 g)
    {
        Context* ctx = table_.ctx[g][n];
        if(ctx == NULL) return;
        ctx->handler.main();
        regPie_->ack.val |= ctx->maskPieAck;
    }    
    
    /**
     * System Control Registers (no boot).
     */  
    ::module::reg::Pie* InterruptController::regPie_;
  
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 InterruptController::isInitialized_;
    
    /**
     * The interrupt source contexs table (no boot).
     */
    InterruptController::Contexts InterruptController::table_;  
  
}
#endif // MODULE_INTERRUPT_CONTROLLER_HPP_
