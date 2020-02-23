cmake_minimum_required(VERSION 3.15)

project(sfx-bitops LANGUAGES C CXX)

set(SFX_BO_STANDALONE_PROJECT FALSE)
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(SFX_BO_STANDALONE_PROJECT TRUE)

  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)

  enable_testing()
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
  list(APPEND cflags "-Weverything" "-Wno-c++98-compat"
       "-Wno-c++98-compat-pedantic")
elseif(CMAKE_C_COMPILER_ID MATCHES GNU)
  list(APPEND cflags "-Wall" "-Wextra")
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
    target_compile_options(${tgt} PRIVATE ${cflags})
    add_test(NAME ${tgt} COMMAND ${tgt})
  endmacro()

  sfx_bo_add_test(main main.c)
  sfx_bo_add_test(main-cxx main-cxx.cpp)
endif()
