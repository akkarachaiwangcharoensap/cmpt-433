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
CMAKE_SOURCE_DIR = /home/aki/cmpt-433/work/neopixel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aki/cmpt-433/work/neopixel/build

# Include any dependencies generated for this target.
include zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/assert.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/assert.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/assert.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/assert.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/assert.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/assert.c > CMakeFiles/lib__libc__picolibc.dir/assert.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/assert.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/assert.c -o CMakeFiles/lib__libc__picolibc.dir/assert.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/cbprintf.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/cbprintf.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/cbprintf.c > CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/cbprintf.c -o CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/chk_fail.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/chk_fail.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/chk_fail.c > CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/chk_fail.c -o CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/errno_wrap.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/errno_wrap.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/errno_wrap.c > CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/errno_wrap.c -o CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/exit.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/exit.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/exit.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/exit.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/exit.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/exit.c > CMakeFiles/lib__libc__picolibc.dir/exit.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/exit.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/exit.c -o CMakeFiles/lib__libc__picolibc.dir/exit.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/locks.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/locks.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/locks.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/locks.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/locks.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/locks.c > CMakeFiles/lib__libc__picolibc.dir/locks.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/locks.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/locks.c -o CMakeFiles/lib__libc__picolibc.dir/locks.c.s

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/flags.make
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj: /home/aki/zephyrproject/zephyr/lib/libc/picolibc/stdio.c
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj -MF CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj.d -o CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj -c /home/aki/zephyrproject/zephyr/lib/libc/picolibc/stdio.c

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib__libc__picolibc.dir/stdio.c.i"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/lib/libc/picolibc/stdio.c > CMakeFiles/lib__libc__picolibc.dir/stdio.c.i

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib__libc__picolibc.dir/stdio.c.s"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/lib/libc/picolibc/stdio.c -o CMakeFiles/lib__libc__picolibc.dir/stdio.c.s

# Object files for target lib__libc__picolibc
lib__libc__picolibc_OBJECTS = \
"CMakeFiles/lib__libc__picolibc.dir/assert.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/exit.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/locks.c.obj" \
"CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj"

# External object files for target lib__libc__picolibc
lib__libc__picolibc_EXTERNAL_OBJECTS =

zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/assert.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/cbprintf.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/chk_fail.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/errno_wrap.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/exit.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/locks.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/stdio.c.obj
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/build.make
zephyr/lib/libc/picolibc/liblib__libc__picolibc.a: zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library liblib__libc__picolibc.a"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && $(CMAKE_COMMAND) -P CMakeFiles/lib__libc__picolibc.dir/cmake_clean_target.cmake
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib__libc__picolibc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/build: zephyr/lib/libc/picolibc/liblib__libc__picolibc.a
.PHONY : zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/build

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/clean:
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc && $(CMAKE_COMMAND) -P CMakeFiles/lib__libc__picolibc.dir/cmake_clean.cmake
.PHONY : zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/clean

zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/depend:
	cd /home/aki/cmpt-433/work/neopixel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/neopixel /home/aki/zephyrproject/zephyr/lib/libc/picolibc /home/aki/cmpt-433/work/neopixel/build /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc /home/aki/cmpt-433/work/neopixel/build/zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/lib/libc/picolibc/CMakeFiles/lib__libc__picolibc.dir/depend

