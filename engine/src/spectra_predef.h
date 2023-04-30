/*******************************************************************************
 * Copyright (c) 2023 Mean UI Thread
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#ifndef SPECTRAPREDEF_H
#define SPECTRAPREDEF_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Language Detection
 ******************************************************************************/
#if defined(__cplusplus)
    #define SPECTRA_LANG_CXX 1
#else
    #define SPECTRA_LANG_C 1
#endif

/*******************************************************************************
 * Debug build type Detection
 ******************************************************************************/
#ifndef SPECTRA_DEBUG
    #if !defined(NDEBUG) || defined(_DEBUG)
        #define SPECTRA_DEBUG 1
    #endif
#endif

/*******************************************************************************
 * Compiler Detection
 * http://sourceforge.net/p/predef/wiki/Compilers/
 ******************************************************************************/
#if defined(__clang__)
    #define SPECTRA_COMPILER_CLANG 1
    #if defined(__apple_build_version__)
        #define SPECTRA_COMPILER_CLANG_APPLE 1
    #elif defined(_MSC_VER)
        #define SPECTRA_COMPILER_CLANG_MSVC 1
    #endif
    #define SPECTRA_COMPILER_NAME clang
    #define SPECTRA_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
#elif defined(__GNUC__)
    #define SPECTRA_COMPILER_GCC 1
    #define SPECTRA_COMPILER_NAME GCC
    #if defined(__MINGW32__)
        #define SPECTRA_COMPILER_GCC_MINGW 1
        #if defined(__MINGW64__)
            #define SPECTRA_COMPILER_VERSION (__MINGW64_VERSION_MAJOR * 10000 + __MINGW64_VERSION_MINOR * 100)
        #else
            #define SPECTRA_COMPILER_VERSION (__MINGW32_VERSION_MAJOR * 10000 + __MINGW32_VERSION_MINOR * 100)
        #endif
    #else
        #define SPECTRA_COMPILER_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
    #endif
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
    #define SPECTRA_COMPILER_INTEL 1
    #define SPECTRA_COMPILER_NAME INTEL

    #if defined(__INTEL_COMPILER)
        #define SPECTRA_COMPILER_VERSION __INTEL_COMPILER
    #elif defined(__ICL)
        #define SPECTRA_COMPILER_VERSION __ICL
    #elif defined(__ICC)
        #define SPECTRA_COMPILER_VERSION __ICC
    #elif defined(__ECC)
        #define SPECTRA_COMPILER_VERSION __ECC
    #endif
#elif defined(_MSC_VER)
    #define SPECTRA_COMPILER_MSVC 1
    #define SPECTRA_COMPILER_NAME MSVC
    #define SPECTRA_COMPILER_VERSION _MSC_VER
    #define SPECTRA_COMPILER_VS6_OR_GREATER       (_MSC_VER >= 1200)
    #define SPECTRA_COMPILER_VS2002_OR_GREATER    (_MSC_VER >= 1300)
    #define SPECTRA_COMPILER_VS2003_OR_GREATER    (_MSC_VER >= 1310)
    #define SPECTRA_COMPILER_VS2005_OR_GREATER    (_MSC_VER >= 1400)
    #define SPECTRA_COMPILER_VS2008_OR_GREATER    (_MSC_VER >= 1500)
    #define SPECTRA_COMPILER_VS2008SP1_OR_GREATER (_MSC_VER >= 1500 && _MSC_FULL_VER >= 150030729)
    #define SPECTRA_COMPILER_VS2010_OR_GREATER    (_MSC_VER >= 1600)
    #define SPECTRA_COMPILER_VS2010SP1_OR_GREATER (_MSC_VER >= 1600 && _MSC_FULL_VER >= 160040219)
    #define SPECTRA_COMPILER_VS2012_OR_GREATER    (_MSC_VER >= 1700)
    #define SPECTRA_COMPILER_VS2013_OR_GREATER    (_MSC_VER >= 1800)
    #define SPECTRA_COMPILER_VS2015_OR_GREATER    (_MSC_VER >= 1900)
#endif



/*******************************************************************************
 * Compiler standard detection
 * https://sourceforge.net/p/predef/wiki/Standards/
 ******************************************************************************/
#if SPECTRA_LANG_C || SPECTRA_COMPILER_MSVC
    #define SPECTRA_COMPILER_C90_OR_GREATER __STDC__ || __STDC_VERSION__ || SPECTRA_COMPILER_VS6_OR_GREATER
    #define SPECTRA_COMPILER_C94_OR_GREATER __STDC_VERSION__ >= 199409L
    #define SPECTRA_COMPILER_C99_OR_GREATER __STDC_VERSION__ >= 199901L || SPECTRA_COMPILER_VS2012_OR_GREATER /* not exactly true, but fmin is available in math.h since vs2012 */
    #define SPECTRA_COMPILER_C11_OR_GREATER __STDC_VERSION__ >= 201112L
#endif

#if SPECTRA_LANG_CXX
    #define SPECTRA_COMPILER_CXX98_OR_GREATER __cplusplus >= 199711L
    #define SPECTRA_COMPILER_CXX11_OR_GREATER __cplusplus >= 201103L
    #define SPECTRA_COMPILER_CXX14_OR_GREATER __cplusplus >= 201402L
#endif

/*******************************************************************************
 * Operating System Detection
 * http://sourceforge.net/p/predef/wiki/OperatingSystems/
 * http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system
 ******************************************************************************/

#if defined(__ANDROID__) || defined(__ANDROID_API__)
    #define SPECTRA_OS_ANDROID 1
#endif

#if defined(__APPLE__) && defined(__MACH__)
    #define SPECTRA_OS_MAC 1
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE == 1
        #define SPECTRA_OS_IOS 1
    #else
        #define SPECTRA_OS_OSX 1
    #endif
#endif

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    #include <sys/param.h>
    #if defined(BSD)
        #define SPECTRA_OS_BSD 1
    #endif
#endif

#if defined(__linux__)
    #define SPECTRA_OS_LINUX 1
#endif

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    #include <unistd.h>
    #if defined(_POSIX_VERSION)
        #define SPECTRA_OS_POSIX 1
    #endif
#endif

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    #define SPECTRA_OS_UNIX 1
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define SPECTRA_OS_WINDOWS 1
#endif

/*******************************************************************************
 * CPU Architecture Detection
 * http://sourceforge.net/p/predef/wiki/Architectures/
 * http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
 ******************************************************************************/

#if defined (__aarch64__)
    #define SPECTRA_ARCH_ARM64 1
#elif defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined (_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__arm)
    #define SPECTRA_ARCH_ARM 1
#endif

#if defined(__mips__) || defined(__mips) || defined(__MIPS__)
    #define SPECTRA_ARCH_MIPS 1
#endif

#if defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
    #if defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(__64BIT__) || defined(_LP64) || defined(__LP64__)
        #define SPECTRA_ARCH_PPC64 1
    #else
        #define SPECTRA_ARCH_PPC 1
    #endif
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #define SPECTRA_ARCH_X86_64 1
#elif defined(__i386) || defined(_M_IX86)
    #define SPECTRA_ARCH_X86 1
#endif

#if UINTPTR_MAX == 0xffffffff
    #define SPECTRA_ARCH_32 1
#elif UINTPTR_MAX == 0xffffffffffffffff
    #define SPECTRA_ARCH_64 1
#endif

/*******************************************************************************
 * Hardware Floating point unit detection
 ******************************************************************************/
#if SPECTRA_ARCH_X86_64 || SPECTRA_ARCH_64 || ((SPECTRA_ARCH_ARM || SPECTRA_ARCH_ARM64) && defined(__VFP_FP__) && !defined(__SOFTFP__))
    #define SPECTRA_ARCH_SUPPORT_FPU 1
#endif


/*******************************************************************************
 * Single Instruction Multiple Data (SIMD) detection
 ******************************************************************************/
#define SPECTRA_SIMD_NONE   0x00000000
#define SPECTRA_SIMD_NEON   0x00000001 // ARM v7a
#define SPECTRA_SIMD_SSE2   0x00000020 // Intel Pentium 4, AMD Athlon 64
#define SPECTRA_SIMD_SSE3   0x00000040 // Intel Pentium 4 Prescott, AMD Athlon 64 San Diego
#define SPECTRA_SIMD_SSSE3  0x00000080 // Intel Core 2, AMD Bulldozer
#define SPECTRA_SIMD_SSE4A  0x00001000 // AMD Phenom
#define SPECTRA_SIMD_SSE41  0x00002000 // Intel Penryn, AMD Bulldozer
#define SPECTRA_SIMD_SSE42  0x00004000 // Intel Nehalem (aka Core i7), AMD Bulldozer
#define SPECTRA_SIMD_AVX    0x00010000
#define SPECTRA_SIMD_AVX2   0x00020000
#define SPECTRA_SIMD_AVX512 0x00040000

#if SPECTRA_SIMD_FORCE_NONE
    #define SPECTRA_SIMD SPECTRA_SIMD_NONE
#elif SPECTRA_SIMD_FORCE_NEON
    #define SPECTRA_SIMD (SPECTRA_SIMD_NEON)
#elif SPECTRA_SIMD_FORCE_AVX512
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX512 | SPECTRA_SIMD_AVX2 | SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_AVX2
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX2 | SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_AVX
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41  | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE42
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE41
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE4A
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE4A |SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSSE3
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE3
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE2
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE2)
#elif __ARM_NEON | __ARM_NEON__
    #define SPECTRA_SIMD (SPECTRA_SIMD_NEON)
#elif __AVX512BW__ && __AVX512F__ && __AVX512CD__ && __AVX512VL__ && __AVX512DQ__
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX512 | SPECTRA_SIMD_AVX2 | SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __AVX2__
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX2 | SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __AVX__
    #define SPECTRA_SIMD (SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41  | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4_2__
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE42  | SPECTRA_SIMD_SSE41  | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4_1__
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4A__
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE4A | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSSE3__
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE3__
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE2__ | _M_X64
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE2)
#elif _M_IX86_FP >= 2
    #define SPECTRA_SIMD (SPECTRA_SIMD_SSE2)
#else
    #define SPECTRA_SIMD (SPECTRA_SIMD_NONE)
#endif

#if __MINGW64__ && (SPECTRA_SIMD != SPECTRA_SIMD_NONE)
    #include <intrin.h>
#endif

#if (SPECTRA_SIMD & SPECTRA_SIMD_NEON)
    #include "SSE2NEON.h"
#elif (SPECTRA_SIMD & SPECTRA_SIMD_AVX)
    #include <immintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE42)
    #if SPECTRA_COMPILER_CLANG
        #include <popcntintrin.h>
    #endif
    #include <nmmintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE41)
    #include <smmintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE4A)
    #include <ammintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSSE3)
    #include <tmmintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE3)
    #include <pmmintrin.h>
#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE2)
    #include <emmintrin.h>
    #include <xmmintrin.h>
#endif


/*******************************************************************************
 * Necessary helper macro for MSVC that is, once again, diverging from the
 * standard specification. Must be used for when the output of a macro is used
 * as an input for another macro.
 *
 * This example works in GCC, but won't work in MSVC:
 *
 *      #define F(x, ...) X = x and VA_ARGS = __VA_ARGS__
 *      #define G(...) F(__VA_ARGS__)
 *
 * To make the above macro work for both GCC and MSVC, do this:
 *
 *      #define F(x, ...) X = x and VA_ARGS = __VA_ARGS__
 *      #define G(...) SPECTRA_EXPAND( F(__VA_ARGS__) )
 *
 * http://stackoverflow.com/questions/5134523/msvc-doesnt-expand-va-args-correctly
 ******************************************************************************/
#define SPECTRA_EXPAND(x) x

/*******************************************************************************
 * Macro that expands only the 65th argument. Useful for counting arguments.
 ******************************************************************************/
#define SPECTRA_SELECT_65TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45, a46, a47, a48, a49, a50, a51, a52, a53, a54, a55, a56, a57, a58, a59, a60, a61, a62, a63, a64, a65, ...) a65

/*******************************************************************************
 * Helper macro to detect if we have at least one comma in the provided
 * __VA_ARGS__
 *
 * Example:
 *
 *     `SPECTRA_HAVE_COMMA()` would expand to `0`
 *     `SPECTRA_HAVE_COMMA(a)` would expand to `0`
 *     `SPECTRA_HAVE_COMMA(a, b)` would expand to `1`
 *     `SPECTRA_HAVE_COMMA(a, b, c)` would expand to `1`
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#if SPECTRA_LANG_CXX || (SPECTRA_LANG_C && __STDC_VERSION__ >= 199901L)
#define SPECTRA_HAVE_COMMA(...) SPECTRA_SELECT_65TH(__VA_ARGS__,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 1,\
    1, 1, 1, 1, 1, 1, 1, 0,\
    0)
#endif

/*******************************************************************************
 * Helper macro to detect if the provided __VA_ARGS__ is empty
 *
 * Special thanks to Jens Gustedt for this blog post:
 * https://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
 *
 * Example:
 *
 *      `SPECTRA_IS_EMPTY()` would expand to `1`
 *      `SPECTRA_IS_EMPTY(a)` would expand to `0`
 *      `SPECTRA_IS_EMPTY(a, b)` would expand to `0`
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#if SPECTRA_LANG_CXX || (SPECTRA_LANG_C && __STDC_VERSION__ >= 199901L)
#define _SPECTRA_PASTE_5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _SPECTRA_IS_EMPTY_HELPER(_0, _1, _2, _3) SPECTRA_HAVE_COMMA(_SPECTRA_PASTE_5(_SPECTRA_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define _SPECTRA_IS_EMPTY_CASE_0001 ,
#define _SPECTRA_TRIGGER_PARENTHESIS_(...) ,
#define SPECTRA_IS_EMPTY(...) _SPECTRA_IS_EMPTY_HELPER(\
    /* test if there is just one argument, eventually an empty one */\
    SPECTRA_HAVE_COMMA(__VA_ARGS__),\
    /* test if _SPECTRA_TRIGGER_PARENTHESIS_ together with the argument adds a comma */\
    SPECTRA_HAVE_COMMA(_SPECTRA_TRIGGER_PARENTHESIS_ __VA_ARGS__),\
    /* test if the argument together with a parenthesis adds a comma */\
    SPECTRA_HAVE_COMMA(__VA_ARGS__ (/*empty*/)),\
    /* test if placing it between _SPECTRA_TRIGGER_PARENTHESIS_ and the parenthesis adds a comma */\
    SPECTRA_HAVE_COMMA(_SPECTRA_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/))\
    )
#endif

/*******************************************************************************
 * Macro that expands the first argument and ignores any arguments following the
 * first argument.
 *
 * Example:
 *
 *     `SPECTRA_FIRST()` would expand to ``
 *     `SPECTRA_FIRST(a)` would expand to `a`
 *     `SPECTRA_FIRST(a, b)` would expand to `a`
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#if SPECTRA_LANG_CXX || (SPECTRA_LANG_C && __STDC_VERSION__ >= 199901L)
#define _SPECTRA_FIRST_IS_EMPTY_0(_0, ...) _0
#define _SPECTRA_FIRST_IS_EMPTY_1(...)
#define _SPECTRA_FIRST_MACRO_SELECTOR(result, ...) SPECTRA_EXPAND(_SPECTRA_FIRST_IS_EMPTY_##result(__VA_ARGS__))
#define _SPECTRA_FIRST_HELPER(result, ...) _SPECTRA_FIRST_MACRO_SELECTOR(result, __VA_ARGS__)
#define SPECTRA_FIRST(...) _SPECTRA_FIRST_HELPER(SPECTRA_IS_EMPTY(__VA_ARGS__), __VA_ARGS__, throwaway)
#endif

/*******************************************************************************
 * Macro that expands all of the arguments except the first argument. If one or
 * no parameters are passed, this macro will expand to nothing.
 *
 * Example:
 *
 *     `SPECTRA_REMOVE_FIRST()` would expand to ``
 *     `SPECTRA_REMOVE_FIRST(a)` would expand to ``
 *     `SPECTRA_REMOVE_FIRST(a, b)` would expand to `b`
 *     `SPECTRA_REMOVE_FIRST(a, b, c)` would expand to `b, c`
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#if SPECTRA_LANG_CXX || (SPECTRA_LANG_C && __STDC_VERSION__ >= 199901L)
#define _SPECTRA_REMOVE_FIRST_HAS_COMMA_0(...)
#define _SPECTRA_REMOVE_FIRST_HAS_COMMA_1(_0, ...) __VA_ARGS__
#define _SPECTRA_REMOVE_FIRST_MACRO_SELECTOR(result, ...) SPECTRA_EXPAND(_SPECTRA_REMOVE_FIRST_HAS_COMMA_##result(__VA_ARGS__))
#define _SPECTRA_REMOVE_FIRST_HELPER(result, ...) _SPECTRA_REMOVE_FIRST_MACRO_SELECTOR(result, __VA_ARGS__)
#define SPECTRA_REMOVE_FIRST(...) _SPECTRA_REMOVE_FIRST_HELPER(SPECTRA_HAVE_COMMA(__VA_ARGS__), __VA_ARGS__)
#endif

/*******************************************************************************
 * Helper macro that inserts a comma to the front of __VA_ARGS__ only when the
 * provided __VA_ARGS__ is not empty.
 *
 * It is a C99 compliant replacement to `## __VA_ARGS__` for automatically
 * removing the front comma which. Unfortunately, `## __VA_ARGS__` is
 * non-standard and only available in GCC only if the compiler's GNU extensions
 * are enabled.
 *
 * Example :
 *
 *     `SPECTRA_ADD_FRONT_COMMA()` would expand to ``
 *     `SPECTRA_ADD_FRONT_COMMA(a)` would expand to `, a`
 *     `SPECTRA_ADD_FRONT_COMMA(a, b)` would expand to `, a, b`
 *     `SPECTRA_ADD_FRONT_COMMA(a, b, c)` would expand to `, a, b, c`
 *
 * It is best use for :
 *
 *      #define PRINT_LINE(fmt, ...) printf(ftm "\n" SPECTRA_ADD_FRONT_COMMA(__VA_ARGS__)
 *
 * Or like this if you do not wish to have the first argument split from the
 * rest of the variadic arguments:
 *
 *      #define PRINT_LINE(...) printf(SPECTRA_FIRST(__VA_ARGS__) "\n" SPECTRA_ADD_FRONT_COMMA(SPECTRA_REMOVE_FIRST(__VA_ARGS__))
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#if SPECTRA_LANG_CXX || (SPECTRA_LANG_C && __STDC_VERSION__ >= 199901L)
#define _SPECTRA_ADD_FRONT_COMMA_IS_EMPTY_0(...), __VA_ARGS__
#define _SPECTRA_ADD_FRONT_COMMA_IS_EMPTY_1(...)
#define _SPECTRA_ADD_FRONT_COMMA_MACRO_SELECTOR(result, ...) SPECTRA_EXPAND(_SPECTRA_ADD_FRONT_COMMA_IS_EMPTY_##result(__VA_ARGS__))
#define _SPECTRA_ADD_FRONT_COMMA_HELPER(result, ...) _SPECTRA_ADD_FRONT_COMMA_MACRO_SELECTOR(result, __VA_ARGS__)
#define SPECTRA_ADD_FRONT_COMMA(...) _SPECTRA_ADD_FRONT_COMMA_HELPER(SPECTRA_IS_EMPTY(__VA_ARGS__), __VA_ARGS__)
#endif

/*******************************************************************************
 * Macro that counts arguments
 *
 * Example:
 *
 *      `SPECTRA_COUNT()` would expand to `0`
 *      `SPECTRA_COUNT(A)` would expand to `1`
 *      `SPECTRA_COUNT(A,B,C)` would expand to `3`
 *      `SPECTRA_COUNT(A, B, C, D, E, F, G, H, I)` would expand to `9`
 *
 * \warning Only works up to 63 arguments, since the first argument is reserved
 * as the solution to the stray comma for when __VA_ARGS__ is empty.
 ******************************************************************************/
#define _SPECTRA_COUNT_HELPER(...) SPECTRA_EXPAND(SPECTRA_SELECT_65TH(__VA_ARGS__,\
    63, 62, 61, 60, 59, 58, 57, 56,\
    55, 54, 53, 52, 51, 50, 49, 48,\
    47, 46, 45, 44, 43, 42, 41, 40,\
    39, 38, 37, 36, 35, 34, 33, 32,\
    31, 30, 29, 28, 27, 26, 25, 24,\
    23, 22, 21, 20, 19, 18, 17, 16,\
    15, 14, 13, 12, 11, 10,  9,  8,\
     7,  6,  5,  4,  3,  2,  1,  0,\
    0))
#define SPECTRA_COUNT(...) _SPECTRA_COUNT_HELPER(reserved_front SPECTRA_ADD_FRONT_COMMA(__VA_ARGS__) )

/*******************************************************************************
 * Macro that calls macro overload based on the amount of parameters
 *
 * Example:
 *
 * #define ASSERT1(expr) singleArgumentExpansion(expr)
 * #define ASSERT2(expr, explain) twoArgumentExpansion(expr, explain)
 * #define ASSERT(...) SPECTRA_CALL_OVERLOAD(ASSERT, __VA_ARGS__)
 *
 * \warning Only works up to 64 arguments.
 ******************************************************************************/
#define _SPECTRA_GLUE(x, y) x y

#define _SPECTRA_OVERLOAD_MACRO2(name, count) name##count
#define _SPECTRA_OVERLOAD_MACRO1(name, count) _SPECTRA_OVERLOAD_MACRO2(name, count)
#define _SPECTRA_OVERLOAD_MACRO(name, count) _SPECTRA_OVERLOAD_MACRO1(name, count)

#define _SPECTRA_EXPAND_ARGS(args) SPECTRA_SELECT_65TH args
#define _SPECTRA_COUNT_ARGS_MAX64(...) _SPECTRA_EXPAND_ARGS((__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define SPECTRA_CALL_OVERLOAD(name, ...) _SPECTRA_GLUE(_SPECTRA_OVERLOAD_MACRO(name, _SPECTRA_COUNT_ARGS_MAX64(__VA_ARGS__)), (__VA_ARGS__))


/*******************************************************************************
 * Stringify macro
 *
 * Example:
 *
 *      `SPECTRA_STRINGIFY(abc)` would expand to `"abc"`
 *
 ******************************************************************************/
#define SPECTRA_STRINGIFY(str) _SPECTRA_STRINGIFY_HELPER(str)
#define _SPECTRA_STRINGIFY_HELPER(str) #str

/*******************************************************************************
 * Join-Stringify macro
 *
 * Example:
 *
 *      `SPECTRA_JOIN_STRINGIFY(abc,def)` would expand to `"abcdef"`
 *
 ******************************************************************************/
#define SPECTRA_JOIN_STRINGIFY(x,y) SPECTRA_STRINGIFY(x ## y)

/*******************************************************************************
 * Compiler-independant pragma
 ******************************************************************************/
#define SPECTRA_PRAGMA(expression) _SPECTRA_PRAGMA_HELPER(expression)
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define _SPECTRA_PRAGMA_HELPER(expression) __pragma(expression)
#elif SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC || SPECTRA_COMPILER_INTEL
    #define _SPECTRA_PRAGMA_HELPER(expression) _Pragma(#expression)
#else
    #define _SPECTRA_PRAGMA_HELPER(expression)
#endif


/*******************************************************************************
 * Compiler-independant user compile warning/error.
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define SPECTRA_WARNING(MSG) SPECTRA_PRAGMA(message(__FILE__ "(" SPECTRA_STRINGIFY(__LINE__) ") : warning c0000:" msg)
    #define SPECTRA_ERROR(MSG) SPECTRA_PRAGMA(message(__FILE__ "(" SPECTRA_STRINGIFY(__LINE__) ") : error c0000:" msg)
#else
    #define SPECTRA_WARNING(msg) SPECTRA_PRAGMA(GCC warning SPECTRA_STRINGIFY(msg))
    #define SPECTRA_ERROR(msg) SPECTRA_PRAGMA(GCC error SPECTRA_STRINGIFY(msg))
#endif

/*******************************************************************************
 * Compiler-independant forced inline
 ******************************************************************************/
#if SPECTRA_DEBUG
    #define SPECTRA_FORCE_INLINE static inline
#else
    #if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
        #define SPECTRA_FORCE_INLINE __forceinline
    #elif SPECTRA_COMPILER_CLANG
        #define SPECTRA_FORCE_INLINE __attribute__((always_inline, nodebug)) static __inline__
    #elif ( SPECTRA_COMPILER_GCC && (__GNUC__ >= 4) )
        #define SPECTRA_FORCE_INLINE __attribute__((always_inline)) static __inline__
    #else
        SPECTRA_WARNING("forced 'inline' not supported by your compiler.")
        #define SPECTRA_FORCE_INLINE static inline
    #endif
#endif

#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    SPECTRA_PRAGMA(inline_recursion(on))
#endif

/*******************************************************************************
 * Compiler-independant static Constructor/Destructor
 ******************************************************************************/
#if SPECTRA_LANG_CXX
    #define SPECTRA_C_CONSTRUCTOR(_func) \
        static void _func(void); \
        struct _func ## _ctor { _func ## _ctor() { _func(); } };\
        static _func ## _ctor s_ ## _func ## _ctor;\
        void _func(void)
    #define SPECTRA_C_DESTRUCTOR(_func) \
        static void _func(void); \
        struct _func ## _dtor { _func ## _dtor() { atexit (_func()); } };\
        static _func ## _dtor s_ ## _func ## _dtor;\
        void _func(void)
#elif SPECTRA_COMPILER_MSVC
    #if SPECTRA_COMPILER_VS2008_OR_GREATER
        #define SPECTRA_C_CONSTRUCTOR(_func) \
            static void _func(void); \
            static int32_t _func ## _ctor(void) { _func(); return 0; } \
            __pragma(section(".CRT$XCU",read)) \
            __declspec(allocate(".CRT$XCU")) static int32_t (* _array ## _func)(void) = _func ## _ctor;\
            void _func(void)
        #define SPECTRA_C_DESTRUCTOR(_func) \
            static void _func(void); \
            static int32_t _func ## _dtor(void) { atexit (_func); return 0; } \
            __pragma(section(".CRT$XCU",read)) \
            __declspec(allocate(".CRT$XCU")) static int32_t (* _array ## _func)(void) = _func ## _dtor;\
            void _func(void)
    #elif SPECTRA_COMPILER_VS2005_OR_GREATER
        #pragma section(".CRT$XCU",read)
        #define SPECTRA_C_CONSTRUCTOR(_func) \
            static void _func(void); \
            static int32_t _func ## _ctor(void) { _func(); return 0; } \
            __declspec(allocate(".CRT$XCU")) static int32_t (* _array ## _func)(void) = _func ## _ctor; \
            void _func(void)
        #define SPECTRA_C_DESTRUCTOR(_func) \
            static void _func(void); \
            static int32_t _func ## _dtor(void) { atexit (_func); return 0; } \
            __declspec(allocate(".CRT$XCU")) static int32_t (* _array ## _func)(void) = _func ## _dtor;\
            void _func(void)
    #else
        SPECTRA_ERROR("Static Constructor/Destructor not supported by your compiler. Please upgrade to VS2005 or later.")
    #endif
#elif defined(__GNUC__)
    #if(__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
        #define SPECTRA_C_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void)

        #define SPECTRA_C_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void)
    #else
        SPECTRA_ERROR("Static Constructor/Destructor not supported by your compiler. Please upgrade to GCC 2.7 or later.")
    #endif
#elif defined(__clang__)
    #if(__clang_major__ >= 5 ) // TODO need to check if that version check is correct
        #define SPECTRA_C_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void)

        #define SPECTRA_C_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void)
    #else
        SPECTRA_ERROR("Static Constructor/Destructor not supported by your compiler. Please upgrade to GCC 2.7 or later.")
    #endif
#else
    SPECTRA_ERROR("Static Constructor/Destructor not supported by your compiler.")
#endif


/*******************************************************************************
 * SPECTRA_CURRENT_FILE: Gets the current file name of the source file
 ******************************************************************************/
#define SPECTRA_CURRENT_FILE __FILE__

/*******************************************************************************
 * SPECTRA_CURRENT_LINE: Gets the current line number.
 ******************************************************************************/
#define SPECTRA_CURRENT_LINE __LINE__

/*******************************************************************************
 * SPECTRA_CURRENT_FUNCTION: Gets the current function name
 ******************************************************************************/
#if (defined(__cplusplus) && (__cplusplus >= 201103)) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901))
    #define SPECTRA_CURRENT_FUNCTION __func__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
    #define SPECTRA_CURRENT_FUNCTION __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define SPECTRA_CURRENT_FUNCTION __FUNC__
#elif SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC
    #define SPECTRA_CURRENT_FUNCTION __extension__ __FUNCTION__
#else
    #define SPECTRA_CURRENT_FUNCTION "<UNKNOWN>"
#endif

/*******************************************************************************
 * SPECTRA_CURRENT_FUNCTION_SIG: Gets the current function signature
 ******************************************************************************/
#if (SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__DMC__) && (__DMC__ >= 0x810)
    #define SPECTRA_CURRENT_FUNCTION_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
    #define SPECTRA_CURRENT_FUNCTION_SIG __FUNCSIG__
#else
    #define SPECTRA_CURRENT_FUNCTION_SIG SPECTRA_CURRENT_FUNCTION
#endif

/*******************************************************************************
 * SPECTRA_UNUSED: Marker to supress the unused variable warning if that's
 * really what the user intended. Works up to 5 parameters.
 ******************************************************************************/
#define _SPECTRA_UNUSED0()
#define _SPECTRA_UNUSED1(arg1) (void)(arg1)
#define _SPECTRA_UNUSED2(arg1, arg2) do { (void)(arg1); (void)(arg2); } while((void)0,0)
#define _SPECTRA_UNUSED3(arg1, arg2, arg3) do { (void)(arg1); (void)(arg2); (void)(arg3); } while((void)0,0)
#define _SPECTRA_UNUSED4(arg1, arg2, arg3, arg4) do { (void)(arg1); (void)(arg2); (void)(arg3); (void)(arg4); } while((void)0,0)
#define _SPECTRA_UNUSED5(arg1, arg2, arg3, arg4, arg5) do { (void)(arg1); (void)(arg2); (void)(arg3); (void)(arg4); (void)(arg5); } while((void)0,0)
#define _SPECTRA_UNUSED6(arg1, arg2, arg3, arg4, arg5, arg6) do { (void)(arg1); (void)(arg2); (void)(arg3); (void)(arg4); (void)(arg5); (void)(arg6); } while((void)0,0)
#define SPECTRA_UNUSED(...) SPECTRA_CALL_OVERLOAD(_SPECTRA_UNUSED, __VA_ARGS__)

/*******************************************************************************
 * SPECTRA_SSCANF: cross-platform sscanf.
 * Secured on Windows platform.
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define SPECTRA_SSCANF sscanf_s
#else
    #define SPECTRA_SSCANF sscanf
#endif

/*******************************************************************************
 * SPECTRA_C_SECTION_BEGIN, SPECTRA_C_SECTION_END :
 * Markers to delimit the begining and end of Pure-C code sections when faced
 * with both C and C++ compilers.
 ******************************************************************************/
#if SPECTRA_LANG_CXX
    #define SPECTRA_C_SECTION_BEGIN extern "C" {
    #define SPECTRA_C_SECTION_END }
#else
    #define SPECTRA_C_SECTION_BEGIN
    #define SPECTRA_C_SECTION_END
#endif

/*******************************************************************************
 * SPECTRA_SIZEOF_ARRAY: Helper macro that determines the number of elements of
 * an array.
 ******************************************************************************/
#define SPECTRA_SIZEOF_ARRAY(a) (int)(sizeof(a)/sizeof(a[0]))

/*******************************************************************************
 * SPECTRA_API: This precedes the return type of every public function in the
 * function prototype, insuring the proper visibility.
 * SPECTRA_LOCAL: This precedes the return type of private function that we do not
 * wish to expose at all.
 ******************************************************************************/
#if defined _WIN32 || defined __CYGWIN__
    #define _SPECTRA_HELPER_DLL_IMPORT __declspec(dllimport)
    #define _SPECTRA_HELPER_DLL_EXPORT __declspec(dllexport)
    #define _SPECTRA_HELPER_DLL_LOCAL
#else
    #if __GNUC__ >= 4
        #define _SPECTRA_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define _SPECTRA_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        #define _SPECTRA_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        #define _SPECTRA_HELPER_DLL_IMPORT
        #define _SPECTRA_HELPER_DLL_EXPORT
        #define _SPECTRA_HELPER_DLL_LOCAL
    #endif
#endif

#ifdef SPECTRA_SHARED_LIB
    #ifdef SPECTRA_EXPORT_LIBRARY
        #define SPECTRA_API _SPECTRA_HELPER_DLL_EXPORT
    #else
        #define SPECTRA_API _SPECTRA_HELPER_DLL_IMPORT
    #endif
    #define SPECTRA_LOCAL _SPECTRA_HELPER_DLL_LOCAL
#else
    #define SPECTRA_API
    #define SPECTRA_LOCAL
#endif

/*******************************************************************************
 * Microsoft-specific function call convention.
 * https://msdn.microsoft.com/en-us/library/984x0h58(VS.80).aspx
 *
 * Any of these should be put after the return type of the function prototype.
 ******************************************************************************/
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    #define SPECTRA_DEFAULT_CALL __cdecl
    #define SPECTRA_CLR_CALL __clrcall
    #define SPECTRA_STD_CALL __stdcall
    #define SPECTRA_FAST_CALL __fastcall
    #define SPECTRA_THIS_CALL __thiscall
#else
    #define SPECTRA_DEFAULT_CALL
    #define SPECTRA_CLR_CALL
    #define SPECTRA_STD_CALL
    #define SPECTRA_FAST_CALL
    #define SPECTRA_THIS_CALL
#endif

/*******************************************************************************
 * Memory alignment macros
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define SPECTRA_ALIGNED(x) __declspec(align(x))
    #define SPECTRA_ALIGNOF(x) __alignof(X)
#elif SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC
    #define SPECTRA_ALIGNED(x) __attribute__ ((aligned(x)))
    #define SPECTRA_ALIGNOF(x) __alignof(X)
#else
    SPECTRA_ERROR("align/alignof not supported by your compiler.")
#endif

/*******************************************************************************
 * packing macro
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define SPECTRA_PACK( DECL ) __pragma( pack(push, 1) ) DECL __pragma( pack(pop) )
#elif (SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC
    #define SPECTRA_PACK( DECL ) DECL __attribute__((packed, aligned(1)))
#else
    SPECTRA_ERROR("packing not supported by your compiler.")
#endif

/*******************************************************************************
 * Helper macro that returns the container struct of a member.
 ******************************************************************************/
#define SPECTRA_CONTAINER_OF(ptr, type, member) ((type *)((char *)(ptr) - offsetof(type, member)))


/*******************************************************************************
 * Helper macros to enable/disable compiler warnings
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define SPECTRA_IGNORE_WARNING_PUSH(gcc_unused,clang_unused,msvc_errorcode) SPECTRA_PRAGMA(warning(push)) SPECTRA_STRINGIFY(warning(disable:##msvc_errorcode))
    #define SPECTRA_IGNORE_WARNING_POP() SPECTRA_PRAGMA(warning(pop))
#elif SPECTRA_COMPILER_CLANG
    #define SPECTRA_IGNORE_WARNING_PUSH(gcc_unused,clang_option,msvc_unused) SPECTRA_PRAGMA(clang diagnostic push) SPECTRA_PRAGMA(clang diagnostic ignored SPECTRA_STRINGIFY(-W ## clang_option))
    #define SPECTRA_IGNORE_WARNING_POP() SPECTRA_PRAGMA(clang diagnostic pop)
#elif SPECTRA_COMPILER_GCC
    #define SPECTRA_IGNORE_WARNING_PUSH(gcc_option,clang_unused,msvc_unused) SPECTRA_PRAGMA(GCC diagnostic push) SPECTRA_PRAGMA(GCC diagnostic ignored SPECTRA_STRINGIFY(-W ## gcc_option))
    #define SPECTRA_IGNORE_WARNING_POP() SPECTRA_PRAGMA(GCC diagnostic pop)
#endif

/*******************************************************************************
 * Helper macros to provide cross-platform aligned memory allocation
 ******************************************************************************/
#if SPECTRA_COMPILER_MSVC || SPECTRA_COMPILER_CLANG_MSVC
    #define spectra_aligned_malloc(alignment, size) _aligned_malloc(size, alignment)
    #define spectra_aligned_realloc(alignment, ptr, size) _aligned_realloc(ptr, size, alignment)
    #define spectra_aligned_free(ptr) _aligned_free(ptr)
#elif SPECTRA_COMPILER_CLANG || SPECTRA_COMPILER_GCC
    #define spectra_aligned_malloc(alignment, size) aligned_alloc(alignment, size)
    static void* spectra_aligned_realloc(size_t alignment, void* ptr, size_t size) { void* new_ptr = aligned_alloc(alignment, size); if (new_ptr) { memcpy(new_ptr, ptr, size); free(ptr); } return new_ptr; }
    #define spectra_aligned_free(ptr) free(ptr)
#else
    #define spectra_aligned_malloc(alignment, size) malloc(size)
    #define spectra_aligned_realloc(alignment, ptr, size) realloc(ptr, size)
    #define spectra_aligned_free(ptr) free(ptr)
#endif


#endif /* SPECTRAPREDEF_H */