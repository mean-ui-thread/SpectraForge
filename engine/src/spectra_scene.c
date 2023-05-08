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

#include <math.h>

spectra_scene spectra_scene_create()
{
    spectra_scene_priv *priv = malloc(sizeof(struct spectra_scene_priv));

    priv->node_count = 0;
    priv->node_capacity = SPECTRA_SCENE_DEFAULT_CAPACITY;
    priv->dirty = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(bool));
    priv->position_x = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->position_y = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->position_z = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->rotation_x = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->rotation_y = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->rotation_z = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->scale_x = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->scale_y = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->scale_z = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m00 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m01 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m02 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    // priv->local_m03 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float)); // always 0.0f
    priv->local_m10 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m11 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m12 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    // priv->local_m13 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float)); // always 0.0f
    priv->local_m20 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m21 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m22 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    // priv->local_m23 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float)); // always 0.0f
    priv->local_m30 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m31 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    priv->local_m32 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float));
    // priv->local_m33 = spectra_aligned_malloc(16, SPECTRA_SCENE_DEFAULT_CAPACITY * sizeof(float)); // always 1.0f

    return spectra_scene_priv_to_pub(priv);
}

void spectra_scene_destroy(spectra_scene scene)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);

    spectra_aligned_free(priv->dirty);
    spectra_aligned_free(priv->position_x);
    spectra_aligned_free(priv->position_y);
    spectra_aligned_free(priv->position_z);
    spectra_aligned_free(priv->rotation_x);
    spectra_aligned_free(priv->rotation_y);
    spectra_aligned_free(priv->rotation_z);
    spectra_aligned_free(priv->scale_x);
    spectra_aligned_free(priv->scale_y);
    spectra_aligned_free(priv->scale_z);
    spectra_aligned_free(priv->local_m00);
    spectra_aligned_free(priv->local_m01);
    spectra_aligned_free(priv->local_m02);
    // spectra_aligned_free(priv->local_m03);
    spectra_aligned_free(priv->local_m10);
    spectra_aligned_free(priv->local_m11);
    spectra_aligned_free(priv->local_m12);
    // spectra_aligned_free(priv->local_m13);
    spectra_aligned_free(priv->local_m20);
    spectra_aligned_free(priv->local_m21);
    spectra_aligned_free(priv->local_m22);
    // spectra_aligned_free(priv->local_m23);
    spectra_aligned_free(priv->local_m30);
    spectra_aligned_free(priv->local_m31);
    spectra_aligned_free(priv->local_m32);
    // spectra_aligned_free(priv->local_m33);

    free(priv);
}

void spectra_scene_begin(spectra_scene scene, float dt, float width, float height, spectra_clear_flags clear_flags)
{
    // TODO render target, clear, animation, etc
}

void spectra_scene_end(spectra_scene scene)
{
    // TODO flush

    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    _spectra_scene_priv_update_local_matrix(priv);

    // TODO render
}

spectra_node spectra_scene_add_node(spectra_scene scene)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);

    if (priv->node_count == priv->node_capacity)
    {
        priv->node_capacity = priv->node_capacity == 0 ? 1 : priv->node_capacity * 2;
        priv->dirty = spectra_aligned_realloc(16, priv->dirty, priv->node_capacity * sizeof(bool));
        priv->position_x = spectra_aligned_realloc(16, priv->position_x, priv->node_capacity * sizeof(float));
        priv->position_y = spectra_aligned_realloc(16, priv->position_y, priv->node_capacity * sizeof(float));
        priv->position_z = spectra_aligned_realloc(16, priv->position_z, priv->node_capacity * sizeof(float));
        priv->rotation_x = spectra_aligned_realloc(16, priv->rotation_x, priv->node_capacity * sizeof(float));
        priv->rotation_y = spectra_aligned_realloc(16, priv->rotation_y, priv->node_capacity * sizeof(float));
        priv->rotation_z = spectra_aligned_realloc(16, priv->rotation_z, priv->node_capacity * sizeof(float));
        priv->scale_x = spectra_aligned_realloc(16, priv->scale_x, priv->node_capacity * sizeof(float));
        priv->scale_y = spectra_aligned_realloc(16, priv->scale_y, priv->node_capacity * sizeof(float));
        priv->scale_z = spectra_aligned_realloc(16, priv->scale_z, priv->node_capacity * sizeof(float));
        priv->local_m00 = spectra_aligned_realloc(16, priv->local_m00, priv->node_capacity * sizeof(float));
        priv->local_m01 = spectra_aligned_realloc(16, priv->local_m01, priv->node_capacity * sizeof(float));
        priv->local_m02 = spectra_aligned_realloc(16, priv->local_m02, priv->node_capacity * sizeof(float));
        // priv->local_m03 = spectra_aligned_realloc(16, priv->local_m03, priv->capacity * sizeof(float));
        priv->local_m10 = spectra_aligned_realloc(16, priv->local_m10, priv->node_capacity * sizeof(float));
        priv->local_m11 = spectra_aligned_realloc(16, priv->local_m11, priv->node_capacity * sizeof(float));
        priv->local_m12 = spectra_aligned_realloc(16, priv->local_m12, priv->node_capacity * sizeof(float));
        // priv->local_m13 = spectra_aligned_realloc(16, priv->local_m13, priv->capacity * sizeof(float));
        priv->local_m20 = spectra_aligned_realloc(16, priv->local_m20, priv->node_capacity * sizeof(float));
        priv->local_m21 = spectra_aligned_realloc(16, priv->local_m21, priv->node_capacity * sizeof(float));
        priv->local_m22 = spectra_aligned_realloc(16, priv->local_m22, priv->node_capacity * sizeof(float));
        // priv->local_m23 = spectra_aligned_realloc(16, priv->local_m23, priv->capacity * sizeof(float));
        priv->local_m30 = spectra_aligned_realloc(16, priv->local_m30, priv->node_capacity * sizeof(float));
        priv->local_m31 = spectra_aligned_realloc(16, priv->local_m31, priv->node_capacity * sizeof(float));
        priv->local_m32 = spectra_aligned_realloc(16, priv->local_m32, priv->node_capacity * sizeof(float));
        // priv->local_m33 = spectra_aligned_realloc(16, priv->local_m33, priv->capacity * sizeof(float));
    }

    int index = priv->node_count++;
    priv->dirty[index] = true;
    priv->position_x[index] = 0.0f;
    priv->position_y[index] = 0.0f;
    priv->position_z[index] = 0.0f;
    priv->rotation_x[index] = 0.0f;
    priv->rotation_y[index] = 0.0f;
    priv->rotation_z[index] = 0.0f;
    priv->scale_x[index] = 1.0f;
    priv->scale_y[index] = 1.0f;
    priv->scale_z[index] = 1.0f;
    priv->local_m00[index] = 1.0f;
    priv->local_m01[index] = 0.0f;
    priv->local_m02[index] = 0.0f;
    // priv->local_m03[index] = 0.0f;
    priv->local_m10[index] = 0.0f;
    priv->local_m11[index] = 1.0f;
    priv->local_m12[index] = 0.0f;
    // priv->local_m13[index] = 0.0f;
    priv->local_m20[index] = 0.0f;
    priv->local_m21[index] = 0.0f;
    priv->local_m22[index] = 1.0f;
    // priv->local_m23[index] = 0.0f;
    priv->local_m30[index] = 0.0f;
    priv->local_m31[index] = 0.0f;
    priv->local_m32[index] = 0.0f;
    // priv->local_m33[index] = 1.0f;

    return index_to_node(index);
}

void spectra_scene_set_node_position(spectra_scene scene, spectra_node node, float x, float y, float z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    priv->position_x[index] = x;
    priv->position_y[index] = y;
    priv->position_z[index] = z;
    priv->dirty[index] = true;
}

void spectra_scene_set_node_rotation(spectra_scene scene, spectra_node node, float x, float y, float z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    priv->rotation_x[index] = x;
    priv->rotation_y[index] = y;
    priv->rotation_z[index] = z;
    priv->dirty[index] = true;
}

void spectra_scene_set_node_scale(spectra_scene scene, spectra_node node, float x, float y, float z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    priv->scale_x[index] = x;
    priv->scale_y[index] = y;
    priv->scale_z[index] = z;
    priv->dirty[index] = true;
}

void spectra_scene_get_node_position(spectra_scene scene, spectra_node node, float *x, float *y, float *z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    *x = priv->position_x[index];
    *y = priv->position_y[index];
    *z = priv->position_z[index];
}

void spectra_scene_get_node_rotation(spectra_scene scene, spectra_node node, float *x, float *y, float *z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    *x = priv->rotation_x[index];
    *y = priv->rotation_y[index];
    *z = priv->rotation_z[index];
}

void spectra_scene_get_node_scale(spectra_scene scene, spectra_node node, float *x, float *y, float *z)
{
    spectra_scene_priv *priv = spectra_scene_pub_to_priv(scene);
    int index = node_to_index(node);
    *x = priv->scale_x[index];
    *y = priv->scale_y[index];
    *z = priv->scale_z[index];
}

#if (SPECTRA_SIMD)
void _spectra_scene_priv_update_local_matrix(spectra_scene_priv *priv)
{
    for (int i = 0; i < priv->node_count; i += SPECTRA_FLOAT32X4_COUNT)
    {
        spectra_float32x4 pos128_x = spectra_simd_load(&priv->position_x[i]);
        spectra_float32x4 pos128_y = spectra_simd_load(&priv->position_y[i]);
        spectra_float32x4 pos128_z = spectra_simd_load(&priv->position_z[i]);

        spectra_float32x4 rot128_x = spectra_simd_load(&priv->rotation_x[i]);
        spectra_float32x4 rot128_y = spectra_simd_load(&priv->rotation_y[i]);
        spectra_float32x4 rot128_z = spectra_simd_load(&priv->rotation_z[i]);

        spectra_float32x4 scale128_x = spectra_simd_load(&priv->scale_x[i]);
        spectra_float32x4 scale128_y = spectra_simd_load(&priv->scale_y[i]);
        spectra_float32x4 scale128_z = spectra_simd_load(&priv->scale_z[i]);

        spectra_float32x4 rot128_cx = spectra_simd_cos(rot128_x);
        spectra_float32x4 rot128_cy = spectra_simd_cos(rot128_y);
        spectra_float32x4 rot128_cz = spectra_simd_cos(rot128_z);

        spectra_float32x4 rot128_sx = spectra_simd_sin(rot128_x);
        spectra_float32x4 rot128_sy = spectra_simd_sin(rot128_y);
        spectra_float32x4 rot128_sz = spectra_simd_sin(rot128_z);

        spectra_simd_store(&priv->local_m00[i], spectra_simd_mul(scale128_x, spectra_simd_mul(rot128_cy, rot128_cz)));
        spectra_simd_store(&priv->local_m01[i], spectra_simd_mul(scale128_x, spectra_simd_mul(rot128_cy, rot128_sz)));
        spectra_simd_store(&priv->local_m02[i], spectra_simd_mul(scale128_x, spectra_simd_mul(rot128_sy, rot128_cz)));
        // spectra_simd_store(&priv->local_m03[i], spectra_simd_set_all(0.0f)); // always 0.0f

        spectra_simd_store(&priv->local_m10[i], spectra_simd_mul(scale128_y, spectra_simd_mul(spectra_simd_mul(rot128_sx, rot128_sy), rot128_cz)));
        spectra_simd_store(&priv->local_m11[i], spectra_simd_mul(scale128_y, spectra_simd_mul(spectra_simd_mul(rot128_sx, rot128_sy), rot128_sz)));
        spectra_simd_store(&priv->local_m12[i], spectra_simd_mul(scale128_y, spectra_simd_mul(rot128_sx, rot128_cy)));
        // spectra_simd_store(&priv->local_m13[i], spectra_simd_set_all(0.0f)); // always 0.0f

        spectra_simd_store(&priv->local_m20[i], spectra_simd_mul(scale128_z, spectra_simd_mul(spectra_simd_mul(rot128_cx, rot128_sy), rot128_cz)));
        spectra_simd_store(&priv->local_m21[i], spectra_simd_mul(scale128_z, spectra_simd_mul(spectra_simd_mul(rot128_cx, rot128_sy), rot128_sz)));
        spectra_simd_store(&priv->local_m22[i], spectra_simd_mul(scale128_z, spectra_simd_mul(rot128_cx, rot128_cy)));
        // spectra_simd_store(&priv->local_m23[i], spectra_simd_set_all(0.0f)); // always 0.0f

        spectra_simd_store(&priv->local_m30[i], pos128_x);
        spectra_simd_store(&priv->local_m31[i], pos128_y);
        spectra_simd_store(&priv->local_m32[i], pos128_z);
        // spectra_simd_store(&priv->local_m33[i], spectra_simd_set_all(1.0f)); // always 1.0f
    }
}
#else
void _spectra_scene_priv_update_local_matrix(spectra_scene_priv *priv)
{
    for (int i = 0; i < priv->node_count; ++i)
    {
        float pos_x = priv->position_x[i];
        float pos_y = priv->position_y[i];
        float pos_z = priv->position_z[i];

        float rot_x = priv->rotation_x[i];
        float rot_y = priv->rotation_y[i];
        float rot_z = priv->rotation_z[i];

        float scale_x = priv->scale_x[i];
        float scale_y = priv->scale_y[i];
        float scale_z = priv->scale_z[i];

        float rot_cx = cosf(rot_x);
        float rot_cy = cosf(rot_y);
        float rot_cz = cosf(rot_z);

        float rot_sx = sinf(rot_x);
        float rot_sy = sinf(rot_y);
        float rot_sz = sinf(rot_z);

        priv->local_m00[i] = scale_x * rot_cy * rot_cz;
        priv->local_m01[i] = scale_x * rot_cy * rot_sz;
        priv->local_m02[i] = scale_x * -rot_sy;
        // priv->local_m03[i] = 0.0f; // always 0.0f

        priv->local_m10[i] = scale_y * (rot_sx * rot_sy * rot_cz - rot_cx * rot_sz);
        priv->local_m11[i] = scale_y * (rot_sx * rot_sy * rot_sz + rot_cx * rot_cz);
        priv->local_m12[i] = scale_y * rot_sx * rot_cy;
        // priv->local_m13[i] = 0.0f; // always 0.0f

        priv->local_m20[i] = scale_z * (rot_cx * rot_sy * rot_cz + rot_sx * rot_sz);
        priv->local_m21[i] = scale_z * (rot_cx * rot_sy * rot_sz - rot_sx * rot_cz);
        priv->local_m22[i] = scale_z * rot_cx * rot_cy;
        // priv->local_m23[i] = 0.0f; // always 0.0f

        priv->local_m30[i] = pos_x;
        priv->local_m31[i] = pos_y;
        priv->local_m32[i] = pos_z;
        // priv->local_m33[i] = 1.0f; // always 1.0f
    }
}
#endif