/**
 * The resources factory of the operating system.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_RESOURCE_HPP_
#define SYSTEM_RESOURCE_HPP_

#include "Object.hpp"
#include "api.System.hpp"

namespace system
{
    class Resource : public ::Object<>, public ::api::System
    {
        typedef ::Object<> Parent;
      
    public:
    
        /** 
         * Constructor.
         *
         * @param scheduler a kernel scheduler.
         */    
        Resource(::api::Kernel& kernel) : Parent(),
            isConstructed_ (getConstruct()),
            kernel_        (kernel){
            setConstruct( construct() );    
        }        
  
        /** 
         * Destructor.
         */
        virtual ~Resource(){}
        
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
         * Returns the operating system kernel interface.
         *
         * @return the operating system kernel interface.
         */      
        virtual ::api::Kernel& getKernel()
        {
            if( not isConstructed_ ) terminate();        
            return kernel_;
        }
        
        /**
         * Returns running time of the operating system in milliseconds.
         *
         * @return time in milliseconds.
         */
        virtual int64 getTimeMs()
        {
            return getTimeNs() / 1000000;
        }
           
        /**
         * Returns running time of the operating system in nanoseconds.
         *
         * @return time in nanoseconds.
         */
        virtual int64 getTimeNs()
        {
            return isConstructed_ ? kernel_.getExecutionTime().getValue() : 0;
        }
        
        /**
         * Terminates the operating system execution.
         *
         * @param status a termination status.
         */
        virtual void terminate()
        {
            if( not isConstructed_ ) while(true);
            kernel_.getRuntime().terminate(-1);
        }
        
    private:
    
        /**
         * Constructor.
         *
         * @return true if object has been constructed successfully.     
         */    
        bool construct()
        {
            if( not isConstructed_ ) return false;
            if( not kernel_.isConstructed() ) return false;
            return true;
        }        
        
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        Resource(const Resource& obj);
      
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        Resource& operator =(const Resource& obj);
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;
  
        /**
         * A kernel factory of the operating system (no boot).
         */
        ::api::Kernel& kernel_;
        
    };
}
#endif // SYSTEM_RESOURCE_HPP_
