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
#include <spectra_predef.h>
#include <spectra_simd.h>
#include <spectra_math.h>
#include <spectra_system.h>

#include <cpuinfo.h>

#include <stdio.h>
#include <stddef.h>
#include <assert.h>

spectra_scene spectra_scene_create(int argc, char **argv)
{
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    /* Register components */
    ECS_COMPONENT(world, spectra_position_x);
    ECS_COMPONENT(world, spectra_position_y);
    ECS_COMPONENT(world, spectra_rotation_z);
    ECS_COMPONENT(world, spectra_scale_x);
    ECS_COMPONENT(world, spectra_scale_y);
    ECS_COMPONENT(world, spectra_velocity_x);
    ECS_COMPONENT(world, spectra_velocity_y);

    cpuinfo_initialize();

    /* Register system */
    if (cpuinfo_has_x86_avx512f())
    {
        ECS_SYSTEM(world, spectra_move_entity_avx512, EcsOnUpdate, spectra_position_x, spectra_position_y, spectra_velocity_x, spectra_velocity_y);
    }
    else if (cpuinfo_has_x86_avx())
    {
        ECS_SYSTEM(world, spectra_move_entity_avx, EcsOnUpdate, spectra_position_x, spectra_position_y, spectra_velocity_x, spectra_velocity_y);
    }
    else if (cpuinfo_has_x86_sse2())
    {
        ECS_SYSTEM(world, spectra_move_entity_sse2, EcsOnUpdate, spectra_position_x, spectra_position_y, spectra_velocity_x, spectra_velocity_y);
    }
    else
    {
        ECS_SYSTEM(world, spectra_move_entity, EcsOnUpdate, spectra_position_x, spectra_position_y, spectra_velocity_x, spectra_velocity_y);
    }

    cpuinfo_deinitialize();

    return spectra_world_to_scene(world);
}

void spectra_scene_destroy(spectra_scene scene)
{
    ecs_world_t *world = spectra_scene_to_world(scene);

    ecs_fini(world);
}
