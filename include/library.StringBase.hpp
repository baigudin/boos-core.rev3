/** 
 * Base string class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef LIBRARY_STRING_BASE_HPP_
#define LIBRARY_STRING_BASE_HPP_

#include "Object.hpp"
#include "api.String.hpp"

namespace library
{
    /** 
     * @param Char data type of string characters.
     * @param Alloc heap memory allocator class.
     */
    template <typename Char, class Alloc=::Allocator>    
    class StringBase : public Object<Alloc>, public ::api::String<Char>
    {
        typedef ::Object<Alloc> Parent;        
      
    public:
    
        /** 
         * Constructor.
         */    
        StringBase() : Parent(),
            isConstructed_ (this->getConstruct()),
            chars_         (NULL),
            length_        (0),
            illegal_       (0){
            this->setConstruct( construct("") );
        }
        
        /** 
         * Constructor.
         *
         * @param chars a sequence of string characters.
         */    
        StringBase(const Char* chars) : Parent(),
            isConstructed_ (this->getConstruct()),
            chars_         (NULL),
            length_        (-1),
            illegal_       (0){
            this->setConstruct( construct(chars) );
        }        
        
        /** 
         * Copy constructor.
         *
         * @param obj a source object.
         */ 
        StringBase(const StringBase& obj) : Parent(obj),
            isConstructed_ (this->getConstruct()),        
            chars_         (NULL),
            length_        (-1),
            illegal_       (0){
            this->setConstruct( construct(obj.chars_) );
        }            
    
        /**
         * Destructor.
         */
        virtual ~StringBase()
        {
            this->free(chars_);
        }
        
        /** 
         * Assignment operator.
         *
         * @param chars a sequence of string characters.
         * @return reference to this object.       
         */     
        StringBase& operator =(const Char* chars)
        {
            Parent::operator=(*this);
            if( isConstructed_ ) assign(chars);
            return *this;
        }         
        
        
        /** 
         * Assignment operator.
         *
         * @param obj a source object.
         * @return reference to this object.       
         */     
        StringBase& operator =(const StringBase& obj)
        {
            Parent::operator=(*this);
            if( isConstructed_ ) assign(obj.chars_);            
            return *this;
        }        
        
        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */    
        virtual bool isConstructed() const
        {
            return isConstructed_;
        }
        
        /**
         * Returns pointer to the first char of containing string.
         *
         * @param first char of containing string or NULL if no string contained.
         */
        virtual const Char* getChar() const
        {
            return isConstructed_ ? chars_ : NULL;
        }
        
        /**
         * Returns a number of elements in this container.
         *
         * @return number of elements.
         */
        virtual int32 getLength() const
        {
            return isConstructed_ ? length_.cur : 0;
        }
       
        /**
         * Tests if this collection has elements.
         *
         * @return true if this collection does not contain any elements.
         */
        virtual bool isEmpty() const
        {
            return getLength() == 0 ? true : false;
        }
        
        /**
         * Returns illegal element which will be returned as error value.
         *
         * @return illegal element.
         */
        virtual Char getIllegal() const
        {
            return illegal_;
        }
        
        /**
         * Sets illegal element which will be returned as error value.
         *
         * @param value illegal value.
         */
        virtual void setIllegal(Char value)
        {
            if( isConstructed_ ) illegal_ = value;
        }
        
        /**
         * Tests if given value is an illegal.
         *
         * @param value testing value.
         * @param true if value is an illegal.
         */
        virtual bool isIllegal(const Char& value) const
        {
            return illegal_ == value ? true : false;
        }
        
    private:
    
        /**
         * Constructor new object.
         *
         * @param chars a sequence of string characters.
         * @return true if object has been constructed successfully.
         */
        bool construct(const Char* chars)
        {
            if( not isConstructed_ ) return false;
            return assign(chars);
        }
        
        
        /** 
         * Allocates a new string.
         *
         * @param str reference to String object.
         * @return true if object has been constructed successfully.
         */
        bool assign(const Char* chars)
        {
            int32 length = calculateLength(chars);          
            size_t size = static_cast<size_t>( length * sizeof(Char) + sizeof(Char) );
            // Delete current buffer            
            if(chars_ != NULL && length > length_.max) 
            {
                this->free(chars_);
                chars_ = NULL;
            }
            // Allocate new buffer
            if(chars_ == NULL)
            {
                chars_ = this->template allocate<Char*>(size);
                if(chars_ == NULL) 
                {
                    return false;
                }
                length_.max = length;
            }
            length_.cur = length;
            copy(chars);
            return true;            
        }          
        
        /** 
         * Copies a string self string.
         *
         * @param chars a sequence of string characters.
         */
        void copy(const Char* chars)
        {
            Char* d = chars_ - 1;     
            const Char* s = chars  - 1;     
            while( (*++d = *++s) != 0 );
        }

        /** 
         * Returns a characters number of passed string.
         *
         * @param chars a sequence of string characters.
         * @return characters number.         
         */
        static int32 calculateLength(const Char* chars)
        {
            if(chars == NULL) return 0;
            int32 len = 0;
            while( *chars != 0 ) 
            {
                len++;
                chars++;
            }
            return len;
        }        
    
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        

        /**
         * The first char of containing string.
         */        
        Char* chars_;

        /**
         * Number of characters of this string.
         */                 
        struct Length
        {
            /** 
             * Constructor.
             *
             * @param lenght a number of characters.
             */        
            Length(int32 lenght) :
                cur (lenght),
                max (lenght){
            }

            /**
             * Destructor.
             */
           ~Length()
            {
            }            
            
            /**
             * Current number of characters of this string.
             */                 
            int32 cur;
        
            /**
             * Max number of characters for this string.
             */                 
            int32 max;        
            
        } length_;

        /**
         * Illegal character of this string.
         */         
        Char illegal_;
        
      //friend StringBase<Char,Alloc> operator+(const StringBase<Char,Alloc>& obj1, const StringBase<Char,Alloc>& obj2);            
      //friend StringBase<Char,Alloc> operator+(const StringBase<Char,Alloc>& obj1, const Char* chars);
    };
    
    /**
     * Concatenates two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline StringBase<Char,Alloc> operator+(const StringBase<Char,Alloc>& obj1, const StringBase<Char,Alloc>& obj2)
    {
        return "";
    }
    
    /**
     * Concatenates two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline StringBase<Char,Alloc> operator+(const StringBase<Char,Alloc>& obj1, const Char* chars)
    {
        return "";
    }    
}
#endif // LIBRARY_STRING_BASE_HPP_
