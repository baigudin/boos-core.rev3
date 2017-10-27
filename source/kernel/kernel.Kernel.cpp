/** 
 * Kernel class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Kernel.hpp"
#include "kernel.Resource.hpp"

namespace kernel
{
    /** 
     * Returns a kernel factory.
     *
     * @return a kernel factory.
     */      
    ::api::Kernel& Kernel::getKernel()
    {
        if( not isInitialized() ) while(true);
        return *kernel_;    
    }
    
    /**
     * Initialization.
     *
     * @return true if no errors.
     */
    bool Kernel::initialize()
    {
        isInitialized_ = 0;
        stage_ = 0;
        global_ = NULL;
        kernel_ = NULL;
        // Stage 1: Create the kernel resource factory
        kernel_ = new Resource();
        if(kernel_ == NULL || not kernel_->isConstructed()) return false;                
        // Stage 3: Set heap interrupt controller
        stage_++;        
        ::api::Heap* heap = ::Allocator::getHeap();
        if(heap == NULL || not heap->isConstructed()) return false;
        global_ = &kernel_->getGlobalInterrupt();
        heap->setToggle(global_);  
        // Stage complete
        stage_ = -1;
        isInitialized_ = IS_INITIALIZED;        
        return true;
    }
    
    /**
     * Deinitialization.
     */
    void Kernel::deinitialize()
    {
        switch(stage_)
        {
            default:
            case 2:             
            {
                global_ = NULL;            
            }
            case 1:
            {
                delete kernel_;
                kernel_ = NULL;
            }            
            case 0: 
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
    bool Kernel::isInitialized()
    {
        return isInitialized_ != IS_INITIALIZED ? false : true;
    }    
    
    /**
     * The module has been initialized successfully (no boot).
     */
    int32 Kernel::isInitialized_;    
    
    /**
     * The module initialization stage (no boot).
     */
    int32 Kernel::stage_;    
  
    /**
     * Global interrupt resource (no boot).
     */
    ::api::Toggle* Kernel::global_;  
    
    /**
     * The kernel factory resource (no boot).
     */
    ::api::Kernel* Kernel::kernel_;    

}
