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

# Utility rule file for pristine.

# Include any custom commands dependencies for this target.
include CMakeFiles/pristine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pristine.dir/progress.make

CMakeFiles/pristine:
	/usr/bin/cmake -DBINARY_DIR=/home/aki/cmpt-433/work/assignment-4/build -DSOURCE_DIR=/home/aki/cmpt-433/work/assignment-4 -P /home/aki/zephyrproject/zephyr/cmake/pristine.cmake

pristine: CMakeFiles/pristine
pristine: CMakeFiles/pristine.dir/build.make
.PHONY : pristine

# Rule to build all files generated by this target.
CMakeFiles/pristine.dir/build: pristine
.PHONY : CMakeFiles/pristine.dir/build

CMakeFiles/pristine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pristine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pristine.dir/clean

CMakeFiles/pristine.dir/depend:
	cd /home/aki/cmpt-433/work/assignment-4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aki/cmpt-433/work/assignment-4 /home/aki/cmpt-433/work/assignment-4 /home/aki/cmpt-433/work/assignment-4/build /home/aki/cmpt-433/work/assignment-4/build /home/aki/cmpt-433/work/assignment-4/build/CMakeFiles/pristine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pristine.dir/depend

