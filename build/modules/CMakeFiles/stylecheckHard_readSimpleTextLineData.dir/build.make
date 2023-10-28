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

# Utility rule file for stylecheckHard_readSimpleTextLineData.

# Include any custom commands dependencies for this target.
include modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/progress.make

modules/CMakeFiles/stylecheckHard_readSimpleTextLineData:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Check if readSimpleTextLineData complies to CodingStandard"
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_errors_readSimpleTextLineData
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_exitcode_readSimpleTextLineData

stylecheckHard_readSimpleTextLineData: modules/CMakeFiles/stylecheckHard_readSimpleTextLineData
stylecheckHard_readSimpleTextLineData: modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/build.make
.PHONY : stylecheckHard_readSimpleTextLineData

# Rule to build all files generated by this target.
modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/build: stylecheckHard_readSimpleTextLineData
.PHONY : modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/build

modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/clean

modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/stylecheckHard_readSimpleTextLineData.dir/depend

