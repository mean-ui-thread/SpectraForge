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
#include <gtest/gtest.h>
#include <spectra.h>

TEST(SceneTest, AddNode){
    spectra_scene scene = spectra_scene_create();
    ASSERT_NE(scene.id, 0);

    spectra_node node1 = spectra_scene_add_node(scene);
    ASSERT_NE(node1.id, 0);

    spectra_node node2 = spectra_scene_add_node(scene);
    ASSERT_NE(node2.id, 0);

    ASSERT_NE(node1.id, node2.id);

    spectra_scene_set_node_position(scene, node1, 1.0f, 2.0f, 3.0f);
    spectra_scene_set_node_rotation(scene, node1, 4.0f, 5.0f, 6.0f);
    spectra_scene_set_node_scale(scene, node1, 7.0f, 8.0f, 9.0f);

    spectra_scene_set_node_position(scene, node2, 10.0f, 11.0f, 12.0f);
    spectra_scene_set_node_rotation(scene, node2, 13.0f, 14.0f, 15.0f);
    spectra_scene_set_node_scale(scene, node2, 16.0f, 17.0f, 18.0f);

    float position_x, position_y, position_z;
    float rotation_x, rotation_y, rotation_z;
    float scale_x, scale_y, scale_z;

    spectra_scene_get_node_position(scene, node1, &position_x, &position_y, &position_z);
    ASSERT_FLOAT_EQ(position_x, 1.0f);
    ASSERT_FLOAT_EQ(position_y, 2.0f);
    ASSERT_FLOAT_EQ(position_z, 3.0f);

    spectra_scene_get_node_rotation(scene, node1, &rotation_x, &rotation_y, &rotation_z);
    ASSERT_FLOAT_EQ(rotation_x, 4.0f);
    ASSERT_FLOAT_EQ(rotation_y, 5.0f);
    ASSERT_FLOAT_EQ(rotation_z, 6.0f);

    spectra_scene_get_node_scale(scene, node1, &scale_x, &scale_y, &scale_z);
    ASSERT_FLOAT_EQ(scale_x, 7.0f);
    ASSERT_FLOAT_EQ(scale_y, 8.0f);
    ASSERT_FLOAT_EQ(scale_z, 9.0f);

    spectra_scene_get_node_position(scene, node2, &position_x, &position_y, &position_z);
    ASSERT_FLOAT_EQ(position_x, 10.0f);
    ASSERT_FLOAT_EQ(position_y, 11.0f);
    ASSERT_FLOAT_EQ(position_z, 12.0f);


    spectra_scene_destroy(scene);
}