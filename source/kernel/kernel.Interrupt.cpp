/** 
 * Hardware interrupt resource.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Interrupt.hpp"
#include "kernel.System.hpp"
#include "driver.Interrupt.hpp"
 
namespace kernel
{
    /**
     * Constructor.
     */
    Interrupt::Interrupt() : Parent(),
        isConstructed_ (getConstruct()),  
        driver_        (NULL){
        setConstruct( construct(NULL, 0) );
    }  
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     */
    Interrupt::Interrupt(::api::Task& handler, int32 source) : Parent(),
        isConstructed_ (getConstruct()),
        driver_        (NULL){
        setConstruct( construct(&handler, source) );
    }
    
    /**
     * Destructor.
     */
    Interrupt::~Interrupt()
    {
        delete driver_;
    }
    
    /**
     * Constructor.
     *
     * @param handler pointer to user class which implements an interrupt handler interface.   
     * @param source  available interrupt source.
     * @return true if object has been constructed successfully.
     */
    bool Interrupt::construct(::api::Task* handler, int32 source)
    {
        if( not isInitialized() ) return false;
        if( not isConstructed_ ) return false;
        ::driver::Interrupt::Resource res;
        if(handler != NULL) 
        {
            res.handler = handler;
            res.source = source;    
        }
        else 
        {
            res.handler = NULL;
            res.source = 0;
        }
        driver_ = ::driver::Interrupt::create(res);    
        return driver_ != NULL ? driver_->isConstructed() : false;
    }
  
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Interrupt::isConstructed() const
    {
        return isConstructed_;
    }
    
    /**
     * Jumps to interrupt HW vector.
     */  
    void Interrupt::jump()
    {
        if( not isConstructed_ ) return;
        driver_->jump();
    }
    
    /**
     * Clears an interrupt status of this source.
     */  
    void Interrupt::clear()
    {
        if( not isConstructed_ ) return;
        driver_->clear();  
    }
    
    /**
     * Sets an interrupt status of this source.
     */  
    void Interrupt::set()
    {
        if( not isConstructed_ ) return;
        driver_->set();  
    }  
    
    /**
     * Locks this interrupt source.
     *
     * @return an interrupt enable source bit value before method was called.
     */    
    bool Interrupt::disable()
    {
        if( not isConstructed_ ) return false;  
        return driver_->disable();
    }
    
    /**
     * Unlocks this interrupt source.
     *
     * @param status returned status by disable method.
     */
    void Interrupt::enable(bool status)
    {
        if( not isConstructed_ ) return;
        driver_->enable(status);  
    }
  
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Interrupt::initialize()
    {
        isInitialized_ = 0;
        stage_ = 0;
        // Stage 1: Create global interrupt class switching
        stage_++;
        global_ = new Global();
        if( global_ == NULL || !global_->isConstructed() ) return false;
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;
        return true;
    }
  
    /**
     * Deinitialization.
     */
    void Interrupt::deinitialize()
    {
        switch(stage_)
        {
            default:
            case  1: 
            {
                delete global_; 
                global_ = NULL;
            }
            case  0: 
            {
                break;
            }
        }
        isInitialized_ = 0;    

    }
  
    /** 
     * Returns the toggle interface for controlling global interrupts.
     *
     * @return toggle interface.
     */ 
    ::api::Toggle& Interrupt::global()
    {
        if(global_ == NULL) System::terminate();
        return *global_;
    }
    
    /** 
     * Returns interrupt developing interface.
     *
     * @return interrupt developing interface.
     */  
    ::driver::Interrupt& Interrupt::getDriver()
    {
        if( not isConstructed_ ) System::terminate();
        return *driver_;
    }
    
    
    /** 
     * Disables all maskable interrupts.
     *
     * @return global interrupt enable bit value before method was called.
     */ 
    bool Interrupt::Global::disable()
    {
        return ::driver::Interrupt::disableAll();
    }
    
    /** 
     * Enables all maskable interrupts.
     *
     * @param status returned status by disable method.
     */    
    void Interrupt::Global::enable(bool status)
    {
        ::driver::Interrupt::enableAll(status);  
    }
    
    /**
     * Tests if the module has been initialized.
     *
     * @return true if the module has been initialized successfully.
     */    
    bool Interrupt::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 Interrupt::isInitialized_;    
    
    /**
     * The module initialization stage (no boot).
     */
    int32 Interrupt::stage_;
    
    /**    
     * Hardware global interrupt controller (no boot).
     */
    Interrupt::Global* Interrupt::global_;
}
