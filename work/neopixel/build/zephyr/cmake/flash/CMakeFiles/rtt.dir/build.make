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

# Utility rule file for rtt.

# Include any custom commands dependencies for this target.
include zephyr/cmake/flash/CMakeFiles/rtt.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/cmake/flash/CMakeFiles/rtt.dir/progress.make

zephyr/cmake/flash/CMakeFiles/rtt:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/aki/cmpt-433/work/neopixel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "RTT beagley_ai"
	/usr/bin/cmake -DTARGET=rtt -DDEPENDENCIES="" -P /home/aki/zephyrproject/zephyr/cmake/flash/check_runner_dependencies.cmake
	/usr/bin/cmake -E env /home/aki/zephyrproject/.venv/bin/python -m west rtt

rtt: zephyr/cmake/flash/CMakeFiles/rtt
rtt: zephyr/cmake/flash/CMakeFiles/rtt.dir/build.make
.PHONY : rtt

# Rule to build all files generated by this target.
zephyr/cmake/flash/CMakeFiles/rtt.dir/build: rtt
.PHONY : zephyr/cmake/flash/CMakeFiles/rtt.dir/build

zephyr/cmake/flash/CMakeFiles/rtt.dir/clean:
	cd /home/aki/cmpt-433/work/neopixel/build/zephyr/cmake/flash && $(CMAKE_COMMAND) -P CMakeFiles/rtt.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/flash/CMakeFiles/rtt.dir/clean

zephyr/cmake/flash/CMakeFiles/rtt.dir/depend:
	cd /home/aki/cmpt-433/work/neopixel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/neopixel /home/aki/zephyrproject/zephyr/cmake/flash /home/aki/cmpt-433/work/neopixel/build /home/aki/cmpt-433/work/neopixel/build/zephyr/cmake/flash /home/aki/cmpt-433/work/neopixel/build/zephyr/cmake/flash/CMakeFiles/rtt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/flash/CMakeFiles/rtt.dir/depend

