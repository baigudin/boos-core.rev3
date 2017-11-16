/** 
 * String class.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef LIBRARY_STRING_HPP_
#define LIBRARY_STRING_HPP_

#include "Object.hpp"
#include "api.String.hpp"

namespace library
{
    /** 
     * @param Char data type of string characters.
     * @param Alloc heap memory allocator class.
     */
    template <typename Char, class Alloc=::Allocator>    
    class String : public Object<Alloc>, public ::api::String<Char>
    {
        typedef ::Object<Alloc> Parent;        
      
    public:
    
        /** 
         * Constructor.
         */    
        String() : Parent(),
            isConstructed_ (this->getConstruct()),
            string_        (),
            illegal_       (0){
            this->setConstruct( construct("") );
        }
        
        /** 
         * Constructor.
         *
         * @param obj a source string object.
         */ 
        String(const ::library::String<Char,Alloc>& obj) : Parent(obj),
            isConstructed_ (this->getConstruct()),        
            string_        (),
            illegal_       (0){
            this->setConstruct( construct(obj) );
        }
        
        /** 
         * Constructor.
         *
         * @param obj a source string object interface.
         */ 
        String(const ::api::String<Char>& obj) : Parent(obj),
            isConstructed_ (this->getConstruct()),        
            string_        (),
            illegal_       (0){
            this->setConstruct( construct(obj) );
        }
        
        /** 
         * Constructor.
         *
         * @param data a sequence of string characters.
         */    
        String(const Char* data) : Parent(),
            isConstructed_ (this->getConstruct()),
            string_        (),
            illegal_       (0){
            this->setConstruct( construct(data) );
        }
    
        /**
         * Destructor.
         */
        virtual ~String()
        {
        }
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object.
         * @return reference to this object.       
         */     
        String& operator=(const ::library::String<Char,Alloc>& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( assign(obj) );
            return *this;            
        }
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object interface.
         * @return reference to this object.       
         */ 
        String& operator=(const ::api::String<Char>& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( assign(obj) );
            return *this;            
        }        
        
        /** 
         * Assignment operator.
         *
         * @param data a sequence of string characters.
         * @return reference to this object.       
         */     
        String& operator=(const Char* data)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( assign(data) );
            return *this;        
        }
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object.
         * @return reference to this object.       
         */     
        String& operator+=(const ::library::String<Char,Alloc>& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( concatenate(obj) );
            return *this; 
        }  
        
        /** 
         * Assignment operator.
         *
         * @param obj a string object interface.
         * @return reference to this object.       
         */
        String& operator+=(const ::api::String<Char>& obj)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( concatenate(obj) );
            return *this; 
        }                 
        
        /** 
         * Assignment operator.
         *
         * @param data a sequence of string characters.
         * @return reference to this object.       
         */     
        String& operator+=(const Char* data)
        {
            if( not isConstructed_ ) return *this;        
            Parent::operator=(*this);
            this->setConstruct( concatenate(data) );
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
         * Compares two strings lexicographically.
         *
         * @param obj a string object.
         * @return the value 0 if given string is equal to this string; 
         *         a value less than 0 if this string is less than given string; 
         *         a value greater than 0 if this string is greater than given string.
         */
        virtual int32 compareTo(const ::api::String<Char>& obj) const
        {
            if( not obj.isConstructed() ) return 1;
            return compareTo( obj.getChar() );
        }
        
        /** 
         * Compares two strings lexicographically.
         *
         * @param data a sequence of string characters.
         * @return the value 0 if given string is equal to this string; 
         *         a value less than 0 if this string is less than given string; 
         *         a value greater than 0 if this string is greater than given string.
         */
        virtual int32 compareTo(const Char* data) const
        {
            if( not isConstructed_ ) return -1;        
            if( data == NULL ) return 1;
            return string_.compareTo( data );        
        }
        
        /**
         * Returns pointer to the first char of containing string.
         *
         * @param first char of containing string or NULL if no string contained.
         */
        virtual const Char* getChar() const
        {
            return isConstructed_ ? string_.getData() : NULL;
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
        bool construct(const ::library::String<Char,Alloc>& obj)
        {
            const ::api::String<Char>& iobj = obj;
            return construct( iobj );
        }    
        
        /** 
         * Constructs this object.
         *
         * @param obj a source string object interface.
         * @return true if object has been constructed successfully.         
         */ 
        bool construct(const ::api::String<Char>& obj)
        {
            if( not obj.isConstructed() ) return false;            
            return construct( obj.getChar() );
        }        
    
        /**
         * Constructs this object.
         *
         * @param data a sequence of string characters.
         * @return true if object has been constructed successfully.
         */
        bool construct(const Char* data)
        {
            if( not isConstructed_ ) return false;
            return assign(data);
        }

        /** 
         * Assigns a new string.
         *
         * @param obj a source string object.
         * @return true if the task has been completed successfully.
         */
        bool assign(const ::library::String<Char,Alloc>& obj)
        {
            const ::api::String<Char>& iobj = obj;        
            return assign( iobj );
        }
        
        /** 
         * Assigns a new string.
         *
         * @param obj a source string object interface.
         * @return true if the task has been completed successfully.
         */
        bool assign(const ::api::String<Char>& obj)
        {
            if( not obj.isConstructed() ) return false;
            return assign( obj.getChar() );
        }        
        
        /** 
         * Assigns a new string.
         *
         * @param data a sequence of string characters.
         * @return true if the task has been completed successfully.
         */
        bool assign(const Char* data)
        {
            if( not isConstructed_ ) return false;        
            return string_.copy(data);
        }
        
        /** 
         * Concatenates self string and new string.
         *
         * @param obj a source string object.
         * @return true if the task has been completed successfully.
         */
        bool concatenate(const ::library::String<Char,Alloc>& obj)
        {
            const ::api::String<Char>& iobj = obj;
            return concatenate( iobj );
        }
        
        /** 
         * Concatenates self string and new string.
         *
         * @param obj a source string object interface.
         * @return true if the task has been completed successfully.
         */
        bool concatenate(const ::api::String<Char>& obj)
        {
            if( not obj.isConstructed() ) return false;
            return concatenate( obj.getChar() );
        }                        
        
        /** 
         * Concatenates self string and new string.
         *
         * @param str reference to String object.
         * @return true if the task has been completed successfully.
         */
        bool concatenate(const Char* data)
        {
            if( not isConstructed_ ) return false;        
            return string_.concatenate(data);
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
                data_ (NULL),
                len_ (0),
                max_ (0){
            }

            /**
             * Destructor.
             */
           ~StringData()
            {
                deleteData(data_);
            }  
            
            /** 
             * Copies a string self string.
             *
             * @param data a sequence of string characters.
             */
            bool copy(const Char* data)
            {
                if(data == NULL) return false;            
                int32 len, max;
                len = getLength(data);
                if( not isFit(len) ) 
                {
                    deleteData(data_);
                    max_ = 0;
                }
                if(data_ == NULL)
                {
                    data_ = createData(len, max);
                    max_ = max;
                }
                if(data_ == NULL) return false;                
                len_ = len;
                copy(data_, data);
                return true;
            } 
            
            /** 
             * Concatenates two strings.
             *
             * @param data a sequence of string characters.             
             */
            bool concatenate(const Char* data)
            {
                if(data == NULL) return false;            
                if(data_ == NULL) return false;
                int32 len, max;
                len = getLength(data) + len_;          
                if( not isFit(len) ) 
                {
                    Char* tmp = createData(len, max);
                    if(tmp != NULL)
                    {
                        copy(tmp, data_);
                    }
                    deleteData(data_);
                    data_ = tmp;
                    max_ = max;                    
                }
                if(data_ == NULL) return false;                
                len_ = len;
                concatenate(data_, data);                    
                return true;
            }
            
            /** 
             * Compares two strings lexicographically.
             *
             * @param data a sequence of string characters.
             * @return the value 0 if given string is equal to this string; 
             *         a value less than 0 if this string is less than given string; 
             *         a value greater than 0 if this string is greater than given string.
             */
            int32 compareTo(const Char* data) const
            {
                int32 val[2];
                int32 res = len_ - getLength(data);
                if(res != 0) return res;
                for(int32 i=0; i<len_; i++)
                {
                    val[0] = data_[i];
                    val[1] = data[i];
                    res = val[0] - val[1];
                    if(res != 0) break;
                }
                return res;
            }
            
            /**
             * Get pointer to data buffer.
             *
             * @return pointer to data buffer, or NULL.
             */
            const Char* getData() const
            {
                return data_;
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
             * Tests if given length fits to current data buffer.
             *
             * @param len string characters number.
             * @return true if the length will be fit successfully.
             */        
            bool isFit(int32 len)
            {
                return len > max_ ? false : true;
            }        
        
            /** 
             * Creates a new data buffer for string.
             *
             * @param len string characters number.
             * @return the data buffer address.
             */        
            static Char* createData(int32 len, int32& max)
            {
                int32 size = calculateSize(len);
                Char* data = reinterpret_cast<Char*>( Alloc::allocate(size) );
                max = data != NULL ? calculateLength(size) : 0;
                return data;
            }        
            
            /** 
             * Deletes the buffer.
             */        
            static void deleteData(Char*& data)
            {
                if(data != NULL) Alloc::free(data);
                data = NULL;
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
             * @param data a sequence of string characters.
             * @return characters number.
             */
            static int32 getLength(const Char* data)
            {
                if(data == NULL) return 0;
                int32 len = 0;
                while( *data != 0 ) 
                {
                    len++;
                    data++;
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
            Char* data_;
            
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
    inline ::library::String<Char,Alloc> operator+(const ::library::String<Char,Alloc>& obj1, const ::library::String<Char,Alloc>& obj2)
    {
        String<Char,Alloc> str = obj1;
        str += obj2;
        return str;
    }
    
    /**
     * Concatenates two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object interface.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline ::library::String<Char,Alloc> operator+(const ::library::String<Char,Alloc>& obj1, const ::api::String<Char>& obj2)
    {
        String<Char,Alloc> str = obj1;
        str += obj2;
        return str;
    }    
    
    /**
     * Concatenates two strings.
     *
     * @param obj1 a string 1 object interface.
     * @param obj2 a string 2 object.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline ::library::String<Char,Alloc> operator+(const ::api::String<Char>& obj1, const ::library::String<Char,Alloc>& obj2)
    {
        String<Char,Alloc> str = obj1;
        str += obj2;
        return str;
    }     
    
    /**
     * Concatenates two strings.
     *
     * @param obj a string object.
     * @param data a sequence of string characters.
     * @return a new string object.
     */         
    template <typename Char, class Alloc>
    inline ::library::String<Char,Alloc> operator+(const ::library::String<Char,Alloc>& obj, const Char* data)
    {
        String<Char,Alloc> str = obj;
        str += data;
        return str;
    } 
    
    /**
     * Concatenates two strings.
     *
     * @param data a sequence of string characters.     
     * @param obj a string object.
     * @return a new string object.
     */
    template <typename Char, class Alloc>
    inline ::library::String<Char,Alloc> operator+(const Char* data, const ::library::String<Char,Alloc>& obj)
    {
        String<Char,Alloc> str = data;
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
    inline bool operator==(const ::library::String<Char,Alloc>& obj1, const ::library::String<Char,Alloc>& obj2)
    {
        return obj1.compareTo(obj2) == 0 ? true : false;
    }
    
    /**
     * Compares for equality of two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object interface.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const ::library::String<Char,Alloc>& obj1, const ::api::String<Char>& obj2)
    {
        return obj1.compareTo(obj2) == 0 ? true : false;
    } 
    
    /**
     * Compares for equality of two strings.
     *
     * @param obj1 a string 1 object interface.
     * @param obj2 a string 2 object.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const ::api::String<Char>& obj1, const ::library::String<Char,Alloc>& obj2)
    {
        return obj1.compareTo(obj2) == 0 ? true : false;
    }       
    
    /**
     * Compares for equality of two strings.
     *
     * @param obj a string object.
     * @param data a sequence of string characters.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const ::library::String<Char,Alloc>& obj, const Char* data)
    {
        return obj.compareTo(data) == 0 ? true : false;
    }
    
    /**
     * Compares for equality of two strings.
     *
     * @param data a sequence of string characters.     
     * @param obj a string object.
     * @return true if strings are equal.
     */
    template <typename Char, class Alloc>
    inline bool operator==(const Char* data, const ::library::String<Char,Alloc>& obj)
    {
        return obj.compareTo(data) == 0 ? true : false;
    }    
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object.
     * @return true if strings are not equal.
     */      
    template <typename Char, class Alloc>
    inline bool operator!=(const ::library::String<Char,Alloc>& obj1, const ::library::String<Char,Alloc>& obj2)     
    {
        return obj1.compareTo(obj2) == 0 ? false : true;
    } 
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj1 a string 1 object.
     * @param obj2 a string 2 object interface.
     * @return true if strings are not equal.
     */      
    template <typename Char, class Alloc>
    inline bool operator!=(const ::library::String<Char,Alloc>& obj1, const ::api::String<Char>& obj2)     
    {
        return obj1.compareTo(obj2) == 0 ? false : true;
    }
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj1 a string 1 object interface.
     * @param obj2 a string 2 object.
     * @return true if strings are not equal.
     */      
    template <typename Char, class Alloc>
    inline bool operator!=(const ::api::String<Char>& obj1, const ::library::String<Char,Alloc>& obj2)     
    {
        return obj1.compareTo(obj2) == 0 ? false : true;
    }    
    
    /**
     * Compares for inequality of two strings.
     *
     * @param obj a string object.
     * @param data a sequence of string characters.
     * @return true if strings are not equal.
     */
    template <typename Char, class Alloc>
    inline bool operator!=(const ::library::String<Char,Alloc>& obj, const Char* data)
    {
        return obj.compareTo(data) == 0 ? false : true;
    }
    
    /**
     * Compares for inequality of two strings.
     *
     * @param data a sequence of string characters.     
     * @param obj a string object.
     * @return true if strings are not equal.
     */
    template <typename Char, class Alloc>
    inline bool operator!=(const Char* data, const ::library::String<Char,Alloc>& obj)
    {
        return obj.compareTo(data) == 0 ? false : true;
    }                 
}
#endif // LIBRARY_STRING_HPP_
