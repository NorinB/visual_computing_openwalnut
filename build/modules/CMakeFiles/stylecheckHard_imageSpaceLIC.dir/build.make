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

# Utility rule file for stylecheckHard_imageSpaceLIC.

# Include any custom commands dependencies for this target.
include modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/progress.make

modules/CMakeFiles/stylecheckHard_imageSpaceLIC:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Check if imageSpaceLIC complies to CodingStandard"
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_errors_imageSpaceLIC
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_exitcode_imageSpaceLIC

stylecheckHard_imageSpaceLIC: modules/CMakeFiles/stylecheckHard_imageSpaceLIC
stylecheckHard_imageSpaceLIC: modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/build.make
.PHONY : stylecheckHard_imageSpaceLIC

# Rule to build all files generated by this target.
modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/build: stylecheckHard_imageSpaceLIC
.PHONY : modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/build

modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/stylecheckHard_imageSpaceLIC.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/clean

modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/stylecheckHard_imageSpaceLIC.dir/depend

