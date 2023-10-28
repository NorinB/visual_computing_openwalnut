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

# Utility rule file for stylecheck_filterProtonData.

# Include any custom commands dependencies for this target.
include modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/progress.make

modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Check if filterProtonData complies to CodingStandard"
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules/filterProtonData && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_errors_filterProtonData

stylecheck_filterProtonData: modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData
stylecheck_filterProtonData: modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/build.make
.PHONY : stylecheck_filterProtonData

# Rule to build all files generated by this target.
modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/build: stylecheck_filterProtonData
.PHONY : modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/build

modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules/filterProtonData && $(CMAKE_COMMAND) -P CMakeFiles/stylecheck_filterProtonData.dir/cmake_clean.cmake
.PHONY : modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/clean

modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules/filterProtonData /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules/filterProtonData /home/noah/Developer/visual_computing_openwalnut/build/modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/filterProtonData/CMakeFiles/stylecheck_filterProtonData.dir/depend

