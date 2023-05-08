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

#ifndef SPECTRA_SCENE_DEFAULT_CAPACITY
#define SPECTRA_SCENE_DEFAULT_CAPACITY 1024
#endif

#define spectra_scene_priv_to_pub(priv) \
    (spectra_scene)                     \
    {                                   \
        .id = (uint64_t)priv            \
    }
#define spectra_scene_pub_to_priv(pub) (spectra_scene_priv *)(pub.id)

#define index_to_node(index) \
    (spectra_node)           \
    {                        \
        .id = index + 1      \
    }
#define node_to_index(node) (uint32_t)(node.id - 1)

typedef struct spectra_scene_priv
{
    uint32_t node_count;
    uint32_t node_capacity;

    bool *dirty;
    float *position_x;
    float *position_y;
    float *position_z;
    float *rotation_x;
    float *rotation_y;
    float *rotation_z;
    float *scale_x;
    float *scale_y;
    float *scale_z;

    float *local_m00;
    float *local_m01;
    float *local_m02;
    // float *local_m03; // always 0.0f
    float *local_m10;
    float *local_m11;
    float *local_m12;
    // float *local_m13; // always 0.0f
    float *local_m20;
    float *local_m21;
    float *local_m22;
    // float *local_m23; // always 0.0f
    float *local_m30;
    float *local_m31;
    float *local_m32;
    // float *local_m33; // always 1.0f

} spectra_scene_priv;

void _spectra_scene_priv_update_local_matrix(spectra_scene_priv *priv);

#endif // SPECTRA_SCENE_PRIV_H