/** 
 * Boot routine.
 *
 * The module performs the tasks to initialize C/C++ run-time environment
 * and calls the operating system main method.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#include "module.Boot.hpp"

namespace module
{
    /**
     * Initialization.
     *
     * @return true if no errors have been occurred.
     */
    bool Boot::initialize()
    {
        #ifdef  __TI_EABI__
        return false;
        #else
        // Initialize global and static variables
        CRecord* cRecord = getCRecord();
        while(cRecord != NULL)
        {
            for(int32 i=0; i<cRecord->size; i++) 
                cRecord->addr[i] = cRecord->data[i];
            cRecord = getCRecord(cRecord);
        }
        // Call global C++ class default constructors
        PRecord* pRecord = getPRecord();
        while(pRecord != NULL)
        {
            pRecord->constructor();
            pRecord = getPRecord(pRecord);
        }    
        return true;    
        #endif
    }
    
    /**
     * Deinitialization.
     */
    void Boot::deinitialize()
    {
    }
    
    /**
     * Returns the next record adderess.
     * 
     * @param record the record address for getting next record after this.
     * @return memory address of the next record or NULL.
     */
    Boot::CRecord* Boot::getCRecord(Boot::CRecord* record)
    {
        const int32 align = 0x3;
        int32 size = (record->size + align) & ~align;    
        record = reinterpret_cast<CRecord*>(&record->data[size]);
        return record->size != 0 ? record : NULL;
    }
  
    /**
     * Returns the next record adderess.
     * 
     * @param record the record address for getting next record after this.
     * @return memory address of the next record or NULL.
     */
    Boot::PRecord* Boot::getPRecord(Boot::PRecord* record)
    {
        record = record + 1;
        return record->constructor != NULL ? record : NULL;
    }  
}
