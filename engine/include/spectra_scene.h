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

#ifndef SPECTRA_SCENE_H
#define SPECTRA_SCENE_H

#include <stdint.h>
#include <stdbool.h>

#include <spectra_math.h>

typedef enum
{
    spectra_clear_none = 0x0,
    spectra_clear_color = 0x1,
    spectra_clear_depth = 0x2,
    spectra_clear_stencil = 0x4
} spectra_clear_flags_t;
typedef uint8_t spectra_clear_flags;

typedef struct spectra_scene
{
    uint64_t id;
} spectra_scene;
typedef struct spectra_node
{
    uint64_t id;
} spectra_node;

#if defined(__cplusplus)
extern "C"
{
#endif

    spectra_scene spectra_scene_create(int argc, char **argv);
    void spectra_scene_destroy(spectra_scene scene);
    void spectra_scene_begin(spectra_scene scene, float dt, float width, float height, spectra_clear_flags clear_flags);
    void spectra_scene_end(spectra_scene scene);

    spectra_node spectra_scene_add_node(spectra_scene scene);

    void spectra_scene_set_node_position(spectra_scene scene, spectra_node node, float x, float y, float z);
    void spectra_scene_set_node_rotation(spectra_scene scene, spectra_node node, float x, float y, float z);
    void spectra_scene_set_node_scale(spectra_scene scene, spectra_node node, float x, float y, float z);

    void spectra_scene_get_node_position(spectra_scene scene, spectra_node node, float *x, float *y, float *z);
    void spectra_scene_get_node_rotation(spectra_scene scene, spectra_node node, float *x, float *y, float *z);
    void spectra_scene_get_node_scale(spectra_scene scene, spectra_node node, float *x, float *y, float *z);

#if defined(__cplusplus)
}
#endif

#endif // SPECTRA_SCENE_H