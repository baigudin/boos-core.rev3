/** 
 * String interface.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef API_STRING_HPP_
#define API_STRING_HPP_

#include "api.Collection.hpp"

namespace api
{
    /** 
     * @param Char data type of string chars.
     */ 
    template <typename Char>
    class String  : public ::api::Collection<Char>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~String(){}
        
        /**
         * Returns pointer to the first char of containing string.
         *
         * @param first char of containing string or NULL if no string contained.
         */
        virtual const Char* getChar() const = 0;
  
    };
}
#endif // API_STRING_HPP_
