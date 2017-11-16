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
    class String : public ::api::Collection<Char>
    {
      
    public:
    
        /**
         * Destructor.
         */
        virtual ~String(){}
        
        /** 
         * Compares two strings lexicographically.
         *
         * @param obj a string object.
         * @return the value 0 if given string is equal to this string; 
         *         a value less than 0 if this string is less than given string; 
         *         a value greater than 0 if this string is greater than given string.
         */
        virtual int32 compareTo(const ::api::String<Char>& obj) const = 0;        
        
        /** 
         * Compares two strings lexicographically.
         *
         * @param data a sequence of string characters.
         * @return the value 0 if given string is equal to this string; 
         *         a value less than 0 if this string is less than given string; 
         *         a value greater than 0 if this string is greater than given string.
         */
        virtual int32 compareTo(const Char* data) const = 0;
        
        /**
         * Returns pointer to the first char of containing string.
         *
         * NOTE: Be careful, some action with the object might relocate internal buffer 
         * that contains characters. By this reason, a returned address will be actual 
         * until you do not call no constant method of the object.
         *
         * @param first char of containing string characters, or NULL if no string contained.
         */
        virtual const Char* getChar() const = 0;        
  
    };
}
#endif // API_STRING_HPP_
