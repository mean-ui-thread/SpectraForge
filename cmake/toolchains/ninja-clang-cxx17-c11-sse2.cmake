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

include("${CMAKE_CURRENT_LIST_DIR}/polly/utilities/polly_init.cmake")

polly_init(
    "clang / c++17 support / C11 support / SSE2 Support"
    "Ninja Multi-Config"
)

include("${CMAKE_CURRENT_LIST_DIR}/polly/utilities/polly_common.cmake")

include("${CMAKE_CURRENT_LIST_DIR}/polly/compiler/clang.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/polly/flags/cxx17.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/polly/flags/c11.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/flags/sse2.cmake")

set(HUNTER_CONFIGURATION_TYPES Debug Release RelWithDebInfo)
