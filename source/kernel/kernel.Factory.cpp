/**
 * Factory of an operating system kernel.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "kernel.Factory.hpp"
#include "kernel.FactoryCreator.hpp"

namespace kernel
{
    /**
     * Returns a factory of an operating system kernel.
     *
     * @return a kernel factory, or NULL if error has been occurred.
     */
    ::kernel::Factory* Factory::create()
    {
        Factory* factory = new FactoryCreator();
        if(factory == NULL) return NULL; 
        if(factory->isConstructed()) return factory;       
        delete factory;
        return NULL;       
    }
}
