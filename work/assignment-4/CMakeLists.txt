# # SPDX-License-Identifier: Apache-2.0

# cmake_minimum_required(VERSION 3.20.0)
# find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
# project(neopixel)


# # CMake Build Configuration for root of project
# # cmake_minimum_required(VERSION 3.20.0)
# # project(assignment-4 VERSION 1.0 DESCRIPTION "Neopixel" LANGUAGES C)

# # Compiler options (inherited by sub-folders)
# set(CMAKE_C_STANDARD 11)
# add_compile_options(-Wall -Werror -Wpedantic -Wextra)
# add_compile_options(-fdiagnostics-color)

# # Enable address sanitizer
# # (Comment this out to make your code faster)
# # add_compile_options(-fsanitize=address)
# # add_link_options(-fsanitize=address)

# # Enable PThread library for linking
# add_compile_options(-pthread)
# add_link_options(-pthread)

# # What folders to build
# add_subdirectory(lgpio)
# add_subdirectory(lcd)
# add_subdirectory(hal)
# # add_subdirectory(app)

# target_sources(app PRIVATE src/main.c)

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(neopixel)

target_sources(app PRIVATE src/main.c)
