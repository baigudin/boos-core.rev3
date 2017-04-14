/** 
 * Target processor registers factory.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_DRIVER_REGISTER_HPP_
#define BOOS_DRIVER_REGISTER_HPP_

#include "boos.api.Object.hpp"
#include "boos.api.Stack.hpp"
#include "boos.api.Toggle.hpp"
#include "boos.Configuration.hpp"

namespace driver
{
  class Register : public ::api::Object
  {
    
  public:
    
    /** 
     * Destructor.
     */    
    virtual ~Register(){}
  
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
    virtual void initialize(::api::Stack<int64>& stack, int32 entry, int32 arg1, int32 arg2) = 0;
  
    /** 
     * Returns a pointer to the first register of CPU registers context.
     *
     * @return memory address of registers order, or NULL if error has been occurred.
     */    
    virtual void* registers() = 0;
  
    /**
     * Returns the register interface of a target processor.
     *
     * @return target processor register interface, or NULL if error has been occurred.
     */
    static ::driver::Register* create();

    /** 
     * Allows an access to protected memory mapped CPU registers.
     */    
    static void allow();
    
    /** 
     * Protects an access to protected memory mapped CPU registers.
     */    
    static void protect();    
    
    /**
     * Initializes the driver.
     *
     * @param config a target processor configuration.
     * @return true if no errors have been occurred.
     */   
    static bool init(const ::Configuration config);
    
    /**
     * Deinitializes the driver.
     */
    static void deinit();    
    
  };
}
#endif // BOOS_DRIVER_REGISTER_HPP_
