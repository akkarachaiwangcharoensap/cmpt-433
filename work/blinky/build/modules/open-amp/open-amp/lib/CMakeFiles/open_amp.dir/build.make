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
include modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/progress.make

# Include the compile flags for this target's objects.
include modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/version.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj -MF CMakeFiles/open_amp.dir/version.c.obj.d -o CMakeFiles/open_amp.dir/version.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/version.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/version.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/version.c > CMakeFiles/open_amp.dir/version.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/version.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/version.c -o CMakeFiles/open_amp.dir/version.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtio.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj -MF CMakeFiles/open_amp.dir/virtio/virtio.c.obj.d -o CMakeFiles/open_amp.dir/virtio/virtio.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtio.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/virtio/virtio.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtio.c > CMakeFiles/open_amp.dir/virtio/virtio.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/virtio/virtio.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtio.c -o CMakeFiles/open_amp.dir/virtio/virtio.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj -MF CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj.d -o CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/virtio/virtqueue.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c > CMakeFiles/open_amp.dir/virtio/virtqueue.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/virtio/virtqueue.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c -o CMakeFiles/open_amp.dir/virtio/virtqueue.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj -MF CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj.d -o CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c > CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c -o CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj -MF CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj.d -o CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c > CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c -o CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/elf_loader.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj -MF CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj.d -o CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/elf_loader.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/elf_loader.c > CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/elf_loader.c -o CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj -MF CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj.d -o CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc.c > CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc.c -o CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc_virtio.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj -MF CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj.d -o CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc_virtio.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc_virtio.c > CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/remoteproc_virtio.c -o CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/rsc_table_parser.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj -MF CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj.d -o CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/rsc_table_parser.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/rsc_table_parser.c > CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/remoteproc/rsc_table_parser.c -o CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.s

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/flags.make
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj: /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/utils/utilities.c
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj -MF CMakeFiles/open_amp.dir/utils/utilities.c.obj.d -o CMakeFiles/open_amp.dir/utils/utilities.c.obj -c /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/utils/utilities.c

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/open_amp.dir/utils/utilities.c.i"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/utils/utilities.c > CMakeFiles/open_amp.dir/utils/utilities.c.i

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/open_amp.dir/utils/utilities.c.s"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/utils/utilities.c -o CMakeFiles/open_amp.dir/utils/utilities.c.s

# Object files for target open_amp
open_amp_OBJECTS = \
"CMakeFiles/open_amp.dir/version.c.obj" \
"CMakeFiles/open_amp.dir/virtio/virtio.c.obj" \
"CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj" \
"CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj" \
"CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj" \
"CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj" \
"CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj" \
"CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj" \
"CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj" \
"CMakeFiles/open_amp.dir/utils/utilities.c.obj"

# External object files for target open_amp
open_amp_EXTERNAL_OBJECTS =

modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/version.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtio.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/rpmsg_virtio.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/elf_loader.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/remoteproc_virtio.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/remoteproc/rsc_table_parser.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/utils/utilities.c.obj
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/build.make
modules/open-amp/open-amp/lib/libopen_amp.a: modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aki/cmpt-433/work/blinky/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C static library libopen_amp.a"
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && $(CMAKE_COMMAND) -P CMakeFiles/open_amp.dir/cmake_clean_target.cmake
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/open_amp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/build: modules/open-amp/open-amp/lib/libopen_amp.a
.PHONY : modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/build

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/clean:
	cd /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib && $(CMAKE_COMMAND) -P CMakeFiles/open_amp.dir/cmake_clean.cmake
.PHONY : modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/clean

modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/depend:
	cd /home/aki/cmpt-433/work/blinky/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/blinky /home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib /home/aki/cmpt-433/work/blinky/build /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib /home/aki/cmpt-433/work/blinky/build/modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/depend

