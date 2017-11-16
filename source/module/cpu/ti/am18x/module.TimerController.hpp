/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_TIMER_CONTROLLER_HPP_
#define MODULE_TIMER_CONTROLLER_HPP_

#include "module.TimerBase.hpp"
#include "module.Interrupt.hpp"
#include "module.reg.Timer.hpp"
#include "module.reg.Syscfg0.hpp"
#include "module.reg.Pllc0.hpp"
#include "module.reg.Pllc1.hpp"

namespace module
{
    class TimerController : public ::module::TimerBase
    {
        typedef ::module::TimerBase  Parent;
  
    public:
    
        /**
         * Available interrupt sources for all AM18x family.
         */
        enum Source
        {
            T64P0_TINT12 = 21,
            T64P1_TINT12 = 23,
            T64P2_ALL    = 68,
            T64P3_ALL    = 96
        };
      
        /** 
         * Constructor.
         *
         * Constructs this object and allocs a first free hardware timer.
         */      
        TimerController() : Parent(),
            index_  (-1),
            regTim_ (NULL){
            for(int32 i=0; i<RESOURCES_NUMBER; i++) 
            {
                if( construct(i) == true )
                {
                    setConstruct(true);
                    return;
                }
            }
            setConstruct(false);
        }  
        
        /** 
         * Constructor.
         *
         * @param index available timer index.
         */
        TimerController(int32 index) : Parent(),
            index_  (-1),
            regTim_ (NULL){
            setConstruct( construct(index) );
        }
      
        /** 
         * Destructor.
         */    
        virtual ~TimerController()
        {
            if(!isConstructed_) return;
            bool is = Interrupt::disableAll();
            lock_[index_] = false;
            stop();
            regTim_ = NULL;
            index_ = -1;
            Interrupt::enableAll(is);    
        }
        
        /**
         * Gets this timer counter.
         *
         * @return timer counter register value.   
         */      
        virtual int64 getCount() const
        {
            if(!isConstructed_) return 0;
            uint64 cnt;
            cnt = regTim_->tim34.value;
            cnt = cnt << 32;      
            cnt = cnt bitor regTim_->tim12.value;
            return cnt;
        }
        
        /**
         * Gets this timer period.
         *
         * @return timer period register value.
         */      
        virtual int64 getPeriod() const
        {
            if(!isConstructed_) return 0;
            uint64 prd;
            prd = regTim_->prd34.value;
            prd = prd << 32;      
            prd = prd bitor regTim_->prd12.value;
            return prd;
        }  
        
        /**
         * Sets this timer counter.
         *
         * @param count timer counter register value.
         */      
        virtual void setCount(int64 count)
        {
            if(!isConstructed_) return;
            uint64 cnt = count;
            uint64 prd = getPeriod();
            if(cnt > prd) return;
            bool is = isStarted();
            if(is) stop();
            regTim_->tim12.value = cnt bitand 0xffffffff;
            cnt = cnt >> 32;       
            regTim_->tim34.value = cnt bitand 0xffffffff;
            if(is) start();
        }      
        
        /**
         * Sets this timer period.
         *
         * @param us timer period in microseconds, zero sets the period to maxinum value.
         */      
        virtual void setPeriod(int64 us=0)
        {
            if(!isConstructed_) return;
            int64 clock = getInternalClock();
            if(clock == 0) return;       
            uint64 prd = us != 0 ? (us * clock) / 1000000 : 0xffffffffffffffff;
            bool is = isStarted();
            if(is) stop();
            regTim_->prd12.value = prd bitand 0xffffffff;
            prd = prd >> 32;       
            regTim_->prd34.value = prd bitand 0xffffffff;
            if(is) start();
        }
        
        /**
         * Starts this timer count.
         */      
        virtual void start()
        {
            if(!isConstructed_) return;
            // The timer is enabled continuously
            regTim_->tcr.bit.enamode12 = 2;
        }
        
        /**
         * Stops this timer count.
         */      
        virtual void stop()
        {
            if(!isConstructed_) return;
            // The timer is disabled
            regTim_->tcr.bit.enamode12 = 0;
        }
      
        /**
         * Returns this timer index.
         *
         * @return index of this timer.
         */      
        virtual int32 getIndex() const
        {
            return isConstructed_ ? index_ : -1;
        }
        
        /**
         * Returns number of timer digits.
         *
         * @return timer digits.
         */  
        virtual int32 getDigit() const
        {
            return 64;
        }
        
        /**
         * Returns this timer internal clock in Hz.
         *
         * @return timer internal clock.
         */  
        virtual int64 getInternalClock() const
        {
            if(!isConstructed_) return 0;
            int64 oscin = config_.sourceClock;
            switch(index_)
            {
                case 0:
                case 1:        
                    // Internal clock for this timers is AUXCLK, which is OSCIN
                    return oscin;

                case 2:
                case 3:        
                {
                    int64 prediv, pllm, postdiv, plldiv2;
                    reg::Syscfg0* syscfg0 = new (reg::Syscfg0::ADDRESS) reg::Syscfg0();
                    // Get clocks from PLL0 SYSCLK2
                    if(syscfg0->cfgchip3.bit.async3Clksrc == 0)
                    {
                        reg::Pllc0* pllc0 = new (reg::Pllc0::ADDRESS) reg::Pllc0();
                        // PLL0 in normal mode
                        if(pllc0->pllctl.bit.pllen == 1)
                        {
                            prediv = pllc0->prediv.bit.ratio + 1;
                            pllm = pllc0->pllm.bit.pllm + 1;
                            postdiv = pllc0->postdiv.bit.ratio + 1;
                        }
                        // PLL0 in bypassed mode
                        else
                        {
                            prediv = 1;
                            pllm = 1;
                            postdiv = 1;
                        }
                        plldiv2 = pllc0->plldiv2.bit.ratio + 1;            
                    }
                    // Get clocks from PLL1 SYSCLK2
                    else
                    {
                        reg::Pllc1* pllc1 = new (reg::Pllc1::ADDRESS) reg::Pllc1();
                        // PLL1 in normal mode
                        if(pllc1->pllctl.bit.pllen == 1)            
                        {
                            pllm = pllc1->pllm.bit.pllm + 1;
                            postdiv = pllc1->postdiv.bit.ratio + 1;
                        }
                        // PLL1 in bypassed mode
                        else
                        {
                            pllm = 1;
                            postdiv = 1;
                        }
                        prediv = 1;
                        plldiv2 = pllc1->plldiv2.bit.ratio + 1;
                    }
                    // Calculation
                    int64 clock = oscin;
                    clock = clock / prediv;
                    clock = clock * pllm;
                    clock = clock / postdiv;
                    clock = clock / plldiv2;
                    return clock;
                }
                
                default: 
                    return 0;        
            }
        }    
        
        /**
         * Tests if this timer can interrupt a CPU.
         *
         * @return true if this source is polarizing.
         */  
        virtual bool isInterrupting() const
        {
            return true;
        }
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source.
         */  
        virtual int32 getInterrupSource() const
        {
            switch(index_)
            {
                case 0: 
                    return T64P0_TINT12;
                    
                case 1: 
                    return T64P1_TINT12;
                    
                case 2: 
                    return T64P2_ALL;
                    
                case 3: 
                    return T64P3_ALL;
            }
            return -1;
        }
        
        /**
         * Initialization.
         *
         * @param config the operating system configuration.
         * @return true if no errors.
         */
        static bool initialize(const Configuration& config)
        {
            isInitialized_ = 0;        
            config_ = config;    
            reg::Timer* timer;    
            reg::Syscfg0* syscfg0 = new (reg::Syscfg0::ADDRESS) reg::Syscfg0();
            // Unlock the SYSCFG module
            syscfg0->kick0r.bit.kick0 = 0x83E70B13;
            syscfg0->kick1r.bit.kick1 = 0x95A4F1E0;
            // Set emulation suspend sources for all timers
            syscfg0->suspsrc.bit.timer64p3src = 0;
            syscfg0->suspsrc.bit.timer64p2src = 0;
            syscfg0->suspsrc.bit.timer64p1src = 0;
            syscfg0->suspsrc.bit.timer64p0src = 0;
            for(int32 i=0; i<RESOURCES_NUMBER; i++) 
            {
                lock_[i] = false;      
                uint32 addr = address(i);
                if(addr == 0) return false;        
                timer = new (addr) reg::Timer(); 
                reset(*timer);
            }
            // Lock the SYSCFG module
            syscfg0->kick0r.bit.kick0 = 0x00000000;
            syscfg0->kick1r.bit.kick1 = 0x00000000;        
            isInitialized_ = IS_INITIALIZED;            
            return true;
        }
      
        /**
         * Deinitialization.
         */
        static void deinitialize()
        {
            for(int32 i=0; i<RESOURCES_NUMBER; i++) 
            {
                uint32 addr = address(i);
                if(addr == 0) break;       
                reg::Timer* reg = new (addr) reg::Timer(); 
                reg->tcr.bit.enamode12 = 0;        
            }
            isInitialized_ = 0;          
        }
      
    private:    
    
        /** 
         * Constructor.
         *
         * @param index available timer index.
         * @return boolean result.
         */  
        bool construct(int32 index)
        {
            if(!isConstructed_) return false;
            if(isInitialized_ != IS_INITIALIZED) return false;      
            uint32 addr = address(index);
            if(addr == 0) return false;
            bool is = Interrupt::disableAll();
            if(lock_[index] == true) return Interrupt::enableAll(is, false); 
            regTim_ = new (addr) reg::Timer();
            lock_[index] = true;
            index_ = index;
            reset(*regTim_);
            // Set an internal clock as the selected clock source for the timer
            regTim_->tcr.bit.clksrc12 = 0;
            // Enable the 64-Bit mode
            regTim_->tgcr.bit.timmode = 0;
            regTim_->tgcr.bit.tim12rs = 1;
            regTim_->tgcr.bit.tim34rs = 1;
            return Interrupt::enableAll(is, true);
        }
        
        /**
         * Tests if this timer is counting.
         *
         * @return true if this timer is counting.
         */        
        bool isStarted()
        {
            return regTim_->tcr.bit.enamode12 == 0 ? false : true;
        }    
        
        /**
         * Resets timer registers.
         *
         * @param reg timer registers.
         */
        static void reset(reg::Timer& reg)
        {
            reg.emumgt.value = 0x00000000;
            reg.tcr.value = 0x00000000;        
            reg.tgcr.value = 0x00000000;            
            reg.prd12.value = 0x00000000;    
            reg.prd34.value = 0x00000000;        
            reg.tim12.value = 0x00000000;    
            reg.tim34.value = 0x00000000; 
        } 
        
        /**
         * Returns a timer register address.
         *
         * @param index timer index.
         * @return memory address of given timer index.
         */
        static uint32 address(int32 index)
        {
            switch(index)
            {
                case 0: 
                    return reg::Timer::ADDRESS0;
                    
                case 1: 
                    return reg::Timer::ADDRESS1;
                    
                case 2: 
                    return reg::Timer::ADDRESS2;
                    
                case 3: 
                    return reg::Timer::ADDRESS3;
                    
                default: 
                    return 0;
            }
        }
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        TimerController(const TimerController& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        TimerController& operator =(const TimerController& obj);
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x19835472;        
      
        /**
         * Number of timers.
         */
        static const int32 RESOURCES_NUMBER = 4;
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;
        
        /**
         * The operating system configuration (no boot).
         */
        static Configuration config_;    
        
        /**
         * Locked by some object flag of each HW timer (no boot).
         */    
        static bool lock_[RESOURCES_NUMBER];
        
        /**
         * Index of hardware timer
         */
        int32 index_;
        
        /**
         * HW timet registers (no boot).
         */
        reg::Timer* regTim_;      
      
    };
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 TimerController::isInitialized_;    
    
    /**
     * The operating system configuration (no boot).
     */
    ::Configuration TimerController::config_;
    
    /**
     * Locked by some object flag of each HW timer (no boot).  
     */
    bool TimerController::lock_[TimerController::RESOURCES_NUMBER];

}
#endif // MODULE_TIMER_CONTROLLER_HPP_
