/** 
 * Target processor resource. 
 *
 * The class describes a skeleton implementation of a processor resource.
 * It should be inherited by all classes, which aim expanding the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_PROCESSOR_RESOURCE_HPP_
#define BOOS_DRIVER_PROCESSOR_RESOURCE_HPP_

#include "boos.Object.hpp"
#include "boos.driver.Processor.hpp"

namespace driver
{
  class ProcessorResource : public ::Object<>, public ::driver::Processor
  {
    typedef ::Object<>  Parent;
    
  public:
  
    /** 
     * Constructor.
     */     
    ProcessorResource() : Parent(),
      isConstructed_ (getConstruct()){
    }    
  
    /** 
     * Destructor.
     */                               
    virtual ~ProcessorResource()
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
    
  protected:
    
    /** 
     * The root object constructed flag.
     */  
    const bool& isConstructed_;
    
  private:
  
    /**
     * Copy constructor.
     *
     * @param obj reference to source object.
     */
    ProcessorResource(const ProcessorResource& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    ProcessorResource& operator =(const ProcessorResource& obj);      

  };
}
#endif // BOOS_DRIVER_PROCESSOR_RESOURCE_HPP_
