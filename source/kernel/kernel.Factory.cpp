/**
 * Factory of an operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Factory.hpp"

namespace kernel
{
    /** 
     * Constructor.
     */    
    Factory::Factory() : Parent(),
        isConstructed_ (getConstruct()){    
        setConstruct( construct() );    
    }
  
    /** 
     * Destructor.
     */      
    Factory::~Factory()
    {
    }
        
    /**
     * Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */    
    bool Factory::isConstructed() const
    {
        return isConstructed_;  
    }
    
    /**
     * Creates new interrupt resource.
     *
     * @param handler user class which implements an interrupt handler interface.
     * @param source  available interrupt source number.
     * @return new interrupt resource.
     */  
    ::api::Interrupt* Factory::createInterrupt(::api::Task& handler, int32 source)
    {
        return NULL;
    }
    
    /**
     * Constructor.
     *
     * @return true if object has been constructed successfully.   
     */
    bool Factory::construct()
    {
        if( not isConstructed_ ) return false;
        return true;
    }
}
