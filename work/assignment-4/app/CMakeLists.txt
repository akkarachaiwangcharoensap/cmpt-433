cmake_minimum_required(VERSION 3.20.0)
project(assignment-4 VERSION 1.0 DESCRIPTION "Neopixel - Linux" LANGUAGES C)

# Compiler options (inherited by sub-folders)
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Werror -Wpedantic -Wextra)
add_compile_options(-fdiagnostics-color)


include_directories(include)
file(GLOB MY_SOURCES "src/*.c")
add_executable(neopixel ${MY_SOURCES})

# Make use of the HAL library
target_link_libraries(neopixel LINK_PRIVATE hal)
target_link_libraries(neopixel LINK_PRIVATE lcd)
target_link_libraries(neopixel LINK_PRIVATE lgpio)

# Enable PThread library for linking
add_compile_options(-pthread)
add_link_options(-pthread)

# What folders to build
add_subdirectory(lgpio)
add_subdirectory(lcd)
add_subdirectory(hal)

# ---------------- NEW! ----------------
# ALSA support
# find_package(ALSA REQUIRED)
# target_link_libraries(neopixel LINK_PRIVATE asound)

# PTHREAD support
find_package(Threads REQUIRED)
target_link_libraries(neopixel LINK_PRIVATE Threads::Threads)

# Copy executable to final location (change `neopixel` to project name as needed)
add_custom_command(TARGET neopixel POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:neopixel>"
     "~/cmpt-433/public/assignment-4/neopixel" 
  COMMENT "Copying ARM executable to public NFS directory")


# ---------------- NEW! ----------------
# Copy the WAV folder to NFS
# add_custom_command(TARGET neopixel POST_BUILD 
#   COMMAND "${CMAKE_COMMAND}" -E copy_directory
#      "${CMAKE_SOURCE_DIR}/wave-files"
#      "~/cmpt-433/public/assignment-3/wave-files" 
#   COMMENT "Copying WAVE files to public NFS directory")

# add_custom_command(TARGET neopixel POST_BUILD 
#   COMMAND "${CMAKE_COMMAND}" -E copy_directory
#      "${CMAKE_SOURCE_DIR}/server"
#      "~/cmpt-433/public/assignment-3/server" 
#   COMMENT "Copying WAVE files to public NFS directory")