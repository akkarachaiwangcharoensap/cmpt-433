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
CMAKE_SOURCE_DIR = /home/aki/cmpt-433/work/assignment-4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aki/cmpt-433/work/assignment-4/build

# Include any dependencies generated for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/CMakeFiles/zephyr_pre0.dir/flags.make

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/zephyr_pre0.dir/flags.make
zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: /home/aki/zephyrproject/zephyr/misc/empty_file.c
zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/zephyr_pre0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aki/cmpt-433/work/assignment-4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj"
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj -MF CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj.d -o CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj -c /home/aki/zephyrproject/zephyr/misc/empty_file.c

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.i"
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aki/zephyrproject/zephyr/misc/empty_file.c > CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.i

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.s"
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aki/zephyrproject/zephyr/misc/empty_file.c -o CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.s

# Object files for target zephyr_pre0
zephyr_pre0_OBJECTS = \
"CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj"

# External object files for target zephyr_pre0
zephyr_pre0_EXTERNAL_OBJECTS =

zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/build.make
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj
zephyr/zephyr_pre0.elf: zephyr/linker_zephyr_pre0.cmd
zephyr/zephyr_pre0.elf: app/libapp.a
zephyr/zephyr_pre0.elf: zephyr/libzephyr.a
zephyr/zephyr_pre0.elf: zephyr/arch/common/libarch__common.a
zephyr/zephyr_pre0.elf: zephyr/arch/arch/arm/core/libarch__arm__core.a
zephyr/zephyr_pre0.elf: zephyr/arch/arch/arm/core/cortex_a_r/libarch__arm__core__cortex_a_r.a
zephyr/zephyr_pre0.elf: zephyr/lib/libc/picolibc/liblib__libc__picolibc.a
zephyr/zephyr_pre0.elf: zephyr/lib/libc/common/liblib__libc__common.a
zephyr/zephyr_pre0.elf: zephyr/drivers/interrupt_controller/libdrivers__interrupt_controller.a
zephyr/zephyr_pre0.elf: zephyr/drivers/console/libdrivers__console.a
zephyr/zephyr_pre0.elf: zephyr/drivers/gpio/libdrivers__gpio.a
zephyr/zephyr_pre0.elf: zephyr/drivers/pinctrl/libdrivers__pinctrl.a
zephyr/zephyr_pre0.elf: zephyr/drivers/serial/libdrivers__serial.a
zephyr/zephyr_pre0.elf: zephyr/drivers/timer/libdrivers__timer.a
zephyr/zephyr_pre0.elf: modules/libmetal/libmetal/lib/libmetal.a
zephyr/zephyr_pre0.elf: modules/open-amp/open-amp/lib/libopen_amp.a
zephyr/zephyr_pre0.elf: zephyr/kernel/libkernel.a
zephyr/zephyr_pre0.elf: zephyr/arch/common/libisr_tables.a
zephyr/zephyr_pre0.elf: zephyr/linker_zephyr_pre0.cmd
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aki/cmpt-433/work/assignment-4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zephyr_pre0.elf"
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zephyr_pre0.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Logical command for additional byproducts on target: zephyr_pre0"
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && /usr/bin/cmake -E true

# Rule to build all files generated by this target.
zephyr/CMakeFiles/zephyr_pre0.dir/build: zephyr/zephyr_pre0.elf
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/build

zephyr/CMakeFiles/zephyr_pre0.dir/clean:
	cd /home/aki/cmpt-433/work/assignment-4/build/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/zephyr_pre0.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/clean

zephyr/CMakeFiles/zephyr_pre0.dir/depend:
	cd /home/aki/cmpt-433/work/assignment-4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/assignment-4 /home/aki/zephyrproject/zephyr /home/aki/cmpt-433/work/assignment-4/build /home/aki/cmpt-433/work/assignment-4/build/zephyr /home/aki/cmpt-433/work/assignment-4/build/zephyr/CMakeFiles/zephyr_pre0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/depend

