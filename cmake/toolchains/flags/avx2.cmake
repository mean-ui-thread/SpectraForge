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

include_guard(GLOBAL)

include(polly_add_cache_flag)

if(CMAKE_GENERATOR MATCHES "^Visual Studio.*$")
    polly_add_cache_flag(CMAKE_C_FLAGS "/arch:AVX2")
    polly_add_cache_flag(CMAKE_CXX_FLAGS "/arch:AVX2")
else()
    polly_add_cache_flag(CMAKE_C_FLAGS "-march=haswell -mtune=skylake")
    polly_add_cache_flag(CMAKE_CXX_FLAGS "-march=haswell -mtune=skylake")
endif()
