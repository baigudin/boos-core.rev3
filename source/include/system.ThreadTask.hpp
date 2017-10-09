/**
 * Skeleton thread task class with default settings.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_THREAD_TASK_HPP_
#define SYSTEM_THREAD_TASK_HPP_

#include "Object.hpp"
#include "api.Task.hpp"

namespace system
{
    class ThreadTask : public ::Object<>, public ::api::Task  
    {
        typedef ::Object<> Parent;    
      
    public:
    
        /** 
         * Constructor.
         */    
        ThreadTask() : Parent(){}
        
        /** 
         * Destructor.
         */
        virtual ~ThreadTask(){}
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return this->Parent::isConstructed();
        }   
        
        /**
         * Returns size of thread stack.
         *
         * The method returns size of thread stack in bytes which should be allocated for the task.
         *
         * @return stack size in bytes.
         */  
        virtual int32 getStackSize() const
        {
            return 0x800;
        }
      
    private:    
  
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        ThreadTask(const ThreadTask& obj);
    
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        ThreadTask& operator =(const ThreadTask& obj);        
  
    };
}
#endif // SYSTEM_THREAD_TASK_HPP_
