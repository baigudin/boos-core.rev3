/** 
 * Target processor register factory. 
 *
 * The class describes a skeleton implementation of CPU register resource.
 * It should be inherited by all classes, which aim expanding the implementation. 
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef DRIVER_REGISTER_RESOURCE_HPP_
#define DRIVER_REGISTER_RESOURCE_HPP_

#include "Object.hpp"
#include "driver.Register.hpp"

namespace driver
{
  class RegisterResource : public ::Object<>, public ::driver::Register
  {
    typedef ::Object<>  Parent;
    
  public:
  
    /** 
     * Constructor.
     */     
    RegisterResource() : Parent(),
      isConstructed_ (getConstruct()){
    }    
  
    /** 
     * Destructor.
     */                               
    virtual ~RegisterResource()
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
     * Initializes the CPU registers.
     *
     * Usually, this method is used for normally restoring 
     * from some interrupt service routines. 
     *
     * @param stack a stack.
     * @param entry router entry point.
     * @param arg1  first router argument.
     * @param arg2  second router argument.     
     */  
    virtual void initialize(::api::Stack<int64>& stack, int32 entry, int32 arg1, int32 arg2)
    {
    }
  
    /** 
     * Returns a pointer to the first register of CPU registers context.
     *
     * @return memory address of registers order, or NULL if error has been occurred.
     */    
    virtual void* registers()
    {
      return NULL;
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
    RegisterResource(const RegisterResource& obj);

    /**
     * Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.     
     */
    RegisterResource& operator =(const RegisterResource& obj);      

  };
}
#endif // DRIVER_REGISTER_RESOURCE_HPP_
