/** 
 * System types.
 * 
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2017, Embedded Team, Sergey Baigudin
 * @license   http://embedded.team/license/
 */
#ifndef TYPES_HPP_
#define TYPES_HPP_

// NULL definition
#ifdef NULL
#undef NULL
#endif
#if __cplusplus >= 201103L  // Since C++11
  typedef decltype(nullptr)  nullptr_t;
  const nullptr_t NULL = nullptr;
#elif __cplusplus           // Until C++11
  const int NULL = 0;
#else
  #error "The source file must be compiled by C++ compiler"
#endif

// LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)
#ifdef EOOS_TYPE_WIDTH_LP32
typedef signed   int        int16;
typedef unsigned int        uint16;
typedef signed   long       int32;
typedef unsigned long       uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
// ILP32 or 4/4/4 (int, long, and pointer are 32-bit)
#elif EOOS_TYPE_WIDTH_ILP32
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
// LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)
#elif EOOS_TYPE_WIDTH_LLP64
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
// LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)
#elif EOOS_TYPE_WIDTH_LP64
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long       int64;
typedef unsigned long       uint64;
// C++ standard
#else
typedef signed   short      int16;
typedef unsigned short      uint16;
typedef signed   int        int32;
typedef unsigned int        uint32;
typedef signed   long long  int64;
typedef unsigned long long  uint64;
#endif
// Byte types for byte addressing
typedef signed char         int8;
typedef unsigned char       uint8;
// Floating point types
typedef float               float32;
typedef long double         float64;
// The type returned by sizeof
typedef uint32              size_t;
// Type of minimal addressable memory cell
typedef signed char         cell;

#endif // TYPES_HPP_
