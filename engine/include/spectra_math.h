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

#ifndef SPECTRA_MATH_H
#define SPECTRA_MATH_H

#include <stdbool.h>

#define SPECTRA_PI 3.14159265358979323846f       // pi
#define SPECTRA_PI_2 1.57079632679489661923f     // pi / 2
#define SPECTRA_PI_4 0.785398163397448309616f    // pi / 4
#define SPECTRA_1_PI 0.318309886183790671538f    // 1 / pi
#define SPECTRA_2_PI 0.636619772367581343076f    // 2 / pi
#define SPECTRA_4_PI 1.27323954473516268615f     // 4 / pi
#define SPECTRA_2_SQRTPI 1.12837916709551257390f // 2 / sqrt(pi)
#define SPECTRA_SQRT2 1.41421356237309504880f    // sqrt(2)
#define SPECTRA_SQRT1_2 0.707106781186547524401f // 1 / sqrt(2)

#define SPECTRA_DEG_TO_RAD 0.0174532925199432957692f // pi / 180
#define SPECTRA_RAD_TO_DEG 57.2957795130823208768f   // 180 / pi

#if defined(__cplusplus)
extern "C"
{
#endif

    inline float spectra_min(float a, float b)
    {
        return a < b ? a : b;
    }

    inline float spectra_max(float a, float b)
    {
        return a > b ? a : b;
    }

    inline float spectra_clamp(float x, float a, float b)
    {
        return x < a ? a : (x > b ? b : x);
    }

    inline float spectra_lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    inline float spectra_lerp_unclamped(float a, float b, float t)
    {
        return (1 - t) * a + t * b;
    }

    inline bool spectra_in_range(float x, float a, float b)
    {
        return x >= a && x <= b;
    }

    inline float spectra_deg_to_rad(float x)
    {
        return x * SPECTRA_DEG_TO_RAD;
    }

    inline float spectra_rad_to_deg(float x)
    {
        return x * SPECTRA_RAD_TO_DEG;
    }

#if defined(__cplusplus)
}
#endif

#endif // SPECTRA_MATH_H
