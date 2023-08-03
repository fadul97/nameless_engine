#ifndef DEFINES_H
#define DEFINES_H

#define TRUE 1
#define FALSE 0

// Unsigned types
typedef unsigned char u8;
typedef	unsigned short u16;
typedef unsigned long ul32;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed types
typedef signed char i8;
typedef	signed short i16;
typedef signed long il32;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double d64;

// Boolean types
typedef char b8;
typedef int b32;

// Platform detection
#if defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX 1
#else
#error "ERROR: Unknown platform."
#endif

// Inline functions
#if defined(__linux__) || defined(__gnu_linux__)
#define INLINE static inline
#endif

#endif // DEFINES_H
