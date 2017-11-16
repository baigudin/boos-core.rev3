/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_TIMER_CONTROLLER_HPP_
#define MODULE_TIMER_CONTROLLER_HPP_

#include "module.TimerBase.hpp"
#include "module.Interrupt.hpp"
#include "module.Register.hpp"
#include "module.reg.Timer.hpp"
#include "module.reg.System.hpp"

namespace module
{
    class TimerController : public ::module::TimerBase
    {
        typedef ::module::TimerBase  Parent;
  
    public:
    
        /**
         * Available interrupt sources.
         */
        enum InterruptSource
        {
            CPU_TIMER0_TINT0 = 0x0060,    
            CPU_TIMER1_TINT1 = 0x020c,
            CPU_TIMER2_TINT2 = 0x021c
        }; 
        
        /** 
         * Constructor.
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
        }
        
        /**
         * Gets this timer counter.
         *
         * @return timer counter register value.   
         */      
        virtual int64 getCount() const
        {
            if( not isConstructed_ ) return 0;
            uint64 cnt;
            cnt = regTim_->timh.val;
            cnt = cnt << 16;
            cnt = cnt | regTim_->tim.val;
            return cnt;
        }
        
        /**
         * Gets this timer period.
         *
         * @return timer period register value.
         */      
        virtual int64 getPeriod() const
        {
            if( not isConstructed_ ) return 0;
            uint64 prd;
            prd = regTim_->prdh.val;
            prd = prd << 16;      
            prd = prd | regTim_->prd.val;
            return prd;
        }  
        
        /**
         * Sets this timer counter.
         *
         * @param count timer counter register value.
         */      
        virtual void setCount(int64 count)
        {
            if( not isConstructed_ ) return;
            uint64 cnt = count;
            uint64 prd = getPeriod();
            if(cnt > prd) return;
            bool is = isStarted();
            if(is) stop();
            regTim_->tim.val = cnt & 0xffff;
            cnt = cnt >> 16;       
            regTim_->timh.val = cnt & 0xffff;
            if(is) start();    
        }      
        
        /**
         * Sets this timer period.
         *
         * @param us timer period in microseconds, zero sets the period to maxinum value.
         */      
        virtual void setPeriod(int64 us=0)
        {
            if( not isConstructed_ ) return; 
            int64 clock = getInternalClock();
            if(clock == 0) return; 
            uint64 prd = us != 0 ? (us * clock) / 1000000 : 0xffffffff;
            bool is = isStarted();
            if(is) stop();
            regTim_->prd.val = prd & 0xffff;
            prd = prd >> 16;       
            regTim_->prdh.val = prd & 0xffff;
            if(is) start();
        }
        
        /**
         * Starts this timer count.
         */      
        virtual void start()
        {
            if( not isConstructed_ ) return;
            regTim_->tcr.bit.tss = 0;    
        }
        
        /**
         * Stops this timer count.
         */      
        virtual void stop()
        {
            if( not isConstructed_ ) return;
            regTim_->tcr.bit.tss = 1;
        }
      
        /**
         * Returns this timer number.
         *
         * @return number of this timer, or -1 if error has been occurred.
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
            return 32;
        }
        
        /**
         * Returns this timer internal clock in Hz.
         *
         * @return timer internal clock.
         */  
        virtual int64 getInternalClock() const
        {
            if( not isConstructed_ ) return 0;    
            int64 div = (regTim_->tprh.bit.tddrh << 8) | regTim_->tpr.bit.tddr;
            return sysclk_ / (div + 1);
        }    
        
        /**
         * Tests if this timer can interrupt a CPU.
         *
         * @return true if this source is polarizing.
         */  
        virtual bool isInterrupting() const
        {
            if( not isConstructed_ ) return false;
            return regTim_->tcr.bit.tie == 1 ? true : false;
        }
        
        /**
         * Returns an available interrupt source for this timer.
         *
         * @return available interrupt source, or -1 if error has been occurred.
         */  
        virtual int32 getInterrupSource() const
        {
            switch(index_)
            {
                case 0: return CPU_TIMER0_TINT0;
                case 1: return CPU_TIMER1_TINT1;
                case 2: return CPU_TIMER2_TINT2;
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
            regSys_ = new (reg::System::ADDRESS) reg::System();            
            sysclk_ = getCpuClock(config.sourceClock);
            if(sysclk_ <= 0) return false;
            Register::allow();
            // Set CPU Timers are not clocked
            regSys_->pclkcr3.bit.cputimer0enclk = 0;
            regSys_->pclkcr3.bit.cputimer1enclk = 0;
            regSys_->pclkcr3.bit.cputimer2enclk = 0;                
            Register::protect();      
            for(int32 i=0; i<RESOURCES_NUMBER; i++) 
            {
                uint32 addr = address(i);
                if(addr == 0) return false;
                reg::Timer* timer = new (addr) reg::Timer();;
                lock_[i] = false;      
            } 
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
         * Constructor.
         *
         * @param index available timer index.
         * @return boolean result.
         */  
        bool construct(int32 index)
        {
            if(isInitialized_ != IS_INITIALIZED) return false;    
            bool res = false;
            bool is = Interrupt::disableAll();
            do
            {
                if(lock_[index] == true) break; 
                uint32 addr = address(index);
                if(addr == 0) break;
                Register::allow();
                // Set the CPU Timer is clocked
                switch(index)
                {
                    case  0: regSys_->pclkcr3.bit.cputimer0enclk = 1; break;
                    case  1: regSys_->pclkcr3.bit.cputimer1enclk = 1; break;
                    case  2: regSys_->pclkcr3.bit.cputimer2enclk = 1; break;               
                    default: break;
                }
                Register::protect();      
                regTim_ = new (addr) reg::Timer();        
                // Set the timer emulation mode
                regTim_->tcr.bit.free = 0;
                regTim_->tcr.bit.soft = 0;
                // Stop the timer
                regTim_->tcr.bit.tss = 1;        
                // Enable timer interrupt
                regTim_->tcr.bit.tie = 1;
                index_ = index;        
                lock_[index_] = true;
                res = true;
            }
            while(false);
            return Interrupt::enableAll(is, res);    
        }
        
        /**
         * Tests if this timer is counting.
         *
         * @return true if this timer is counting.
         */        
        bool isStarted()
        {
            return regTim_->tcr.bit.tss == 1 ? false : true;
        }
        
        /** 
         * Returns SYSCLK based on OSCCLK.
         *     
         * @param sourceClock source clock in Hz.    
         * @return CPU clock in Hz.
         */  
        static int64 getCpuClock(int64 sourceClock)
        {
            int32 sysclk, m, d;
            if(regSys_ == NULL) return -1;
            // Test the oscillator is not off
            if(regSys_->pllsts.bit.oscoff == 1) return false;
            // Test the PLL is set correctly
            if(regSys_->pllsts.bit.plloff == 1 && regSys_->pllcr.bit.div > 0) return false;
            // Calculate the CPU frequency
            m = regSys_->pllcr.bit.div != 0 ? regSys_->pllcr.bit.div : 1;
            switch(regSys_->pllsts.bit.divsel)
            {
                case  0: 
                case  1: d = 4; break;
                case  2: d = 2; break;       
                default: return false;
            }
            sysclk = (sourceClock & 0xffffffff) / d * m;
            return sysclk > 0 ? sysclk : -1;
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
                case 0: return reg::Timer::ADDRESS0;
                case 1: return reg::Timer::ADDRESS1;
                case 2: return reg::Timer::ADDRESS2;
                default: return 0;
            }
        }    
        
        /**
         * Number of HW timers.
         */
        static const int32 RESOURCES_NUMBER = 3;    
        
        /**
         * The module initialized falg value.
         */
        static const int32 IS_INITIALIZED = 0x123abc73;
      
        /**
         * CPU clock in Hz (no boot).
         */
        static int64 sysclk_;
      
        /**
         * Locked by some object flag of each HW timer (no boot).
         */    
        static bool lock_[RESOURCES_NUMBER];
        
        /**
         * System Control Registers (no boot).
         */  
        static reg::System* regSys_;
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;    
        
        /**
         * Number of hardware timer
         */
        int32 index_;
        
        /**
         * HW timer registers.
         */
        reg::Timer* regTim_;
      
    }; 
    
    /**
     * CPU clock in Hz (no boot).
     */
    int64 TimerController::sysclk_;
    
    /**
     * Locked by some object flag of each HW timer (no boot).  
     */
    bool TimerController::lock_[TimerController::RESOURCES_NUMBER];
    
    /**
     * System Control Registers (no boot).
     */  
    ::module::reg::System* TimerController::regSys_;
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 TimerController::isInitialized_;
       
}
#endif // MODULE_TIMER_CONTROLLER_HPP_
