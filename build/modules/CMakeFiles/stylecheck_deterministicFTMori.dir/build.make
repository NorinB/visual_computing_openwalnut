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

# Utility rule file for stylecheck_deterministicFTMori.

# Include any custom commands dependencies for this target.
include modules/CMakeFiles/stylecheck_deterministicFTMori.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/stylecheck_deterministicFTMori.dir/progress.make

modules/CMakeFiles/stylecheck_deterministicFTMori:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Check if deterministicFTMori complies to CodingStandard"
	cd /home/noah/Developer/visual_computing_openwalnut/src/modules && bash /home/noah/Developer/visual_computing_openwalnut/build/brainlint/brainlintcommand_errors_deterministicFTMori

stylecheck_deterministicFTMori: modules/CMakeFiles/stylecheck_deterministicFTMori
stylecheck_deterministicFTMori: modules/CMakeFiles/stylecheck_deterministicFTMori.dir/build.make
.PHONY : stylecheck_deterministicFTMori

# Rule to build all files generated by this target.
modules/CMakeFiles/stylecheck_deterministicFTMori.dir/build: stylecheck_deterministicFTMori
.PHONY : modules/CMakeFiles/stylecheck_deterministicFTMori.dir/build

modules/CMakeFiles/stylecheck_deterministicFTMori.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/stylecheck_deterministicFTMori.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/stylecheck_deterministicFTMori.dir/clean

modules/CMakeFiles/stylecheck_deterministicFTMori.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/stylecheck_deterministicFTMori.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/stylecheck_deterministicFTMori.dir/depend

