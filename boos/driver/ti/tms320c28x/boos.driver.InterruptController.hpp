/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_INTERRUPT_CONTROLLER_HPP_
#define BOOS_DRIVER_INTERRUPT_CONTROLLER_HPP_

#include "boos.driver.InterruptResource.hpp"
#include "boos.driver.Processor.hpp"
#include "boos.driver.Register.hpp"
#include "boos.driver.reg.Pie.hpp"
#include "boos.util.Stack.hpp"

namespace driver
{
  class InterruptController : public ::driver::InterruptResource
  {
    friend class ::driver::Interrupt;
      
    typedef ::driver::InterruptResource     Parent;
    typedef ::util::Stack<int64,Allocator>  Stack;

  public:
  
    /**
     * Available interrupt sources.
     */
    enum Source 
    {
      // NOT PIE Vectors
      GPIO0_INT            = 0x0000,
      GPIO1_INT            = 0x0010,
      GPIO2_INT            = 0x0020,
      GPIO3_INT            = 0x0030,
      GPIO4_INT            = 0x0040,
      GPIO5_INT            = 0x0050,
      GPIO6_INT            = 0x0060,
      GPIO7_INT            = 0x0070,
      GPIO8_INT            = 0x0080,
      GPIO9_INT            = 0x0090,
      GPIO10_INT           = 0x00a0,
      GPIO11_INT           = 0x00b0,
      GPIO12_INT           = 0x00c0,
      GPIO13_INT           = 0x00d0,
      GPIO14_INT           = 0x00e0,
      GPIO15_INT           = 0x00f0,
      GPIO16_INT           = 0x0100,
      GPIO17_INT           = 0x0110,
      GPIO18_INT           = 0x0120,
      GPIO19_INT           = 0x0130,
      GPIO20_INT           = 0x0140,
      GPIO21_INT           = 0x0150,
      GPIO22_INT           = 0x0160,
      GPIO23_INT           = 0x0170,
      GPIO24_INT           = 0x0180,
      GPIO25_INT           = 0x0190,
      GPIO26_INT           = 0x01a0,
      GPIO27_INT           = 0x01b0,
      GPIO28_INT           = 0x01c0,
      GPIO29_INT           = 0x01d0,
      GPIO30_INT           = 0x01e0,
      GPIO31_INT           = 0x01f0,
      CPU_TIMER1_TINT1     = 0x0200,
      CPU_TIMER2_TINT2     = 0x0210,
      // PIE Group 1 Vectors - MUXed into CPU INT1
      ADC_SEQ1INT          = 0x0011,
      ADC_SEQ2INT          = 0x0021,
      XINT1                = 0x0041,
      XINT2                = 0x0051,
      ADC_ADCINT           = 0x0061,
      CPU_TIMER0_TINT0     = 0x0071,
      LPM_WD_WAKEINT       = 0x0081,
      // PIE Group 2 Vectors - MUXed into CPU INT2
      EPWM1_TZINT          = 0x0012,
      EPWM2_TZINT          = 0x0022,
      EPWM3_TZINT          = 0x0032,
      EPWM4_TZINT          = 0x0042,
      EPWM5_TZINT          = 0x0052,
      EPWM6_TZINT          = 0x0062,
      // PIE Group 3 Vectors - MUXed into CPU INT3
      EPWM1_INT            = 0x0013,
      EPWM2_INT            = 0x0023,
      EPWM3_INT            = 0x0033,
      EPWM4_INT            = 0x0043,
      EPWM5_INT            = 0x0053,
      EPWM6_INT            = 0x0063,     
      // PIE Group 4 Vectors - MUXed into CPU INT4
      ECAP1_INT            = 0x0014,
      ECAP2_INT            = 0x0024,
      ECAP3_INT            = 0x0034,
      ECAP4_INT            = 0x0044,
      ECAP5_INT            = 0x0054,
      ECAP6_INT            = 0x0064,
      // PIE Group 5 Vectors - MUXed into CPU INT5
      EQEP1_INT            = 0x0015,
      EQEP2_INT            = 0x0025,
      // PIE Group 6 Vectors - MUXed into CPU INT6
      SPI_A_SPIRXINTA      = 0x0016,
      SPI_A_SPITXINTA      = 0x0026,
      McBSP_B_MRINTB       = 0x0036,
      McBSP_B_SPI_B_MXINTB = 0x0046,
      McBSP_A_MRINTA       = 0x0056,
      McBSP_A_MXINTA       = 0x0066,
      // PIE Group 7 Vectors - MUXed into CPU INT7
      DMA_CHANNEL1_DINTCH1 = 0x0017, 
      DMA_CHANNEL2_DINTCH2 = 0x0027, 
      DMA_CHANNEL3_DINTCH3 = 0x0037, 
      DMA_CHANNEL4_DINTCH4 = 0x0047, 
      DMA_CHANNEL5_DINTCH5 = 0x0057, 
      DMA_CHANNEL6_DINTCH6 = 0x0067,
      // PIE Group 8 Vectors - MUXed into CPU INT8
      I2C_A_I2CINT1A       = 0x0018,  
      I2C_A_I2CINT2A       = 0x0028,
      SCI_C_SCIRXINTC      = 0x0058,
      SCI_C_SCITXINTC      = 0x0068,
      // PIE Group 9 Vectors - MUXed into CPU INT9
      SCI_A_SCIRXINTA      = 0x0019,
      SCI_A_SCITXINTA      = 0x0029,
      SCI_B_SCIRXINTB      = 0x0039,
      SCI_B_SCITXINTB      = 0x0049,
      ECAN_A_ECAN0INTA     = 0x0059,
      ECAN_A_ECAN1INTA     = 0x0069,
      ECAN_B_ECAN0INTB     = 0x0079,
      ECAN_B_ECAN1INTB     = 0x0089,
      // PIE Group 12 Vectors - Muxed into CPU INT12
      XINT3                = 0x001c,
      XINT4                = 0x002c,
      XINT5                = 0x003c,
      XINT6                = 0x004c,
      XINT7                = 0x005c,
      FPU_LVF              = 0x007c,
      FPU_LUF              = 0x008c
    };    
  
    /** 
     * Constructor.
     */    
    InterruptController() : Parent(),
      ctx_ (NULL){
      setConstruct( true );      
    }

    /** 
     * Constructor.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @param source  available interrupt source.
     */     
    InterruptController(::api::Task* handler, int32 source) : Parent(),
      ctx_ (NULL){
      setConstruct( setHandler(*handler, source) );      
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
      if(!isAllocated()) return;
      jumpLow(0xffffffff);    
    }
    
    /**
     * Clears an interrupt status of this source.
     */     
    virtual void clear()
    {
      if(!isAllocated()) return;    
      bool is = Interrupt::globalDisable();      
      if(ctx_->pie == NULL)
        clearLow(ctx_->bitCpu);
      else
        ctx_->pie->ifr.val &= ~ctx_->bitPie;
      return Interrupt::globalEnable(is);
    }
    
    /**
     * Sets an interrupt status of this source.
     */    
    virtual void set()
    {
      if(!isAllocated()) return;
      bool is = Interrupt::globalDisable();      
      if(ctx_->pie == NULL)
        setLow(ctx_->bitCpu);
      else
        ctx_->pie->ifr.val |= ctx_->bitPie;
      return Interrupt::globalEnable(is);
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    virtual bool disable()
    {
      if(!isAllocated()) return false;
      bool res;
      bool is = Interrupt::globalDisable();      
      if(ctx_->pie == NULL)
        res = disableLow(ctx_->bitCpu);
      else
      {
        res = ctx_->pie->ier.val & ctx_->bitPie ? true : false;
        ctx_->pie->ier.val &= ~ctx_->bitPie;      
      }
      return Interrupt::globalEnable(is, res);
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by lock method.
     */
    virtual void enable(bool status)
    {
      if(!isAllocated()) return;
      bool is = Interrupt::globalDisable();
      if(ctx_->pie == NULL)
        enableLow(ctx_->bitCpu, status);
      else if(status)
        ctx_->pie->ier.val |= ctx_->bitPie;
      Interrupt::globalEnable(is);      
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
      bool is = Interrupt::globalDisable();
      do{
        if( isAllocated() ) break;
        if( not isSource(source) ) break;
        Source src = static_cast<Source>(source);
        Context* ctx = new Context(handler, src);
        if(ctx == NULL || not ctx->isConstructed()) break;
        ctx_ = ctx;
        res = true;
      }while(false);
      return Interrupt::globalEnable(is, res);
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
     * Sets new registers context for storing.
     *
     * @param reg new registers context.
     */
    virtual void setRegister(::driver::Register& reg)
    {
    }
    
    /**
     * Disables all maskable interrupts.
     *
     * @return global interrupts enable bit value before method was called.
     */
    static bool globalDisable();

    /**
     * Enables all maskable interrupts.
     *
     * @param status the returned status by disable method.
     */
    static void globalEnable(bool status);
    
  private:
  
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
      if(vec.bit.grp == 0x0)
      {
        // Drop GPIO interrupt sources
        if(vec.bit.num < 0x20) return false;
      }
      // PIE interrupt vector       
      else
      {
        if(vec.bit.num < 1 || vec.bit.num > 8) return false;      
      }
      return true;      
    }
    
    /**
     * Initialization.
     *
     * @param config the operating system configuration.
     * @return true if no errors.
     */
    static bool init(const Configuration& config)
    {
      isInitialized_ = 0;   
      if(config.sourceClock == 0) return false;
      regPie_ = new (reg::Pie::ADDRESS) reg::Pie();
      // PIE vectors table initialization
      uint32* dst = reinterpret_cast<uint32*>(PIE_ADDR);
      const uint32* src = getVectorsLow();
      Register::allow();
      for(int32 i=0; i<PIE_VETS; i++) dst[i] = src[i];
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
    static void deinit()
    {
      isInitialized_ = 0;
    }
    
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
     * The driver initialized falg value.
     */
    static const int32 IS_INITIALIZED = 0x98753af7;

    /**
     * PIE 32-bit vectors number.
     */    
    static const int32 PIE_VETS = 0x0000080;

    /**
     * PIE vectors address.
     */
    static const uint32 PIE_ADDR = 0x00000d00;
    
    /**
     * Peripheral Interrupt Expansion (no boot).
     */  
    static reg::Pie* regPie_;
    
    /**
     * Driver has been initialized successfully (no boot).
     */
    static int32 isInitialized_;
    
    /**
     * Hi level interrupt context.
     */
    struct Context : public ::Object<>
    {
      typedef ::Object<> Parent;
      
    public:
    
      /** 
       * Constructor.
       *
       * @param handler pointer to user class which implements an interrupt handler interface.
       * @param source  available interrupt source.
       */    
      Context(::api::Task& hndl, Source src) : Parent(),
        grpIndex  (((static_cast<int32>(src) & 0x0000000f) >> 0) - 1),
        numIndex  (((static_cast<int32>(src) & 0x0000fff0) >> 4) - 1),
        source    (src),
        handler   (hndl),
        bitCpu    (0x00000000),
        bitPie    (0x00000000),
        pie       (NULL),
        reg       (NULL),
        stack     (NULL){
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
        ::driver::reg::Pie* regPie = new (reg::Pie::ADDRESS) reg::Pie();
        // The source is CPU source
        if(grpIndex < 0)
        {
          switch(source)
          {
            case CPU_TIMER1_TINT1:
            {
              bitCpu = 0x1 << 12;
            }
            break;
            case CPU_TIMER2_TINT2:
            {
              bitCpu = 0x1 << 13;
            }
            break;
          }
        
        }
        // The source is PIE source
        else
        {
          pie = &regPie->pie[grpIndex];
          bitPie = 0x1 << numIndex;
          bitCpu = 0x1 << grpIndex;
        }
        // Create context CPU registers
        reg = ::driver::Register::create();
        if(reg == NULL) return false;
        // Create context stack
        stack = new Stack(::driver::Processor::stackType(), handler.stackSize() >> 2);
        if(stack == NULL || not stack->isConstructed()) return false;
        return true;
      }
      
      /**
       * Number of PIE group
       */
      int32 grpIndex;

      /**
       * Number of vector in PIE group
       */
      int32 numIndex;
      
    public:        
    
      /**
       * Interrupt source.
       */
      Source source;

      /**
       * This user interrupt handler.
       */
      ::api::Task& handler;
      
      /**
       * Mask for IER or IFR bit mask.
       */
      uint16 bitCpu;
      
      /**
       * Mask for IER or IFR bit mask.
       */
      uint16 bitPie;

      /**
       * Mask for IER or IFR bit mask.
       */      
      ::driver::reg::Pie::Group* pie;
    
      /**
       * CPU register state of interrupt source handler.
       */
      ::driver::Register* reg;
      
      /**
       * Stack of interrupt source handler.
       */         
      ::api::Stack<int64>* stack;

    };
    
    /**
     * The interrupt source contex.
     */    
    Context* ctx_;

  };
  
  /**
   * System Control Registers (no boot).
   */  
  ::driver::reg::Pie* InterruptController::regPie_;

  /**
   * Driver has been initialized successfully (no boot).
   */
  int32 InterruptController::isInitialized_;
  
}
#endif // BOOS_DRIVER_INTERRUPT_CONTROLLER_HPP_
