/**
 * TI TMS320F28x3x registers.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_PROCESSOR_CONTROLLER_HPP_
#define MODULE_PROCESSOR_CONTROLLER_HPP_

#include "module.RegisterBase.hpp"

namespace module
{  
    class RegisterController : public ::module::RegisterBase
    { 
        typedef ::module::RegisterBase  Parent;
    
    public:
    
        /** 
         * Constructor.
         */  
        RegisterController() : Parent(),
            align8_ (0xb00cffffffffb00c){
            setConstruct( construct() );
        }
        
        /** 
         * Destructor.
         */    
        virtual ~RegisterController()
        {
        }
        
        /** 
         * Initializes the registers.
         *
         * @param stack a stack.
         * @param entry router entry point.
         * @param arg1  first router argument.
         * @param arg2  second router argument.     
         */  
        virtual void setInitialization(::api::Stack<int64>& stack, int32 entry, int32 arg1, int32 arg2)
        {
            if(!isConstructed_) return;
        }     
      
        /** 
         * Returns a pointer to a first register of registers.
         *
         * @return memory address of registers order.
         */    
        virtual void* getRegisters()
        {
            return NULL;
        }
      
    private:
    
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            #ifndef EOOS_DEBUG
            #else  //!EOOS_DEBUG
            #endif // EOOS_DEBUG
            return true;
        }
        
        /** 
         * Copy constructor.
         *
         * @param obj reference to source object.
         */ 
        RegisterController(const RegisterController& obj) : //Parent(obj),
            align8_ (obj.align8_){
        }    
        
        /** 
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.       
         */  
        RegisterController& operator =(const RegisterController& obj)
        {
          //Parent::operator=(obj);
            return *this;
        }
        
        /**
         * For alignment to eight on stack
         */
        int64 align8_;
      
        /**
         * CPU registers.
         *
         * IMPORTANT: The order of CPU registers must not be changed,
         * because these are used by low level interrupt routine.
         */
        int32 acc_;
        int32 p_;
        int32 xt_;
        int32 xar0_;
        int32 xar1_;
        int32 xar2_;
        int32 xar3_;
        int32 xar4_;
        int32 xar5_;
        int32 xar6_;
        int32 xar7_;
        int32 pc_;
        int32 rpc_;
        int16 st0_;
        int16 st1_;
        int16 dp_;
        int16 sp_;
        int16 ier_;    
        int16 ifr_;        
        int16 dbgier_;
        
        /**
         * FPU registers.
         *
         * IMPORTANT: The order of CPU registers must not be changed,
         * because these are used by low level interrupt routine.
         */
        int32 rb_;          
        int32 stf_;     
        int32 r0h_;
        int32 r1h_;
        int32 r2h_;
        int32 r3h_;
        int32 r4h_;
        int32 r5h_;
        int32 r6h_;
        int32 r7h_;
      
    };
}
#endif // MODULE_PROCESSOR_CONTROLLER_HPP_
