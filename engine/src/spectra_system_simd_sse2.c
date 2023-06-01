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
 ******************************************************************************/ \
#include<spectra_scene_priv.h>
#include <spectra_simd.h>

void spectra_move_entity_sse2(ecs_iter_t *it)
{
#if (SPECTRA_SIMD & SPECTRA_SIMD_SSE2)
    spectra_position_x *p_x = ecs_field(it, spectra_position_x, 1);
    spectra_position_y *p_y = ecs_field(it, spectra_position_y, 2);
    spectra_velocity_x *v_x = ecs_field(it, spectra_velocity_x, 3);
    spectra_velocity_y *v_y = ecs_field(it, spectra_velocity_y, 4);

    /* Iterate entities for the current table */
    for (int i = 0; i < it->count; i += 4)
    {
        __m128 p_x_128 = _mm_load_ps(&p_x[i].value);
        __m128 p_y_128 = _mm_load_ps(&p_y[i].value);
        __m128 v_x_128 = _mm_load_ps(&v_x[i].value);
        __m128 v_y_128 = _mm_load_ps(&v_y[i].value);

        p_x_128 = _mm_add_ps(p_x_128, v_x_128);
        p_y_128 = _mm_add_ps(p_y_128, v_y_128);

        _mm_store_ps(&p_x[i].value, p_x_128);
        _mm_store_ps(&p_y[i].value, p_y_128);
    }
#endif
}
