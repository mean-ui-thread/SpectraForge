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
#include <spectra_scene_priv.h>

void spectra_move_entity(ecs_iter_t *it)
{
    spectra_position_x *p_x = ecs_field(it, spectra_position_x, 1);
    spectra_position_y *p_y = ecs_field(it, spectra_position_y, 2);
    spectra_velocity_x *v_x = ecs_field(it, spectra_velocity_x, 3);
    spectra_velocity_y *v_y = ecs_field(it, spectra_velocity_y, 4);

    /* Iterate entities for the current table */
    for (int i = 0; i < it->count; ++i)
    {
        p_x[i].value += v_x[i].value;
        p_y[i].value += v_y[i].value;
    }
}
