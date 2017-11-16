/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_TIMER_CONTROLLER_HPP_
#define MODULE_TIMER_CONTROLLER_HPP_

#include "Object.hpp"
#include "api.ProcessorTimer.hpp"
#include "module.reg.Timer.hpp"

namespace module
{
    class TimerController : public ::Object<>, public ::api::ProcessorTimer
    {
        typedef ::Object<> Parent;
        
        /**
         * Available interrupt sources.
         */
        enum InterruptSource
        {
            TINTLO0 = 67, // Timer 0 lower counter interrupt
            TINTHI0 = 68, // Timer 0 higher counter interrupt
            TINTLO1 = 69, // Timer 1 lower counter interrupt
            TINTHI1 = 70  // Timer 1 higher counter interrupt
        };
        
    public:        
      
        /** 
         * Constructor.
         */      
        TimerController() : Parent(),
            isConstructed_ (getConstruct()),        
            timerClock_    (0),
            index_         (-1),
            regTim_        (NULL){
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
            isConstructed_ (getConstruct()),        
            timerClock_    (0),
            index_         (-1),
            regTim_        (NULL){
            setConstruct( construct(index) );
        }
      
        /** 
         * Destructor.
         */    
        virtual ~TimerController()
        {
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
         * Gets this timer counter.
         *
         * @return timer counter register value.   
         */      
        virtual int64 getCount() const
        {
            if( not isConstructed_ ) return 0;
            uint64 cnt;
            cnt = regTim_->cnthi.value;
            cnt = cnt << 32;
            cnt = cnt | regTim_->cntlo.value;
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
            prd = regTim_->prdhi.value;
            prd = prd << 32;      
            prd = prd | regTim_->prdlo.value;
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
            regTim_->cntlo.value = cnt & 0xffffffff;
            cnt = cnt >> 32;       
            regTim_->cnthi.value = cnt & 0xffffffff;
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
            uint64 prd = us != 0 ? (us * clock) / 1000000 : 0xffffffffffffffff;
            bool is = isStarted();
            if(is) stop();
            regTim_->prdlo.value = prd & 0xffffffff;
            prd = prd >> 32;       
            regTim_->prdhi.value = prd & 0xffffffff;
            if(is) start();
        }
        
        /**
         * Starts this timer count.
         */      
        virtual void start()
        {
            if( not isConstructed_ ) return; 
            regTim_->tcr.bit.enamodeLo = 2;
        }
        
        /**
         * Stops this timer count.
         */      
        virtual void stop()
        {
            if( not isConstructed_ ) return;   
            regTim_->tcr.bit.enamodeLo = 0;      
        }
      
        /**
         * Returns this timer index.
         *
         * @return index of this timer, or -1 if error has been occurred.
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
            if( not isConstructed_ ) return 0; 
            return timerClock_;
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
                case 0: 
                    return TINTLO0;
                    
                case 1: 
                    return TINTLO1;
            }
            return -1;
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
            cpuClock_ = config.cpuClock;
            for(int32 i=0; i<RESOURCES_NUMBER; i++) 
            {
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
            if( not isConstructed_ ) return false;
            if( not isIndex(index) ) return false; 
            do
            {
                if(lock_[index] == true)
                {
                    break;
                }
                uint32 addr;
                switch(index)
                {
                    case 0: 
                        addr = reg::Timer::ADDRESS0; 
                        break;
                        
                    case 1: 
                        addr = reg::Timer::ADDRESS1; 
                        break;
                        
                    default: 
                        addr = 0; 
                        break;
                }    
                if(addr == 0) 
                {
                    break;
                }        
                regTim_ = new (addr) reg::Timer();
                // Set the timer emulation mode
                regTim_->emumgtClkspd.bit.free = 0;
                regTim_->emumgtClkspd.bit.soft = 0;
                // Disable watchdog
                regTim_->wdtcr.bit.wden = 0;
                // Set the timer clock
                if(regTim_->emumgtClkspd.bit.clkdiv == 0)
                {
                    break;
                }
                timerClock_ = cpuClock_ / static_cast<int64>(regTim_->emumgtClkspd.bit.clkdiv);
                // Set Timer Control Register
                regTim_->tcr.value = 0;
                regTim_->tcr.bit.clksrcLo = 0;
                regTim_->tcr.bit.tienLo = 0; 
                regTim_->tcr.bit.enamodeLo = 0;
                // Set Timer Global Control Register
                regTim_->tgcr.value = 0;
                regTim_->tgcr.bit.timmode = 0;
                regTim_->tgcr.bit.timhirs = 1;
                regTim_->tgcr.bit.timlors = 1;
                index_ = index;
                lock_[index_] = true;
                setPeriod();
                setCount(0);        
            }
            while(false);
            return index_ >= 0 ? true : false;    
        }
        
        /** 
         * Tests .
         *
         * @param index a timer index.
         * @return boolean result.
         */  
        bool isIndex(int32 index)
        {
            return 0 <= index && index < RESOURCES_NUMBER ? true : false;
        }
        
        /**
         * Tests if this timer is counting.
         *
         * @return true if this timer is counting.
         */        
        bool isStarted()
        {
            return regTim_->tcr.bit.enamodeLo == 0 ? false : true;
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
        static const int32 IS_INITIALIZED = 0x95633217;        
      
        /**
         * Number of HW timers.
         */
        static const int32 RESOURCES_NUMBER = 2;
        
        /**
         * The module has been initialized successfully (no boot).
         */
        static int32 isInitialized_;        
        
        /**
         * CPU clock rate in Hz (no boot).
         */      
        static int64 cpuClock_;
        
        /**
         * Locked by some object flag of each HW timer (no boot).
         */    
        static bool lock_[RESOURCES_NUMBER];

        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        
        
        /**
         * The timer internal clock in Hz.
         */  
        int64 timerClock_;
      
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
     * The module has been initialized successfully (no boot).
     */
    int32 TimerController::isInitialized_;    
  
    /**
     * CPU clock rate in Hz (no boot).
     */      
    int64 TimerController::cpuClock_;  
  
    /**
     * Locked by some object flag of each HW timer (no boot).  
     */
    bool TimerController::lock_[TimerController::RESOURCES_NUMBER];
    
}
#endif // MODULE_TIMER_CONTROLLER_HPP_
