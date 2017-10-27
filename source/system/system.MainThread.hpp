/** 
 * User main thread class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef SYSTEM_MAIN_THREAD_HPP_
#define SYSTEM_MAIN_THREAD_HPP_

#include "system.Thread.hpp"

namespace system
{
    /**
     * User main thread.
     */ 
    class MainThread : public ::system::Thread
    {
        typedef ::system::Thread Parent;
      
    public:
    
        /** 
         * Constructor.
         */
        MainThread() : Parent(),
            error_ (-1){
        }
        
        /** 
         * Destructor.
         */
        virtual ~MainThread()
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
        int32 error()
        {
            return error_;
        }    
      
    private:
      
        /**
         * Copy constructor.
         *
         * @param obj reference to source object.
         */
        MainThread(const MainThread& obj);
        
        /**
         * Assignment operator.
         *
         * @param obj reference to source object.
         * @return reference to this object.     
         */
        MainThread& operator =(const MainThread& obj);      
        
        /**
         * Execution error.
         */
        int32 error_;
      
    };
}
#endif // SYSTEM_MAIN_THREAD_HPP_
