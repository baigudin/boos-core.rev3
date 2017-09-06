/** 
 * Hardware interrupt controller.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_INTERRUPT_CONTROLLER_HPP_
#define DRIVER_INTERRUPT_CONTROLLER_HPP_

#include "driver.InterruptResource.hpp"
#include "driver.Processor.hpp"
#include "driver.Register.hpp"
#include "driver.reg.Intc.hpp"
#include "utility.Stack.hpp"
#include "utility.Memory.hpp"

namespace driver
{
  class InterruptController : public ::driver::InterruptResource
  {
    typedef ::driver::InterruptResource        Parent;
    typedef ::utility::Stack<int64,Allocator>  Stack;

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
      IDMA_BUSERR     = 127  // IDMA bus error interrupt
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
      removeHandler();    
    }
    
    /**
     * Jumps to interrupt hardware vector.
     */      
    virtual void jump()
    {
    }
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear()
    {
    }
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set()
    {
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable()
    {
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status)
    { 
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
    }

    /**
     * Removes this interrupt source.
     */        
    virtual void removeHandler()
    {
    }
    
    /**
     * Resets registers context for storing to the default.
     */
    virtual void resetRegister()
    {
    }
    
    /**
     * Sets new registers context for store.
     *
     * @param reg pointer to new registers context.
     */
    virtual void setRegister(::driver::Register& reg)
    {
    }

    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const ::Configuration& config)
    {
      isInitialized_ = 0;    
      config_ = config;
      regInt_ = new (reg::Intc::ADDRESS) reg::Intc();
      
      isInitialized_ = IS_INITIALIZED; 
      return true;
    }
    
    /**
     * Deinitialization.
     */
    static void deinit()
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
      if(!isConstructed_) return false;
      return ctx_ == NULL ? false : true;
    }      
    
    /**
     * HW interrupt handle routing.
     *
     * @param index index of HW interrupt vector number in context table
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
    struct ContextLow
    {
      /**
       * DSP A0 for storing and restoring intrrupted program.
       */
      void* reg;
      
      /**
       * Top of stack will be loaded to DSP SP for routing an intrrupt.
       */        
      const int64* tos;

    };
    
    /**
     * Hi level interrupt context.
     */
    struct Context
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
      ::driver::Register* reg;
      
      /**
       * Stack of interrupt source handler.
       */         
      ::api::Stack<int64>* stack;
      
      /**
       * Low level interrupt context.
       */        
      ContextLow* low;        

    };
    
    /**
     * The driver initialized falg value.
     */
    static const int32 IS_INITIALIZED = 0x98753af7;    

    /**
     * Number of HW interrupt vectors.
     */
    static const int32 NUMBER_VECTORS = 12;

    /**
     * HW interrupt registers (no boot).
     */
    static reg::Intc* regInt_;
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    static int32 isInitialized_;
    
    /**
     * Hi level interrupts context table (no boot).
     */        
    static Context context_[NUMBER_VECTORS];

    /**
     * Low level interrupts context table (no boot).
     */    
    static ContextLow contextLow_[NUMBER_VECTORS];
    
    /**
     * The operating system configuration (no boot).
     */
    static ::Configuration config_;

    /**
     * Pointer to the hi level interrupt context.
     */    
    Context* ctx_;
  
  };
  
  /**
   * HW interrupt handle routing.
   *
   * @param index index of HW interrupt vector number in context table
   */  
  void InterruptController::handler(register int32 index)
  {
    register Context* ctx = &context_[index];
    #ifdef EOOS_NESTED_INT
    register bool is = ctx->disable();
    Interrupt::globalEnable(true);
    #endif
    ctx->handler->main();
    #ifdef EOOS_NESTED_INT
    Interrupt::globalDisable();
    ctx->enable(is);
    #endif
  }    
  
  /**
   * HW interrupt registers (no boot).
   */
  reg::Intc* InterruptController::regInt_;
  
  /**
   * Driver has been initialized successfully (no boot).
   */
  int32 InterruptController::isInitialized_;  

  /**
   * Hi level interrupts context table (no boot).
   */        
  InterruptController::Context InterruptController::context_[NUMBER_VECTORS];  

  /**
   * Low level interrupts context table (no boot).
   */    
  InterruptController::ContextLow InterruptController::contextLow_[NUMBER_VECTORS];

  /**
   * The operating system configuration (no boot).
   */
  ::Configuration InterruptController::config_; 

}
#endif // DRIVER_INTERRUPT_CONTROLLER_HPP_
