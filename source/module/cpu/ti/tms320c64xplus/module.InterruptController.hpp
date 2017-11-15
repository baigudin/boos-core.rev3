/** 
 * Hardware interrupt controller.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_INTERRUPT_CONTROLLER_HPP_
#define MODULE_INTERRUPT_CONTROLLER_HPP_

#include "Object.hpp"
#include "api.ProcessorInterrupt.hpp"
#include "module.Processor.hpp"
#include "module.Registers.hpp"
#include "module.reg.Intc.hpp"
#include "library.Stack.hpp"
#include "library.Buffer.hpp"

namespace module
{
    class InterruptController : public ::Object<>, public ::api::ProcessorInterrupt
    {
        typedef ::Object<>                          Parent;  
        typedef ::library::Stack<int64, Allocator>  Stack;
  
    public:
    
        /**
         * Available interrupt sources.
         */
        enum Source 
        {
            EVT0            = 0,   // Output of event combiner 0 in interrupt controller, for events 1 - 31.
            EVT1            = 1,   // Output of event combiner 1 in interrupt controller, for events 32 - 63.
            EVT2            = 2,   // Output of event combiner 2 in interrupt controller, for events 64 - 95.
            EVT3            = 3,   // Output of event combiner 3 in interrupt controller, for events 96 - 127.
            EMU_DTDMA       = 9,   // EMU interrupt for: Host scan access; DTDMA transfer complete; AET interrupt
            EMU_RTDXRX      = 11,  // EMU real-time data exchange (RTDX) receive complete
            EMU_RTDXTX      = 12,  // EMU RTDX transmit complete
            IDMA0           = 13,  // IDMA channel 0 interrupt
            IDMA1           = 14,  // IDMA channel 1 interrupt
            DSPINT          = 15,  // HPI-to-DSP interrupt
            I2CINT          = 16,  // I2C interrupt
            MACINT          = 17,  // Ethernet MAC interrupt
            AEASYNCERR      = 18,  // EMIFA error interrupt
            INTDST0         = 20,  // RapidIO interrupt 0
            INTDST1         = 21,  // RapidIO interrupt 1
            INTDST2         = 22,  // RapidIO interrupt 2
            INTDST3         = 23,  // RapidIO interrupt 3
            EDMA3CC_GINT    = 24,  // EDMA3 channel global completion interrupt
            MACRXINT        = 25,  // Ethernet MAC receive interrupt
            MACTXINT        = 26,  // Ethernet MAC transmit interrupt
            MACTHRESH       = 27,  // Ethernet MAC receive threshold interrupt
            INTDST4         = 28,  // RapidIO interrupt 4
            INTDST5         = 29,  // RapidIO interrupt 5
            INTDST6         = 30,  // RapidIO interrupt 6
            VCP2_INT        = 32,  // VCP2 error interrupt
            TCP2A_INT       = 33,  // TCP2_A error interrupt
            TCP2B_INT       = 34,  // TCP2_B error interrupt
            UINT            = 36,  // UTOPIA interrupt
            RINT0           = 40,  // McBSP0 receive interrupt
            XINT0           = 41,  // McBSP0 transmit interrupt
            RINT1           = 42,  // McBSP1 receive interrupt
            XINT1           = 43,  // McBSP1 transmit interrupt
            GPINT0          = 51,  // GPIO interrupt
            GPINT1          = 52,  // GPIO interrupt
            GPINT2          = 53,  // GPIO interrupt
            GPINT3          = 54,  // GPIO interrupt
            GPINT4          = 55,  // GPIO interrupt
            GPINT5          = 56,  // GPIO interrupt
            GPINT6          = 57,  // GPIO interrupt
            GPINT7          = 58,  // GPIO interrupt
            GPINT8          = 59,  // GPIO interrupt
            GPINT9          = 60,  // GPIO interrupt
            GPINT10         = 61,  // GPIO interrupt
            GPINT11         = 62,  // GPIO interrupt
            GPINT12         = 63,  // GPIO interrupt
            GPINT13         = 64,  // GPIO interrupt
            GPINT14         = 65,  // GPIO interrupt
            GPINT15         = 66,  // GPIO interrupt
            TINTLO0         = 67,  // Timer 0 lower counter interrupt
            TINTHI0         = 68,  // Timer 0 higher counter interrupt
            TINTLO1         = 69,  // Timer 1 lower counter interrupt
            TINTHI1         = 70,  // Timer 1 higher counter interrupt
            EDMA3CC_INT0    = 71,  // EDMA3CC completion interrupt - Mask0
            EDMA3CC_INT1    = 72,  // EDMA3CC completion interrupt - Mask1
            EDMA3CC_INT2    = 73,  // EDMA3CC completion interrupt - Mask2
            EDMA3CC_INT3    = 74,  // EDMA3CC completion interrupt - Mask3
            EDMA3CC_INT4    = 75,  // EDMA3CC completion interrupt - Mask4
            EDMA3CC_INT5    = 76,  // EDMA3CC completion interrupt - Mask5
            EDMA3CC_INT6    = 77,  // EDMA3CC completion interrupt - Mask6
            EDMA3CC_INT7    = 78,  // EDMA3CC completion interrupt - Mask7
            EDMA3CC_ERRINT  = 79,  // EDMA3CC error interrupt
            EDMA3TC0_ERRINT = 81,  // EDMA3TC0 error interrupt
            EDMA3TC1_ERRINT = 82,  // EDMA3TC1 error interrupt
            EDMA3TC2_ERRINT = 83,  // EDMA3TC2 error interrupt
            EDMA3TC3_ERRINT = 84,  // EDMA3TC3 error interrupt
            EDMA3CC_AET     = 85,  // EDMA3CC AET Event
            EDMA3TC4_ERRINT = 86,  // EDMA3TC4 error interrupt
            EDMA3TC5_ERRINT = 87,  // EDMA3TC5 error interrupt
            ETBOVFLINT      = 94,  // Overflow condition occurred in ETB
            ETBUNFLINT      = 95,  // Underflow condition occurred in ETB
            INTERR          = 96,  // Interrupt Controller dropped CPU interrupt event
            EMC_IDMAERR     = 97,  // EMC invalid IDMA parameters
            EFIINTA         = 100, // EFI interrupt from side A
            EFIINTB         = 101, // EFI interrupt from side B
            L1P_ED1         = 113, // L1P single bit error detected during DMA read
            L2_ED1          = 116, // L2 single bit error detected
            L2_ED2          = 117, // L2 two bit error detected
            PDC_INT         = 118, // Powerdown sleep interrupt
            SYS_CMPA        = 119, // CPU memory protection fault
            L1P_CMPA        = 120, // L1P CPU memory protection fault
            L1P_DMPA        = 121, // L1P DMA memory protection fault
            L1D_CMPA        = 122, // L1D CPU memory protection fault
            L1D_DMPA        = 123, // L1D DMA memory protection fault
            L2_CMPA         = 124, // L2 CPU memory protection fault
            L2_DMPA         = 125, // L2 DMA memory protection fault
            IDMA_CMPA       = 126, // IDMA CPU memory protection fault
            IDMA_BUSERR     = 127, // IDMA bus error interrupt
            UNDEF           = -1
        };  
      
        /** 
         * Constructor.
         */    
        InterruptController() : Parent(),
            isConstructed_ (getConstruct()),
            index_         (-1),
            ctx_           (){
            setConstruct( construct() );
        } 
      
        /** 
         * Constructor.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         */     
        InterruptController(::api::Task* handler, int32 source) : Parent(),
            isConstructed_ (getConstruct()),
            index_         (-1),
            ctx_           (){
            setConstruct( construct(*handler, source) );
        }
        
        /** 
         * Destructor.
         */
        virtual ~InterruptController()
        {
            removeHandler();    
        }
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }           
        
        /**
         * Jumps to interrupt hardware vector.
         */      
        virtual void jump()
        {
            if( not isAllocated() ) return;
            jumpLow(ctx_.hi->number);    
        }
        
        /**
         * Clears an interrupt status of this source.
         */     
        virtual void clear()
        {
            if( not isAllocated() ) return;    
            clearLow(ctx_.hi->number);    
        }
        
        /**
         * Sets an interrupt status of this source.
         */    
        virtual void set()
        {
            if( not isAllocated() ) return;
            setLow(ctx_.hi->number);    
        }  
        
        /**
         * Locks this interrupt source.
         *
         * @return an interrupt enable source bit value before method was called.
         */    
        virtual bool disable()
        {
            if( not isAllocated() ) return false;
            return disableLow(ctx_.hi->number);
        }
        
        /**
         * Unlocks this interrupt source.
         *
         * @param status returned status by lock method.
         */
        virtual void enable(bool status)
        {
            if( not isAllocated() ) return;    
            enableLow(ctx_.hi->number, status);    
        }
       
        /**
         * Sets interrupt source handler.
         *
         * @param handler user class which implements an interrupt handler interface.
         * @param source  available interrupt source.
         * @return true if handler is set successfully.
         */      
        virtual bool setHandler(::api::Task& handler, int32 source)
        {
            if( not isConstructed_ ) return false;
            if( isAllocated() )  return false;
            Source src = static_cast<Source>(source);
            int32 index = contexts_->allocate(handler, src);
            if(index == -1) return false;
            ctx_.hi = &contexts_->getHi(index);
            ctx_.lo = &contexts_->getLo(index);
            setMux();
            index_ = index;
            return true;
        }
      
        /**
         * Removes this interrupt source.
         */        
        virtual void removeHandler()
        {
            if( not isAllocated() ) return;  
            disable();
            clear();
            resetMux();
            contexts_->free(index_);
        }
        
        /**
         * Sets new registers context for store.
         *
         * @param reg pointer to new registers context.
         */
        virtual void setContext(::api::ProcessorRegisters& reg)
        {
            if( not isAllocated() ) return;
            ctx_.lo->reg = reg.getRegisters();
        }

        /**
         * Restores registers context for storing to the default.
         */
        virtual void restoreContext()
        {
            if( not isAllocated() ) return;
            ctx_.lo->reg = ctx_.hi->reg->getRegisters();    
        }        
      
        /**
         * Initialization.
         *
         * @param config the operating system configuration.
         * @return true if no errors.
         */
        static bool initialize(const ::Configuration& config)
        {
            isInitialized_ = 0; 
            regInt_ = 0;
            contexts_ = NULL;
            contextHi_ = NULL;
            if(config.cpuClock <= 0) return false;      
            regInt_ = new (reg::Intc::ADDRESS) reg::Intc();
            contexts_ = new Contexts();
            if( contexts_ == NULL || not contexts_->isConstructed() ) return false;
            contextHi_ = &contexts_->getHi(0);
            initLow();
            // Set base value of registers
            for(int32 i=1; i<4; i++)
            {
                // Clear all mux registers      
                regInt_->intmux[i].value = 0;      
            }      
            isInitialized_ = IS_INITIALIZED; 
            return true;
        }
        
        /**
         * Deinitialization.
         */
        static void deinitialize()
        {
            delete contexts_;
            regInt_ = NULL;
            contexts_ = NULL;      
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
            return index_ == -1 ? false : true;
        }
        
        /**
         * Resets MUX register.
         *
         * @param vn hardware interrupt vector number.
         */    
        void resetMux()
        {
            setMuxRegister(0, ctx_.hi->number);    
        }    
        
        /**
         * Sets MUX register.
         *
         * @param source available interrupt source.
         * @param vn     hardware interrupt vector number.
         */    
        void setMux()
        {
            setMuxRegister(ctx_.hi->source, ctx_.hi->number);
        }
        
        /**
         * Sets MUX register.
         *
         * @param source available interrupt source.
         * @param vn     hardware interrupt vector number.
         */    
        static void setMuxRegister(int32 source, int32 vn)
        {
            if(vn < 4 || vn > 16) return;
            int32 i = vn >> 2;
            int32 p = vn & 0x3;
            // Do reading a current register value, modify the value, and store it back. 
            // This sequence is required only because TI has not corrected a bug yet with 
            // the internal data bus of the interrupt controller. The bug cause that 
            // during accessing to bit field of a register, STB instruction is used 
            // and rewrites entire register.
            reg::Intc::Intmux* reg = &regInt_->intmux[i];
            reg::Intc::Intmux temp = 0;
            temp.value = reg->value;
            switch(p)
            {
                case 0: 
                    temp.bit.intsel0 = source & 0x7f; 
                    break;
                    
                case 1: 
                    temp.bit.intsel1 = source & 0x7f; 
                    break;
                    
                case 2: 
                    temp.bit.intsel2 = source & 0x7f; 
                    break;
                    
                case 3: 
                    temp.bit.intsel3 = source & 0x7f; 
                    break;
                    
                default: 
                    break;
            }
            reg->value = temp.value;
        }    
        
        /**
         * HW interrupt handle routing.
         *
         * @param index index of HW interrupt vector number in contexts table
         */  
        static void handler(register int32 index);
      
        /**
         * Locks maskable interrupt source.
         *
         * @param vn hardware interrupt vector number.
         * @return an interrupt enable source bit in low bit before method was called.
         */
        static bool disableLow(uint32 vn);
        
        /**
         * Unlocks maskable interrupt source.
         *
         * @param vn hardware interrupt vector number.
         * @param is the returned status by disable method.
         */
        static void enableLow(uint32 vn, bool is);
        
        /**
         * Sets a maskable interrupt status.
         *
         * @param vn hardware interrupt vector number.
         */    
        static void setLow(uint32 vn);
        
        /**
         * Clears a maskable interrupt status.
         *
         * @param vn hardware interrupt vector number.
         */    
        static void clearLow(uint32 vn);
        
        /**
         * Jumps to interrupt HW vector.
         *
         * @param vn hardware interrupt vector number.
         */    
        static void jumpLow(uint32 vn);
        
        /**
         * Initializes a low-level.
         */
        static void initLow();
      
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
         * Low level interrupt context.
         *
         * NOTE: This struct data is used by low level interrupt routine.
         *       It has to contain two fields and total size has to be eight bytes.
         *       The address of it has to be aligned to eight.
         */
        struct ContextLo
        {
            /**
             * DSP A0 for storing and restoring an intrrupted program.
             */
            void* reg;
            
            /**
             * Top of stack will be loaded to DSP SP for routing an intrrupt.
             */        
            const int64* tos;
            
            /** 
             * Constructor.
             */    
            ContextLo() :
                reg (NULL),
                tos (NULL){
            }
            
            /** 
             * Destructor.
             */
           ~ContextLo(){}
           
            /**
             * Equality operator.
             *
             * @param obj1 first object.
             * @param obj2 second object.
             * @return true if object are equal.
             */
            friend bool operator ==(const ContextLo& obj1, const ContextLo& obj2);     
      
        };
        
        /**
         * Hi level interrupt context.
         */
        struct ContextHi
        {
            /**
             * Number of interrupt vector.
             */
            int32 number;
          
            /**
             * Interrupt source.
             */
            Source source;
          
            /**
             * This user interrupt handler.
             */
            ::api::Task* handler;
          
            /**
             * CPU register state of interrupt source handler.
             */
            ::api::ProcessorRegisters* reg;
            
            /**
             * Stack of interrupt source handler.
             */         
            ::api::Stack<int64>* stack;
            
            /** 
             * Constructor.
             */    
            ContextHi() :
                number  (0),
                source  (UNDEF),
                handler (NULL),
                reg     (NULL),
                stack   (NULL){
            }
            
            /** 
             * Destructor.
             */
           ~ContextHi(){}
           
            /**
             * Equality operator.
             *
             * @param obj1 first object.
             * @param obj2 second object.
             * @return true if object are equal.
             */
            friend bool operator ==(const ContextHi& obj1, const ContextHi& obj2);
      
        };
            
        /**
         * All interrupt resource contexts.
         */
        class Contexts : public ::Object<>
        {
            typedef ::Object<> Parent;
          
        public:
        
            /**
             * Number of HW interrupt vectors.
             */
            static const int32 NUMBER_VECTORS = 12;      
            
            /** 
             * Constructor.
             */    
            Contexts() : Parent(),
                hi_        (),
                lo_        (NUMBER_VECTORS, reinterpret_cast< ContextLo* >( &buffer_[0] ) ),
                illegalHi_ (),
                illegalLo_ (){
                setConstruct( construct() ); 
            }
            
            /** 
             * Destructor.
             */
            virtual ~Contexts()
            {
            }
            
            /**
             * Allocates interrupt vectot.
             *
             * @param task    user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             * @return a vector intdex, or -1 if error has been occurred.
             */      
            int32 allocate(::api::Task& task, Source source)
            {
                if( not isConstructed() ) return false;
                if( not isSource(source) ) return false;
                int32 index = -1;
                // Test if interrupt source had been alloced
                bool wasAllocated = false;
                for(int32 i=0; i<NUMBER_VECTORS; i++)
                {
                    if(hi_[i].source != source) continue;
                    wasAllocated = true;
                    break;
                }        
                if( wasAllocated ) return -1;
                // Looking for free vector and alloc that if it is found          
                for(int32 i=0; i<Contexts::NUMBER_VECTORS; i++)
                {
                    if(hi_[i].handler != NULL) continue;
                    index = i;
                    break;
                }
                if(index < 0) return -1;
                // Set new context
                ContextHi* hi = &hi_[index];
                ContextLo* lo = &lo_[index];
                hi->number = index + 4;      
                hi->source = source;
                hi->handler = &task;      
                hi->reg = ::module::Registers::create();
                if(hi->reg == NULL) return -1;
                hi->stack = new Stack(::module::Processor::getStackType(), task.getStackSize() >> 3);
                if(hi->stack == NULL || not hi->stack->isConstructed()) return -1;
                lo->reg = hi->reg->getRegisters();
                lo->tos = hi->stack->getTos();      
                return index;
            } 
            
            /**
             * Removes this interrupt source.
             *
             * @param index an interrupt index.       
             */        
            void free(int32 index)
            {
                if( not isConstructed() ) return;      
                if( not isIndex(index) ) return ;   
                ContextHi* hi = &hi_[index];
                ContextLo* lo = &lo_[index];        
                delete hi->stack;        
                delete hi->reg;        
                lo->reg = NULL;
                lo->tos = NULL;
                hi->stack = NULL;
                hi->reg = NULL;      
                hi->handler = NULL;
                hi->source = UNDEF;      
                hi->number = 0;      
            }      
            
            /**
             * Returns hi context.
             *
             * @param index an interrupt index.
             * @return hi context.
             */        
            ContextHi& getHi(int32 index)
            {
                if( not isConstructed() ) return illegalHi_;      
                if( not isIndex(index) ) return illegalHi_;              
                return hi_[index];
            }
          
            /**
             * Returns a low context.
             *
             * @param index an interrupt index.
             * @return a low context.
             */              
            ContextLo& getLo(int32 index)
            {
                if( not isConstructed() ) return illegalLo_;      
                if( not isIndex(index) ) return illegalLo_;              
                return lo_[index];
            }
          
        private:
         
            /** 
             * Constructs the object.
             *
             * @param handler user class which implements an interrupt handler interface.
             * @param source  available interrupt source.     
             * @return true if object has been constructed successfully.
             */
            bool construct()
            {
                if( not isConstructed() ) return false;
                if( not hi_.isConstructed() ) return false;
                if( not lo_.isConstructed() ) return false;
                hi_.setIllegal(illegalHi_);
                lo_.setIllegal(illegalLo_);
                hi_.fill(illegalHi_);
                lo_.fill(illegalLo_);                
                return true;
            } 
            
            /**
             * Tests if given source is available.
             *
             * @param source interrupt source.
             * @return true if the source is available.
             */      
            static bool isSource(int32 source)
            {
                return 0 <= source && source < 128 ? true : false;
            }
            
            /**
             * Tests if given index is available.
             *
             * @param index an index.
             * @return true if the index is available.
             */      
            static bool isIndex(int32 index)
            {
                return 0 <= index && index < NUMBER_VECTORS ? true : false;
            }      
            
            /**
             * Hi level interrupt contexts.
             */            
            ::library::Buffer<ContextHi, NUMBER_VECTORS> hi_;
            
            /**
             * Low level interrupt contexts.
             */    
            ::library::Buffer<ContextLo> lo_;
          
            /**
             * Hi level interrupt illegal context.
             */
            ContextHi illegalHi_;
            
            /**
             * Low level interrupt illegal context.
             */
            ContextLo illegalLo_;      
            
            /**
             * Buffer for allocating low level interrupts contexts table (no boot).
             * 
             * Here is uint64 used instead of ContextLo for prohibiting of calling
             * default class constructors and excluding .pinit section by a compiler.
             * Also, uint64 is needed to be sure that the buffer will be aligned to eight.
             */    
            static uint64 buffer_[NUMBER_VECTORS];      
      
        };
        
        /**
         * Context of this interrupt resource.
         */    
        struct Context
        {
            /**
             * Hi level interrupt context.
             */            
            ContextHi* hi;
            
            /**
             * Low level interrupt context.
             */        
            ContextLo* lo;
                
            /** 
             * Constructor.
             */    
            Context() : 
                hi (NULL),
                lo (NULL){
            }
            
            /** 
             * Destructor.
             */
           ~Context(){}
           
        };       
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x98753af7;    
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;
        
        /**
         * HW interrupt registers (no boot).
         */
        static reg::Intc* regInt_;    
      
        /**
         * All interrupt resource contexts (no boot).
         */
        static Contexts* contexts_;
        
        /**
         * All interrupt resource contexts (no boot).
         *
         * This field is used only in interrupt service routine 
         * for fast accessing to the context table.
         * Don't use the field in any other cases.
         */    
        static ContextHi* contextHi_;    
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
        
        /**
         * Index of the interrupt context.
         */       
        int32 index_;
        
        /**
         * Context of the interrupt.
         */    
        Context ctx_;
        
        friend bool operator ==(const ContextHi& obj1, const ContextHi& obj2);
        friend bool operator ==(const ContextLo& obj1, const ContextLo& obj2);  
    };
    
    /**
     * HW interrupt handle routing.
     *
     * @param index index of HW interrupt vector number in contexts table
     */  
    void InterruptController::handler(register int32 index)
    {
        register ContextHi* ctx = &contextHi_[index];
        #ifdef EOOS_NESTED_INT
        register bool is = ctx->disable();
        Interrupt::enableAll(true);
        #endif
        ctx->handler->main();
        #ifdef EOOS_NESTED_INT
        Interrupt::disableAll();
        ctx->enable(is);
        #endif
    }
    
    /**
     * Equality operator.
     *
     * @param obj1 first object.
     * @param obj2 second object.
     * @return true if object are equal.
     */
    inline bool operator ==(const InterruptController::ContextHi& obj1, const InterruptController::ContextHi& obj2)
    {
        if      ( obj1.number  != obj2.number  ) return false;
        else if ( obj1.source  != obj2.source  ) return false;
        else if ( obj1.handler != obj2.handler ) return false;
        else if ( obj1.reg     != obj2.reg     ) return false;
        else if ( obj1.stack   != obj2.stack   ) return false;
        else return true;
    }      
    
    /**
     * Equality operator.
     *
     * @param obj1 first object.
     * @param obj2 second object.
     * @return true if object are equal.
     */
    inline bool operator ==(const InterruptController::ContextLo& obj1, const InterruptController::ContextLo& obj2)
    {
        if      ( obj1.tos != obj2.tos ) return false;
        else if ( obj1.reg != obj2.reg ) return false;
        else return true;
    }   
  
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 InterruptController::isInitialized_;  
  
    /**
     * HW interrupt registers (no boot).
     */
    reg::Intc* InterruptController::regInt_;  
    
    /**
     * All interrupt resource contexts (no boot).
     */
    InterruptController::Contexts* InterruptController::contexts_;
    
    /**
     * All interrupt resource contexts (no boot).
     */    
    InterruptController::ContextHi* InterruptController::contextHi_;
    
    /**
     * Buffer for allocating low level interrupts contexts table (no boot).
     */    
    uint64 InterruptController::Contexts::buffer_[ InterruptController::Contexts::NUMBER_VECTORS ];      
  
}
#endif // MODULE_INTERRUPT_CONTROLLER_HPP_
