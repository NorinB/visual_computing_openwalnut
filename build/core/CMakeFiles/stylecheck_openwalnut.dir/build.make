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
CMAKE_SOURCE_DIR = /home/noah/Developer/visual_computing_openwalnut/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/noah/Developer/visual_computing_openwalnut/build

# Utility rule file for stylecheck_openwalnut.

# Include any custom commands dependencies for this target.
include core/CMakeFiles/stylecheck_openwalnut.dir/compiler_depend.make

# Include the progress variables for this target.
include core/CMakeFiles/stylecheck_openwalnut.dir/progress.make

core/CMakeFiles/stylecheck_openwalnut:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Check if openwalnut complies to CodingStandard"
	cd /home/noah/Developer/visual_computing_openwalnut/src/core && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_errors_openwalnut

stylecheck_openwalnut: core/CMakeFiles/stylecheck_openwalnut
stylecheck_openwalnut: core/CMakeFiles/stylecheck_openwalnut.dir/build.make
.PHONY : stylecheck_openwalnut

# Rule to build all files generated by this target.
core/CMakeFiles/stylecheck_openwalnut.dir/build: stylecheck_openwalnut
.PHONY : core/CMakeFiles/stylecheck_openwalnut.dir/build

core/CMakeFiles/stylecheck_openwalnut.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/core && $(CMAKE_COMMAND) -P CMakeFiles/stylecheck_openwalnut.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/stylecheck_openwalnut.dir/clean

core/CMakeFiles/stylecheck_openwalnut.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/core /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/core /home/noah/Developer/visual_computing_openwalnut/build/core/CMakeFiles/stylecheck_openwalnut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/CMakeFiles/stylecheck_openwalnut.dir/depend

