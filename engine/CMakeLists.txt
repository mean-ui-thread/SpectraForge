###############################################################################
# Copyright (c) 2023 Mean UI Thread
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
##############################################################################/

include(spectra_simd)

add_subdirectory(3rdparty)

# https://hunter.readthedocs.io/en/latest/packages/pkg/cpuinfo.html
hunter_add_package(cpuinfo)
find_package(cpuinfo CONFIG REQUIRED)

# https://hunter.readthedocs.io/en/latest/packages/pkg/SDL2.html
hunter_add_package(SDL2)
find_package(SDL2 CONFIG REQUIRED)


add_library(SpectraForge
    include/spectra_math.h
    include/spectra_scene.h
    include/spectra.h
    src/systems/spectra_system_sdl2.c
    src/systems/spectra_system_sdl2.h
    src/spectra_predef.h
    src/spectra_scene_priv.h
    src/spectra_scene.c
    src/spectra_simd.h
    src/spectra_system_simd_avx2.c
    src/spectra_system_simd_avx512.c
    src/spectra_system_simd_sse2.c
    src/spectra_system.c
    src/spectra_system.h
    src/spectra.c
)

set_source_files_properties(src/spectra_system_simd_avx2.c PROPERTIES COMPILE_FLAGS ${SPECTRA_AVX2_COMPILE_FLAG})
set_source_files_properties(src/spectra_system_simd_avx512.c PROPERTIES COMPILE_FLAGS ${SPECTRA_AVX512_COMPILE_FLAG})

target_link_libraries(SpectraForge 
    PUBLIC
        cpuinfo::cpuinfo        
        flecs_static
        SDL2::SDL2
)

target_include_directories(SpectraForge
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

add_subdirectory(tests)