/** 
 * User main class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "Main.hpp"
#include "system.Thread.hpp"
#include "system.Mutex.hpp"
#include "system.Semaphore.hpp"
#include "system.System.hpp"

/**
 * User thread class.
 */   
class Thread : public ::system::Thread
{
  
public:
  
  /** 
   * Constructor.
   *
   * @param sem   a semaphore of critical area.
   * @param index an index of this thread.   
   * @param time  some working time in critical section in seconds.  
   * @param name  a name of this thread.
   */
  Thread(::api::Semaphore& sem, int32 index, int32 permits, int32 time) :
    sem_     (sem),
    index_   (index),    
    permits_ (permits),    
    time_    (time * 1000){
  }
  
  /**
   * Destructor.
   */
  virtual ~Thread()
  {
  }
  
  /**
   * The main method of this thread.
   */  
  void main()
  {
    volatile bool exe = true;
    while(exe) 
    {
      sem_.acquire(permits_);
      Thread::sleep(time_);
      sem_.release(permits_);
    }
  }
  
  /**
   * The semaphore of critical area.
   */
  ::api::Semaphore& sem_;
  
  /**
   * The index of this thread.
   */
  int32 index_;
  
  /**
   * The permits of this thread.
   */
  int32 permits_;    
  
  /**
   * The working time in critical area in seconds.
   */
  int32 time_;

};

/**
 * User method which will be stated as first.
 *
 * @return error code or zero.
 */   
int32 Main::main()
{
  // Create and check one semaphore of all threads
  ::system::Semaphore sem(2, true);
  if(!sem.isConstructed()) return 1;
  // Create the threads
  Thread thr1(sem, 1, 2, 5);
  Thread thr2(sem, 2, 1, 2);  
  Thread thr3(sem, 3, 1, 1);  
  // Check the threads
  if(!thr1.isConstructed() || 
     !thr2.isConstructed() || 
     !thr3.isConstructed()) return 1;
  // Start the threads
  thr1.start();  
  thr2.start();
  thr3.start();  
  // Wait the threads will be completed
  thr1.join();
  thr2.join();  
  thr3.join();    
  return 0;
}
