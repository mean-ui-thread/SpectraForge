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

#define NODE_MAX 1024

typedef struct spectra_scene_priv {
    uint32_t count;
    float position_x[NODE_MAX];
    float position_y[NODE_MAX];
    float position_z[NODE_MAX];
    float rotation_x[NODE_MAX];
    float rotation_y[NODE_MAX];
    float rotation_z[NODE_MAX];
    float scale_x[NODE_MAX];
    float scale_y[NODE_MAX];
    float scale_z[NODE_MAX];
    float anchor_x[NODE_MAX];
    float anchor_y[NODE_MAX];
    float anchor_z[NODE_MAX];

    float local_m00[NODE_MAX];
    float local_m01[NODE_MAX];
    float local_m02[NODE_MAX];
    float local_m03[NODE_MAX];
    float local_m10[NODE_MAX];
    float local_m11[NODE_MAX];
    float local_m12[NODE_MAX];
    float local_m13[NODE_MAX];
    float local_m20[NODE_MAX];
    float local_m21[NODE_MAX];
    float local_m22[NODE_MAX];
    float local_m23[NODE_MAX];
    float local_m30[NODE_MAX];
    float local_m31[NODE_MAX];
    float local_m32[NODE_MAX];
    float local_m33[NODE_MAX];

} spectra_scene_priv;

void _spectra_scene_priv_update_local_matrix(spectra_scene_priv *priv);

#endif // SPECTRA_SCENE_PRIV_H