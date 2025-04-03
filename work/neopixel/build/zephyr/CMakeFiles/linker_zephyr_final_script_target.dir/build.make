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

# Utility rule file for linker_zephyr_final_script_target.

# Include any custom commands dependencies for this target.
include zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/progress.make

zephyr/CMakeFiles/linker_zephyr_final_script_target: zephyr/linker.cmd

zephyr/linker.cmd: /home/aki/zephyrproject/zephyr/soc/ti/k3/am6x/r5/linker.ld
zephyr/linker.cmd: zephyr/include/generated/zephyr/autoconf.h
zephyr/linker.cmd: zephyr/zephyr_pre0.elf
zephyr/linker.cmd: zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating linker.cmd"
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr && /home/aki/zephyr-sdk-0.17.0/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc -x assembler-with-cpp -undef -MD -MF linker.cmd.dep -MT linker.cmd -D_LINKER -D_ASMLANGUAGE -D__GCC_LINKER_CMD__ -imacros /home/aki/cmpt-433/work/neopixel/build/zephyr/include/generated/zephyr/autoconf.h -I/home/aki/cmpt-433/work/neopixel/build/zephyr/include/generated/zephyr -I/home/aki/zephyrproject/zephyr/include -I/home/aki/cmpt-433/work/neopixel/build/zephyr/include/generated -I/home/aki/zephyrproject/zephyr/soc/ti/k3 -I/home/aki/zephyrproject/zephyr/lib/libc/common/include -I/home/aki/zephyrproject/zephyr/lib/open-amp/. -I/home/aki/zephyrproject/zephyr/soc/ti/k3/am6x/. -I/home/aki/zephyrproject/zephyr/soc/ti/k3/am6x/r5 -I/home/aki/zephyrproject/modules/hal/cmsis/CMSIS/Core_R/Include -I/home/aki/zephyrproject/zephyr/modules/cmsis/. -I/home/aki/cmpt-433/work/neopixel/build/modules/libmetal/libmetal/lib/include -I/home/aki/zephyrproject/modules/lib/open-amp/open-amp/lib/include -I/home/aki/zephyrproject/zephyr/soc/ti/k3/am6x/r5 -DLINKER_ZEPHYR_FINAL -E /home/aki/zephyrproject/zephyr/soc/ti/k3/am6x/r5/linker.ld -P -o linker.cmd

linker_zephyr_final_script_target: zephyr/CMakeFiles/linker_zephyr_final_script_target
linker_zephyr_final_script_target: zephyr/linker.cmd
linker_zephyr_final_script_target: zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/build.make
.PHONY : linker_zephyr_final_script_target

# Rule to build all files generated by this target.
zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/build: linker_zephyr_final_script_target
.PHONY : zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/build

zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/clean:
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/linker_zephyr_final_script_target.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/clean

zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/depend:
	cd /home/aki/cmpt-433/work/neopixel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/neopixel /home/aki/zephyrproject/zephyr /home/aki/cmpt-433/work/neopixel/build /home/aki/cmpt-433/work/neopixel/build/zephyr /home/aki/cmpt-433/work/neopixel/build/zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/linker_zephyr_final_script_target.dir/depend

