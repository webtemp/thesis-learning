cmake_minimum_required(VERSION 3.30)

# import std; is still marked experimental in CMake 4.x and needs an unlock key.
# The key is different in every CMake version, so pick it by version.
# Must be set before project(). To find the key for a new version:
#   strings <path-to-cmake> | grep -B1 CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.4)
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")  # 4.4.x, Homebrew
else()
  set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")  # 4.3.x, bundled in CLion
endif()

project(thesis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD ON)

# One program: main.cpp plus every module in sorts/.
file(GLOB SORT_MODULES CONFIGURE_DEPENDS sorts/*.cppm)
file(GLOB GRAPH_MODULES CONFIGURE_DEPENDS graphs/*.cppm)

add_executable(main main.cpp)

target_sources(main PUBLIC FILE_SET CXX_MODULES FILES ${SORT_MODULES} ${GRAPH_MODULES})
target_compile_options(main PRIVATE -Wall -Wextra)

# Guard against CLion Nova inserting #include on autocomplete (bug CPP-48644).
# Any #include of a standard header next to import std; breaks the build with "conflicting declaration" errors
# deep inside the compiler's own files. This target runs before main compiles and names the file and line instead.
add_custom_target(check_no_includes
        COMMAND sh -c "if grep -rn --include='*.cpp' --include='*.cppm' '^[[:space:]]*#include' '${CMAKE_SOURCE_DIR}'; then echo 'ERROR: #include found, use import std; instead'; exit 1; fi"
        VERBATIM)
add_dependencies(main check_no_includes)
