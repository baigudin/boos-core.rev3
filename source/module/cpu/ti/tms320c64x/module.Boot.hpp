/** 
 * Boot routine.
 *
 * The module performs the tasks to initialize C/C++ run-time environment
 * and calls the operating system main method.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef MODULE_BOOT_HPP_
#define MODULE_BOOT_HPP_

#include "Types.hpp"

namespace module
{
    class Boot
    {
  
    public:
    
        /**
         * Initialization record in .cinit section.
         */    
        struct CRecord
        {
            /**
             * The size of the initialization data in bytes.
             */
            int32 size;
            
            /**
             * The starting address of the area within the .bss section.
             */
            cell* addr;
            
            /**
             * The data of a variable.
             */
            cell data[1];
          
        };  
        
        /**
         * Initialization record in .pinit section.
         */    
        struct PRecord
        {
            /**
             * Address of constructor.
             */
            void (*constructor)();
          
        };
        
        /**
         * Initialization.
         *
         * @return true if no errors have been occurred.
         */
        static bool initialize();
      
        /**
         * Deinitialization.
         */
        static void deinitialize(); 
      
    private:   
    
        /**
         * Returns the first record adderess.
         * 
         * @return memory address of .cinit section or NULL.
         */
        static CRecord* getCRecord();
        
        /**
         * Returns the next record adderess.
         * 
         * @param record the record address for getting next record after this.
         * @return memory address of the next record or NULL.
         */
        static CRecord* getCRecord(CRecord* record);
      
        /**
         * Returns the first record adderess.
         * 
         * @return memory address of .pinit section or NULL.
         */
        static PRecord* getPRecord();
        
        /**
         * Returns the next record adderess.
         * 
         * @param record the record address for getting next record after this.
         * @return memory address of the next record or NULL.
         */
        static PRecord* getPRecord(PRecord* record);
  
    };
}
#endif // MODULE_BOOT_HPP_
