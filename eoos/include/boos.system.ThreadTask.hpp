/**
 * Skeleton thread task class with default settings.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_SYSTEM_THREAD_TASK_HPP_
#define BOOS_SYSTEM_THREAD_TASK_HPP_

#include "boos.Object.hpp"
#include "boos.api.Task.hpp"

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
    virtual int32 stackSize() const
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
#endif // BOOS_SYSTEM_THREAD_TASK_HPP_
