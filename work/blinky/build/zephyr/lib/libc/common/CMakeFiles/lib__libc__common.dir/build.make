# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aki/cmpt-433/work/blinky

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aki/cmpt-433/work/blinky/build

# Include any dependencies generated for this target.
include zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/flags.make

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/flags.make
zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/abort.c
zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj -MF CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj.d -o CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/abort.c

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/abort.c > CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.i

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/abort.c -o CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.s

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/flags.make
zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/malloc.c
zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj -MF CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj.d -o CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/malloc.c

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/malloc.c > CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.i

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/common/source/stdlib/malloc.c -o CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.s

# Object files for target lib__libc__common
lib__libc__common_OBJECTS = \
"CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj" \
"CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj"

# External object files for target lib__libc__common
lib__libc__common_EXTERNAL_OBJECTS =

zephyr/lib/libc/common/liblib__libc__common.a: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/abort.c.obj
zephyr/lib/libc/common/liblib__libc__common.a: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/source/stdlib/malloc.c.obj
zephyr/lib/libc/common/liblib__libc__common.a: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/build.make
zephyr/lib/libc/common/liblib__libc__common.a: zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library liblib__libc__common.a"
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && $(CMAKE_COMMAND) -P CMakeFiles/lib__libc__common.dir/cmake_clean_target.cmake
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib__libc__common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/build: zephyr/lib/libc/common/liblib__libc__common.a
.PHONY : zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/build

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/clean:
	cd /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common && $(CMAKE_COMMAND) -P CMakeFiles/lib__libc__common.dir/cmake_clean.cmake
.PHONY : zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/clean

zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/depend:
	cd /home/aki/cmpt-433/work/blinky/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/blinky /home/aki/zephyrproject/zephyr/lib/libc/common /home/aki/cmpt-433/work/blinky/build /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common /home/aki/cmpt-433/work/blinky/build/zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/lib/libc/common/CMakeFiles/lib__libc__common.dir/depend

