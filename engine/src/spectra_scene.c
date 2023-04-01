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

#include <stdlib.h>
#include <string.h>

#define priv_to_pub(priv) (spectra_scene){.id = (uint64_t)priv}
#define pub_to_priv(pub) (spectra_scene_priv *)pub.id

spectra_scene spectra_scene_create() {
    spectra_scene_priv *priv = malloc(sizeof(struct spectra_scene_priv));
    priv->count = 0;

    return priv_to_pub(priv);
}

void spectra_scene_destroy(spectra_scene scene) {
    spectra_scene_priv *priv = pub_to_priv(scene);
    free(priv);
}


void _spectra_scene_priv_update_local_matrix(spectra_scene_priv *priv) {
    for (int i = 0; i < priv->count; i+= 4) {

    }
}
