cmake_minimum_required(VERSION 3.15)

set(SFX_BO_STANDALONE_PROJECT FALSE)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(SFX_BO_STANDALONE_PROJECT TRUE)
endif()

if(SFX_BO_STANDALONE_PROJECT)
  project(sfx-bitops LANGUAGES C CXX)

  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(NOT TARGET header-utils::header-utils)
  add_subdirectory(deps/cxx-header-utils)
endif()

add_library(sfx-bitops INTERFACE)
target_include_directories(sfx-bitops
                           INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_link_libraries(sfx-bitops INTERFACE header-utils::header-utils)
add_library(sfx-bitops::sfx-bitops ALIAS sfx-bitops)

if(SFX_BO_STANDALONE_PROJECT)
  macro(sfx_bo_add_test tgt)
    add_executable(${tgt} test/${ARGN})
    target_link_libraries(${tgt} sfx-bitops::sfx-bitops)
  endmacro()

  sfx_bo_add_test(main main.c)
  sfx_bo_add_test(main-cxx main-cxx.cpp)
endif()
