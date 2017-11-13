/** 
 * System class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "system.System.hpp"
#include "system.Resource.hpp"

namespace system
{
    /** 
     * Returns the operating system syscall interface.
     *
     * @return the operating system syscall interface.
     */   
    ::api::System& System::call()
    {
        if( not isInitialized() ) while(true);
        return *system_;    
    }

    /**
     * Initializes the operating system.
     *
     * @param kernel a kernel resources factory.              
     * @return true if no errors have been occurred.
     */   
    bool System::initialize(::api::Kernel& kernel)
    {
        isInitialized_ = 0;
        stage_ = 0;
        system_ = 0;        
        // Stage 1: Create the kernel resource factory
        stage_++;
        system_ = new Resource(kernel);
        if(system_ == NULL || not system_->isConstructed()) return false; 
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;        
        return true;
    }
    
    /**
     * Deinitializes the operating system.
     */
    void System::deinitialize()
    {
        switch(stage_)
        {
            default:
            case 1: 
                delete system_;
                system_ = NULL;            

            case 0: 
                break;
        }
        isInitialized_ = 0;     
    }
    
    /**
     * Tests if the operating system has been initialized.
     *
     * @return true if the operating system has been initialized successfully.
     */        
    bool System::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }    
    
    /**
     * The operating system has been initialized successfully (no boot).
     */
    int32 System::isInitialized_;    
    
    /**
     * The operating system initialization stage (no boot).
     */
    int32 System::stage_;    

    /**
     * The operating system factory resource (no boot).
     */
    ::api::System* System::system_;

}
