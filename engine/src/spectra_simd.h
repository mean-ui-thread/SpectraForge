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

#ifndef SPECTRA_SIMD_H
#define SPECTRA_SIMD_H

#include "spectra_predef.h"
#include "spectra_math.h"

#define SPECTRA_INT32X4_COUNT 4
#define SPECTRA_FLOAT32X4_COUNT 4

#define SPECTRA_SIMD_NONE 0x00000000
#define SPECTRA_SIMD_NEON 0x00000001  // ARM v7a
#define SPECTRA_SIMD_SSE2 0x00000020  // Intel Pentium 4, AMD Athlon 64
#define SPECTRA_SIMD_SSE3 0x00000040  // Intel Pentium 4 Prescott, AMD Athlon 64 San Diego
#define SPECTRA_SIMD_SSSE3 0x00000080 // Intel Core 2, AMD Bulldozer
#define SPECTRA_SIMD_SSE4A 0x00001000 // AMD Phenom
#define SPECTRA_SIMD_SSE41 0x00002000 // Intel Penryn, AMD Bulldozer
#define SPECTRA_SIMD_SSE42 0x00004000 // Intel Nehalem (aka Core i7), AMD Bulldozer
#define SPECTRA_SIMD_AVX 0x00010000
#define SPECTRA_SIMD_AVX2 0x00020000
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
#define SPECTRA_SIMD (SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE42
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE41
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif SPECTRA_SIMD_FORCE_SSE4A
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE4A | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
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
#define SPECTRA_SIMD (SPECTRA_SIMD_AVX | SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4_2__
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE42 | SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4_1__
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE41 | SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE4A__
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE4A | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSSE3__
#define SPECTRA_SIMD (SPECTRA_SIMD_SSSE3 | SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE3__
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE3 | SPECTRA_SIMD_SSE2)
#elif __SSE2__ || _M_X64 || _M_IX86_FP >= 2
#define SPECTRA_SIMD (SPECTRA_SIMD_SSE2)
#else
#define SPECTRA_SIMD (SPECTRA_SIMD_NONE)
#endif

#if (SPECTRA_SIMD & SPECTRA_SIMD_NEON)
#include "arm_neon.h"
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
#endif

#if (SPECTRA_SIMD & SPECTRA_SIMD_NEON)
typedef float32x4_t spectra_float32x4;

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_load(const float *p)
{
    return vreinterpretq_m128_f32(vld1q_f32(p));
}

SPECTRA_FORCE_INLINE void spectra_simd_store(float *p, spectra_float32x4 a){
    vst1q_f32(p, vreinterpretq_f32_m128(a))}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_mul(spectra_float32x4 a, spectra_float32x4 b)
{
    return vreinterpretq_m128_f32(vmulq_f32(vreinterpretq_f32_m128(a), vreinterpretq_f32_m128(b)));
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set(float z, float y, float x, float w)
{
    float SPECTRA_ALIGNED(16) data[4] = {w, x, y, z};
    return vreinterpretq_m128_f32(vld1q_f32(data));
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set_all(float w)
{
    return vreinterpretq_m128_f32(vdupq_n_f32(w));
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set_zero(void)
{
    return vreinterpretq_m128_f32(vdupq_n_f32(0));
}

#elif (SPECTRA_SIMD & SPECTRA_SIMD_SSE2)

#define _PS_CONST(Name, Val) \
    static const float _ps_##Name[4] SPECTRA_ALIGNED(16) = {(const float)(Val), (const float)(Val), (const float)(Val), (const float)(Val)}
#define _PI32_CONST(Name, Val) \
    static const int _pi32_##Name[4] SPECTRA_ALIGNED(16) = {Val, Val, Val, Val}
#define _PS_CONST_TYPE(Name, Type, Val) \
    static const Type _ps_##Name[4] SPECTRA_ALIGNED(16) = {Val, Val, Val, Val}

typedef __m128i spectra_int32x4;
typedef __m128 spectra_float32x4;

_PS_CONST(0, 0.0f);
_PS_CONST(1, 1.0f);
_PS_CONST(0p5, 0.5f);

_PS_CONST_TYPE(sign_mask, int, 0x80000000);
_PS_CONST_TYPE(inv_sign_mask, int, ~0x80000000);

_PI32_CONST(0, 0);
_PI32_CONST(1, 1);
_PI32_CONST(inv1, ~1);
_PI32_CONST(2, 2);
_PI32_CONST(4, 4);

_PS_CONST(minus_cephes_DP1, -0.78515625);
_PS_CONST(minus_cephes_DP2, -2.4187564849853515625e-4);
_PS_CONST(minus_cephes_DP3, -3.77489497744594108e-8);
_PS_CONST(sincof_p0, -1.9515295891E-4);
_PS_CONST(sincof_p1, 8.3321608736E-3);
_PS_CONST(sincof_p2, -1.6666654611E-1);
_PS_CONST(coscof_p0, 2.443315711809948E-005);
_PS_CONST(coscof_p1, -1.388731625493765E-003);
_PS_CONST(coscof_p2, 4.166664568298827E-002);
_PS_CONST(cephes_FOPI, 1.27323954473516); // 4 / M_PI

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_load(const float *p)
{
    return _mm_load_ps(p);
}

SPECTRA_FORCE_INLINE void spectra_simd_store(float *p, spectra_float32x4 a)
{
    _mm_store_ps(p, a);
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_mul(spectra_float32x4 a, spectra_float32x4 b)
{
    return _mm_mul_ps(a, b);
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set(float z, float y, float x, float w)
{
    return _mm_set_ps(z, y, x, w);
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set_all(float w)
{
    return _mm_set1_ps(w);
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_set_zero(void)
{
    return _mm_setzero_ps();
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_sin(spectra_float32x4 x)
{
    __m128 xmm1, xmm2 = *(__m128 *)_ps_0, xmm3, sign_bit, y, y2, z, tmp;

    __m128 swap_sign_bit, poly_mask;
    __m128i emm0, emm2;
    sign_bit = x;
    /* take the absolute value */
    x = _mm_and_ps(x, *(__m128 *)_ps_inv_sign_mask);
    /* extract the sign bit (upper one) */
    sign_bit = _mm_and_ps(sign_bit, *(__m128 *)_ps_sign_mask);

    /* scale by 4/Pi */
    y = _mm_mul_ps(x, *(__m128 *)_ps_cephes_FOPI);

    /* store the integer part of y in mm0 */
    emm2 = _mm_cvttps_epi32(y);
    /* j=(j+1) & (~1) (see the cephes sources) */
    emm2 = _mm_add_epi32(emm2, *(__m128i *)_pi32_1);
    emm2 = _mm_and_si128(emm2, *(__m128i *)_pi32_inv1);
    y = _mm_cvtepi32_ps(emm2);
    /* get the swap sign flag */
    emm0 = _mm_and_si128(emm2, *(__m128i *)_pi32_4);
    emm0 = _mm_slli_epi32(emm0, 29);
    /* get the polynom selection mask
        there is one polynom for 0 <= x <= Pi/4
        and another one for Pi/4<x<=Pi/2W
        Both branches will be computed.
    */
    emm2 = _mm_and_si128(emm2, *(__m128i *)_pi32_2);
    emm2 = _mm_cmpeq_epi32(emm2, *(__m128i *)_pi32_0);

    swap_sign_bit = _mm_castsi128_ps(emm0);
    poly_mask = _mm_castsi128_ps(emm2);
    sign_bit = _mm_xor_ps(sign_bit, swap_sign_bit);

    /* The magic pass: "Extended precision modular arithmetic"
        x = ((x - y * DP1) - y * DP2) - y * DP3; */
    xmm1 = *(__m128 *)_ps_minus_cephes_DP1;
    xmm2 = *(__m128 *)_ps_minus_cephes_DP2;
    xmm3 = *(__m128 *)_ps_minus_cephes_DP3;
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    /* Evaluate the first polynom  (0 <= x <= Pi/4) */
    y = *(__m128 *)_ps_coscof_p0;
    z = _mm_mul_ps(x, x);

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, *(__m128 *)_ps_coscof_p1);
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, *(__m128 *)_ps_coscof_p2);
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    tmp = _mm_mul_ps(z, *(__m128 *)_ps_0p5);
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, *(__m128 *)_ps_1);

    /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

    y2 = *(__m128 *)_ps_sincof_p0;
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, *(__m128 *)_ps_sincof_p1);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, *(__m128 *)_ps_sincof_p2);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    /* select the correct result from the two polynoms */
    xmm3 = poly_mask;
    y2 = _mm_and_ps(xmm3, y2); //, xmm3);
    y = _mm_andnot_ps(xmm3, y);
    y = _mm_add_ps(y, y2);
    /* update the sign */
    y = _mm_xor_ps(y, sign_bit);

    return y;
}

SPECTRA_FORCE_INLINE spectra_float32x4 spectra_simd_cos(spectra_float32x4 x)
{
    __m128 xmm1, xmm2 = *(__m128 *)_ps_0, xmm3, y, y2, z, sign_bit, poly_mask, tmp;
    __m128i emm0, emm2;

    /* take the absolute value */
    x = _mm_and_ps(x, *(__m128 *)_ps_inv_sign_mask);

    /* scale by 4/Pi */
    y = _mm_mul_ps(x, *(__m128 *)_ps_cephes_FOPI);

    /* store the integer part of y in mm0 */
    emm2 = _mm_cvttps_epi32(y);
    /* j=(j+1) & (~1) (see the cephes sources) */
    emm2 = _mm_add_epi32(emm2, *(__m128i *)_pi32_1);
    emm2 = _mm_and_si128(emm2, *(__m128i *)_pi32_inv1);
    y = _mm_cvtepi32_ps(emm2);

    emm2 = _mm_sub_epi32(emm2, *(__m128i *)_pi32_2);

    /* get the swap sign flag */
    emm0 = _mm_andnot_si128(emm2, *(__m128i *)_pi32_4);
    emm0 = _mm_slli_epi32(emm0, 29);
    /* get the polynom selection mask */
    emm2 = _mm_and_si128(emm2, *(__m128i *)_pi32_2);
    emm2 = _mm_cmpeq_epi32(emm2, *(__m128i *)_pi32_0);

    sign_bit = _mm_castsi128_ps(emm0);
    poly_mask = _mm_castsi128_ps(emm2);
    /* The magic pass: "Extended precision modular arithmetic"
        x = ((x - y * DP1) - y * DP2) - y * DP3; */
    xmm1 = *(__m128 *)_ps_minus_cephes_DP1;
    xmm2 = *(__m128 *)_ps_minus_cephes_DP2;
    xmm3 = *(__m128 *)_ps_minus_cephes_DP3;
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    /* Evaluate the first polynom  (0 <= x <= Pi/4) */
    y = *(__m128 *)_ps_coscof_p0;
    z = _mm_mul_ps(x, x);

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, *(__m128 *)_ps_coscof_p1);
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, *(__m128 *)_ps_coscof_p2);
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    tmp = _mm_mul_ps(z, *(__m128 *)_ps_0p5);
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, *(__m128 *)_ps_1);

    /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

    y2 = *(__m128 *)_ps_sincof_p0;
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, *(__m128 *)_ps_sincof_p1);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, *(__m128 *)_ps_sincof_p2);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    /* select the correct result from the two polynoms */
    xmm3 = poly_mask;
    y2 = _mm_and_ps(xmm3, y2); //, xmm3);
    y = _mm_andnot_ps(xmm3, y);
    y = _mm_add_ps(y, y2);
    /* update the sign */
    y = _mm_xor_ps(y, sign_bit);

    return y;
}
#endif

#endif // SPECTRA_SIMD_H