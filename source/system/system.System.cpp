/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"

namespace system
{
    /**
     * Current value of the running system in milliseconds.
     *
     * @return time in milliseconds.
     */  
    int64 System::getTimeMs()
    {
        return getTimeNs() / 1000000;
    }
  
    /**
     * Current value of the running system in nanoseconds.
     *
     * @return time in nanoseconds.
     */  
    int64 System::getTimeNs()
    {
        return isInitialized() ? kernel_->getExecutionTime().getValue() : 0;
    }
    
    /**
     * Returns an kernel factory of the operating system.
     *
     * @return a kernel factory.
     */
    ::api::Kernel& System::getKernel()
    {
        if( not isInitialized() ) terminate();
        return *kernel_;
    }
    
    /**
     * Terminates the operating system execution.
     */
    void System::terminate()
    {
        kernel_->getRuntime().terminate(-1);
    }
    
    /**
     * Initialization.
     *
     * @param kernel a kernel resources factory.     
     * @return true if no errors.
     */
    bool System::initialize(::api::Kernel& kernel)
    {
        isInitialized_ = 0;
        stage_ = 0;        
        // Stage 1: Create the operating system tick timer
        stage_++;        
        kernel_ = &kernel;
        if(kernel_ == NULL || not kernel_->isConstructed() )  return false;
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;        
        return true;
    }
    
    /**
     * Deinitialization.
     */
    void System::deinitialize()
    {
        switch(stage_)
        {
            default:
            case  1: 
            {
            }          
            case  0: 
            {
                break;
            }
        }
        isInitialized_ = 0;     
    }
    
    /**
     * Tests if the module has been initialized.
     *
     * @return true if the module has been initialized successfully.
     */    
    bool System::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }    
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 System::isInitialized_;    
    
    /**
     * The module initialization stage (no boot).
     */
    int32 System::stage_;    
    
    /**
     * A kernel factory of the operating system (no boot).
     */
    ::api::Kernel* System::kernel_;
    
}
