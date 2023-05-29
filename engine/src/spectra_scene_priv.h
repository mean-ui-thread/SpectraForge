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

#ifndef SPECTRA_SCENE_PRIV_H
#define SPECTRA_SCENE_PRIV_H

#include <spectra_scene.h>

#include <flecs.h>

#ifndef SPECTRA_SCENE_DEFAULT_CAPACITY
#define SPECTRA_SCENE_DEFAULT_CAPACITY 1024
#endif

#define spectra_world_to_scene(world) \
    (spectra_scene)                   \
    {                                 \
        .id = (uint64_t)world         \
    }

typedef struct
{
    float value;
} spectra_position_x, spectra_position_y, spectra_rotation_z, spectra_scale_x, spectra_scale_y, spectra_velocity_x, spectra_velocity_y;

#define spectra_scene_to_world(pub) (ecs_world_t *)(pub.id)

void _spectra_move_entity(ecs_iter_t *it);

#endif // SPECTRA_SCENE_PRIV_H