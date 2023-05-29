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

#include <stdio.h>

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

    /* Register system */
    ECS_SYSTEM(world, _spectra_move_entity, EcsOnUpdate, spectra_position_x, spectra_position_y, spectra_velocity_x, spectra_velocity_y);

    return spectra_world_to_scene(world);
}

void spectra_scene_destroy(spectra_scene scene)
{
    ecs_world_t *world = spectra_scene_to_world(scene);

    ecs_fini(world);
}

void _spectra_move_entity(ecs_iter_t *it)
{
    spectra_position_x *p_x = ecs_field(it, spectra_position_x, 1);
    spectra_position_y *p_y = ecs_field(it, spectra_position_y, 2);
    spectra_velocity_x *v_x = ecs_field(it, spectra_velocity_x, 3);
    spectra_velocity_y *v_y = ecs_field(it, spectra_velocity_y, 4);

    /* Print the set of components for the iterated over entities */
    char *type_str = ecs_table_str(it->world, it->table);
    printf("Move entities with [%s]\n", type_str);
    ecs_os_free(type_str);

    /* Iterate entities for the current table */
#if (SPECTRA_SIMD)
    for (int i = 0; i < it->count; i += SPECTRA_FLOAT32X4_COUNT)
    {
        spectra_float32x4 p_x_128 = spectra_simd_load(&p_x[i].value);
        spectra_float32x4 p_y_128 = spectra_simd_load(&p_y[i].value);
        spectra_float32x4 v_x_128 = spectra_simd_load(&v_x[i].value);
        spectra_float32x4 v_y_128 = spectra_simd_load(&v_y[i].value);

        p_x_128 = spectra_simd_add(p_x_128, v_x_128);
        p_y_128 = spectra_simd_add(p_y_128, v_y_128);

        spectra_simd_store(&p_x[i].value, p_x_128);
        spectra_simd_store(&p_y[i].value, p_y_128);
    }
#else
    for (int i = 0; i < it->count; i++)
    {
        p_x[i].value += v_x[i].value;
        p_y[i].value += v_y[i].value;
    }
#endif
}