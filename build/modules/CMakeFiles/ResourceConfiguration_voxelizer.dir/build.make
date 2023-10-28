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

# Utility rule file for ResourceConfiguration_voxelizer.

# Include any custom commands dependencies for this target.
include modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/progress.make

modules/CMakeFiles/ResourceConfiguration_voxelizer:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying resources for voxelizer to build directory"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/cmake -E copy_directory /home/noah/Developer/visual_computing_openwalnut/src/modules/voxelizer/resources/ /home/noah/Developer/visual_computing_openwalnut/build/share/openwalnut/modules/voxelizer/

ResourceConfiguration_voxelizer: modules/CMakeFiles/ResourceConfiguration_voxelizer
ResourceConfiguration_voxelizer: modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/build.make
.PHONY : ResourceConfiguration_voxelizer

# Rule to build all files generated by this target.
modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/build: ResourceConfiguration_voxelizer
.PHONY : modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/build

modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/ResourceConfiguration_voxelizer.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/clean

modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/ResourceConfiguration_voxelizer.dir/depend

