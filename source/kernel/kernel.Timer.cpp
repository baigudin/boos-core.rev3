/** 
 * Hardware timer resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Timer.hpp"
#include "kernel.Kernel.hpp" 
#include "driver.Timer.hpp"

namespace kernel
{
    /** 
     * Constructor.
     *
     * Construct Timer object and alloc first free HW timer.
     */
    Timer::Timer() : Parent(),
        isConstructed_ (getConstruct()),    
        driver_ (NULL){
        setConstruct( construct(NULL) );    
    }
  
    /** 
     * Constructor.
     *
     * @param available timer index.
     */
    Timer::Timer(int32 index) : Parent(),
        isConstructed_ (getConstruct()),        
        driver_ (NULL){
        setConstruct( construct(&index) );
    }
    
    /** 
     * Destructor.
     */
    Timer::~Timer()
    {
        delete driver_;
    }
    
    /**
     * Constructor.
     *
     * @param index available timer index.
     * @return true if object has been constructed successfully.
     */
    bool Timer::construct(int32* index)
    {
        if( not isConstructed_ ) return false;
        ::driver::Timer::Resource res;
        if(index != NULL) 
        {
            res.index = *index;
        }
        else 
        {
            res.index = -1;    
        }  
        driver_ = ::driver::Timer::create(res);
        return driver_ != NULL ? driver_->isConstructed() : false;
    }
    
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Timer::isConstructed() const
    {
        return isConstructed_;
    } 
    
    /**
     * Gets this timer period.
     *
     * @return timer period register value.
     */      
    int64 Timer::getPeriod() const
    {
        return isConstructed_ ? driver_->getPeriod() : 0;
    }  
    
    /**
     * Sets this timer period.
     *
     * @param us timer period in microseconds, zero is set period to maxinum value.
     */      
    void Timer::setPeriod(int64 us)
    {
        if( isConstructed_ ) driver_->setPeriod(us);  
    }
    
    /**
     * Gets this timer counter.
     *
     * @return timer counter register value.   
     */      
    int64 Timer::getCount() const
    {
        return isConstructed_ ? driver_->getCount() : 0;
    }
    
    /**
     * Sets this timer counter.
     *
     * @param count timer counter register value.
     */      
    void Timer::setCount(int64 count)
    {
        if( isConstructed_ ) driver_->setCount(count);  
    }      
    
    /**
     * Starts this timer count.
     */        
    void Timer::start()
    {
        if( isConstructed_ ) driver_->start();  
    }
        
    /**
     * Stops this timer count.
     */      
    void Timer::stop()
    {
        if( isConstructed_ ) driver_->stop();  
    }
    
    /**
     * Returns this timer index.
     *
     * @return index of this timer, or -1 if error has been occurred.
     */
    int32 Timer::getIndex() const
    {
        return isConstructed_ ? driver_->getIndex() : -1;
    }
    
    /** 
     * Returns timer developing interface.
     *
     * @return timer developing interface.
     */  
    ::driver::Timer& Timer::getDriver() const
    {
        if( not isConstructed_ ) Kernel::getKernel().getRuntime().terminate(-1);
        return *driver_;
    }
}
