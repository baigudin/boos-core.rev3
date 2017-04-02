/** 
 * The operating system main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
#ifndef BOOS_SYSTEM_MAIN_HPP_
#define BOOS_SYSTEM_MAIN_HPP_

#include "boos.Main.hpp"
#include "boos.system.Thread.hpp"

namespace system
{
  class Main
  {
  
  public:
 
    /**
     * The method which will be stated first.
     * 
     * @return error code or zero.
     */
    static int32 main();
    
  private:
 
    /**
     * User main thread.
     */ 
 
    class Thread : public ::system::Thread
    {
      typedef ::system::Thread Parent;
      
    public:
  
      /** 
       * Constructor.
       */
      Thread() : Parent(),
        error_ (-1){
      }
  
      /** 
       * Destructor.
       */
      virtual ~Thread()
      {
      }
      
      /**
       * The method with self context.
       */  
      virtual void main()
      {
        error_ = ::Main::main();
      }
      
      /**
       * Returns execution error.
       */  
      virtual int32 error()
      {
        return error_;
      }    
      
    private:
      
      /**
       * Copy constructor.
       *
       * @param obj reference to source object.
       */
      Thread(const Thread& obj);
  
      /**
       * Assignment operator.
       *
       * @param obj reference to source object.
       * @return reference to this object.     
       */
      Thread& operator =(const Thread& obj);      
      
      /**
       * Execution error.
       */
      int32 error_;
      
    };
    
  };
}
#endif // BOOS_SYSTEM_MAIN_HPP_
