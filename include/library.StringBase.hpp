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
        typedef ::library::StringBase<Char,Alloc>  Self;
        typedef ::Object<Alloc>                    Parent;        
      
    public:
    
        /** 
         * Constructor.
         */    
        StringBase() : Parent(),
            isConstructed_ (this->getConstruct()),
            string_        (),
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
            string_        (),
            illegal_       (0){
            this->setConstruct( construct(chars) );
        }        
        
        /** 
         * Copy constructor.
         *
         * @param obj a source string object.
         */ 
        StringBase(const StringBase& obj) : Parent(obj),
            isConstructed_ (this->getConstruct()),        
            string_        (),
            illegal_       (0){
            this->setConstruct( construct(obj) );
        }            
    
        /**
         * Destructor.
         */
        virtual ~StringBase()
        {
        }
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object.
         * @return reference to this object.       
         */     
        StringBase& operator=(const StringBase& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( assign(obj) );
            return *this;            
        }        
        
        /** 
         * Assignment operator.
         *
         * @param chars a sequence of string characters.
         * @return reference to this object.       
         */     
        StringBase& operator=(const Char* chars)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( assign(chars) );
            return *this;        
        }
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object.
         * @return reference to this object.       
         */     
        StringBase& operator+=(const StringBase& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( concatenate(obj) );
            return *this; 
        }          
        
        /** 
         * Assignment operator.
         *
         * @param chars a sequence of string characters.
         * @return reference to this object.       
         */     
        StringBase& operator+=(const Char* chars)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( concatenate(chars) );
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
            return isConstructed_ ? string_.getBuffer() : NULL;
        }
        
        /** 
         * Compares two strings lexicographically.
         *
         * @param obj a string object.
         * @return the value 0 if given string is equal to this string; 
         *         a value less than 0 if this string is less than given string; 
         *         a value greater than 0 if this string is greater than given string.
         */
        virtual int32 compareTo(const ::api::String<Char>& obj) const
        {
            if( not isConstructed_ ) return -1;
            if( not obj.isConstructed() ) return 1;
            return string_.compareTo( obj.getChar() );
        }          
        
        /**
         * Returns a number of elements in this container.
         *
         * @return number of elements.
         */
        virtual int32 getLength() const
        {
            return isConstructed_ ? string_.getLength() : 0;
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
         * Constructs this object.
         *
         * @param obj a source string object.
         * @return true if object has been constructed successfully.         
         */ 
        bool construct(const StringBase& obj)
        {
            if( not obj.isConstructed_ ) return false;            
            return construct( obj.string_.getBuffer() );
        }    
    
        /**
         * Constructs this object.
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
         * Assigns a new string.
         *
         * @param obj a source string object.
         * @return true if the task has been completed successfully.
         */
        bool assign(const StringBase& obj)
        {
            if( not obj.isConstructed_ ) return false;
            return assign( obj.string_.getBuffer() );
        }
        
        /** 
         * Assigns a new string.
         *
         * @param chars a sequence of string characters.
         * @return true if the task has been completed successfully.
         */
        bool assign(const Char* chars)
        {
            return string_.copy(chars);
        }
        
        /** 
         * Concatenates self string and new string.
         *
         * @param obj a source string object.
         * @return true if the task has been completed successfully.
         */
        bool concatenate(const StringBase& obj)
        {
            if( not obj.isConstructed_ ) return false;
            return concatenate( obj.string_.getBuffer() );
        }                
        
        /** 
         * Concatenates self string and new string.
         *
         * @param str reference to String object.
         * @return true if the task has been completed successfully.
         */
        bool concatenate(const Char* chars)
        {
            return string_.concatenate(chars);
        }
        
        /** 
         * The root object constructed flag.
         */  
        const bool& isConstructed_;        

        /**
         * Number of characters of this string.
         */                 
        class StringData
        {
        
        public:
        
            /** 
             * Constructor.
             */        
            StringData() :
                buf_ (NULL),
                len_ (0),
                max_ (0){
            }

            /**
             * Destructor.
             */
           ~StringData()
            {
                deleteBuffer(buf_);
            }  
            
            /** 
             * Copies a string self string.
             *
             * @param buf a sequence of string characters.
             */
            bool copy(const Char* buf)
            {
                if(buf == NULL) return false;            
                int32 len, max;
                len = getLength(buf);
                if( not isFit(len) ) 
                {
                    deleteBuffer(buf_);
                    max_ = 0;
                }
                if(buf_ == NULL)
                {
                    buf_ = createBuffer(len, max);
                    max_ = max;
                }
                if(buf_ == NULL) return false;                
                len_ = len;
                copy(buf_, buf);
                return true;
            } 
            
            /** 
             * Concatenates two strings.
             *
             * @param buf a sequence of string characters.             
             */
            bool concatenate(const Char* buf)
            {
                if(buf == NULL) return false;            
                if(buf_ == NULL) return false;
                int32 len, max;
                len = getLength(buf) + len_;          
                if( not isFit(len) ) 
                {
                    Char* tmp = createBuffer(len, max);
                    if(tmp != NULL)
                    {
                        copy(tmp, buf_);
                    }
                    deleteBuffer(buf_);
                    buf_ = tmp;
                    max_ = max;                    
                }
                if(buf_ == NULL) return false;                
                len_ = len;
                concatenate(buf_, buf);                    
                return true;
            }
            
            /** 
             * Compares two strings lexicographically.
             *
             * @param buf a sequence of string characters.
             * @return the value 0 if given string is equal to this string; 
             *         a value less than 0 if this string is less than given string; 
             *         a value greater than 0 if this string is greater than given string.
             */
            int32 compareTo(const Char* buf) const
            {
                return -1;
            }
            
            /**
             * Get pointer to buffer.
             *
             * @return pointer to buffer, or NULL.
             */
            const Char* getBuffer() const
            {
                return buf_;
            }
            
            /**
             * Gets length of string.
             *
             * @return length of string.
             */
            int32 getLength() const
            {
                return len_;
            }                                              
            
        private:
        
            /** 
             * Tests if given length fits to current buffer.
             *
             * @param len string characters number.
             * @return true if the length will be fit successfully.
             */        
            bool isFit(int32 len)
            {
                return len > max_ ? false : true;
            }        
        
            /** 
             * Creates a new buffer for string.
             *
             * @param len string characters number.
             * @return the buffer address.
             */        
            static Char* createBuffer(int32 len, int32& max)
            {
                int32 size = calculateSize(len);
                Char* buf = reinterpret_cast<Char*>( Alloc::allocate(size) );
                max = buf != NULL ? calculateLength(size) : 0;
                return buf;
            }        
            
            /** 
             * Deletes the buffer.
             */        
            static void deleteBuffer(Char*& buf)
            {
                if(buf != NULL) Alloc::free(buf);
                buf = NULL;
            }            
            
            /** 
             * Returns size in byte of a string length.
             *
             * @param length string characters number.
             * @return size in byte for given string.
             */
            static int32 calculateSize(int32 len)
            {
                size_t size = static_cast<size_t>(len) * sizeof(Char) + sizeof(Char);
                // Align size to eight
                if(size & 0x7) size = (size & ~0x7) + 0x8;
                return static_cast<int32>(size);
            }
            
            /** 
             * Returns a string length of size in byte.
             *
             * @param size size in byte.
             * @return characters number.
             */
            static int32 calculateLength(int32 size)
            {
                int32 charSize =  static_cast<int32>( sizeof(Char) );
                if(charSize == 0) return 0;
                int32 len = size / charSize;
                return len > 1 ? len - 1 : 0;
            }
            
            /** 
             * Returns a characters number of passed string.
             *
             * @param chars a sequence of string characters.
             * @return characters number.
             */
            static int32 getLength(const Char* chars)
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
             * Copys string to string.
             */
            static Char* copy(Char* dst, const Char* src)
            {
              if(dst == NULL || src == NULL) return NULL;
              Char* d = dst - 1;     
              const Char* s = src  - 1;     
              while(*++d = *++s);
              return dst;
            }

            /** 
             * Concatenates two strings.
             */
            static Char* concatenate(Char* ptr1, const Char* ptr2)
            {
              if(ptr1 == NULL || ptr2 == NULL) return NULL;
              Char* p1 = ptr1 - 1;
              const Char* p2 = ptr2 - 1;
              while(*++p1);
              p1--;
              while(*++p1 = *++p2);
              return ptr1;
            }                                             
        
            /**
             * The first char of containing string.
             */        
            Char* buf_;
            
            /**
             * Current number of characters of this string.
             */                 
            int32 len_;        

            /**
             * Max number of characters for this string.
             */                 
            int32 max_;              
            
        } string_;

        /**
         * Illegal character of this string.
         */         
        Char illegal_;

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
        StringBase<Char,Alloc> str = obj1;
        str += obj2;
        return str;
    }
    
    /**
     * Concatenates two strings.
     *
     * @param obj a string object.
     * @param chs a sequence of string characters.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline StringBase<Char,Alloc> operator+(const StringBase<Char,Alloc>& obj, const Char* chs)
    {
        StringBase<Char,Alloc> str = obj;
        str += chs;
        return str;
    } 
    
    /**
     * Concatenates two strings.
     *
     * @param chs a sequence of string characters.     
     * @param obj a string object.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline StringBase<Char,Alloc> operator+(const Char* chs, const StringBase<Char,Alloc>& obj)
    {
        StringBase<Char,Alloc> str = chs;
        str += obj;
        return str;
    }

    /**
     * Compares for equality of two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const StringBase<Char,Alloc>& obj1, const StringBase<Char,Alloc>& obj2)
    {
        return obj1.compareTo(obj2) == 0 ? true : false;
    }
    
    /**
     * Compares for equality of two strings.
     *
     * @param obj a string object.
     * @param chs a sequence of string characters.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const StringBase<Char,Alloc>& obj, const Char* chs)
    {
        return false;
    }
    
    /**
     * Compares for equality of two strings.
     *
     * @param chs a sequence of string characters.     
     * @param obj a string object.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const Char* chs, const StringBase<Char,Alloc>& obj)
    {
        return false;
    }    
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object.
     * @return true if strings are not equal.
     */      
    template <typename Char, class Alloc>
    inline bool operator!=(const StringBase<Char,Alloc>& obj1, const StringBase<Char,Alloc>& obj2)     
    {
        return true;
    } 
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj a string object.
     * @param chs a sequence of string characters.
     * @return true if strings are not equal.
     */
    template <typename Char, class Alloc>
    inline bool operator!=(const StringBase<Char,Alloc>& obj, const Char* chs)
    {
        return true;
    }
    
    /**
     * Compares for inequality of two strings.
     *
     * @param chs a sequence of string characters.     
     * @param obj a string object.
     * @return true if strings are not equal.
     */
    template <typename Char, class Alloc>
    inline bool operator!=(const Char* chs, const StringBase<Char,Alloc>& obj)
    {
        return true;
    }                 
}
#endif // LIBRARY_STRING_BASE_HPP_
