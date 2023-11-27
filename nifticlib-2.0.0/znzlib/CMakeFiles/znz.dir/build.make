# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0

# Include any dependencies generated for this target.
include znzlib/CMakeFiles/znz.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include znzlib/CMakeFiles/znz.dir/compiler_depend.make

# Include the progress variables for this target.
include znzlib/CMakeFiles/znz.dir/progress.make

# Include the compile flags for this target's objects.
include znzlib/CMakeFiles/znz.dir/flags.make

znzlib/CMakeFiles/znz.dir/znzlib.o: znzlib/CMakeFiles/znz.dir/flags.make
znzlib/CMakeFiles/znz.dir/znzlib.o: znzlib/znzlib.c
znzlib/CMakeFiles/znz.dir/znzlib.o: znzlib/CMakeFiles/znz.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object znzlib/CMakeFiles/znz.dir/znzlib.o"
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT znzlib/CMakeFiles/znz.dir/znzlib.o -MF CMakeFiles/znz.dir/znzlib.o.d -o CMakeFiles/znz.dir/znzlib.o -c /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib/znzlib.c

znzlib/CMakeFiles/znz.dir/znzlib.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/znz.dir/znzlib.i"
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib/znzlib.c > CMakeFiles/znz.dir/znzlib.i

znzlib/CMakeFiles/znz.dir/znzlib.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/znz.dir/znzlib.s"
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib/znzlib.c -o CMakeFiles/znz.dir/znzlib.s

# Object files for target znz
znz_OBJECTS = \
"CMakeFiles/znz.dir/znzlib.o"

# External object files for target znz
znz_EXTERNAL_OBJECTS =

znzlib/libznz.a: znzlib/CMakeFiles/znz.dir/znzlib.o
znzlib/libznz.a: znzlib/CMakeFiles/znz.dir/build.make
znzlib/libznz.a: znzlib/CMakeFiles/znz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libznz.a"
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && $(CMAKE_COMMAND) -P CMakeFiles/znz.dir/cmake_clean_target.cmake
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/znz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
znzlib/CMakeFiles/znz.dir/build: znzlib/libznz.a
.PHONY : znzlib/CMakeFiles/znz.dir/build

znzlib/CMakeFiles/znz.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib && $(CMAKE_COMMAND) -P CMakeFiles/znz.dir/cmake_clean.cmake
.PHONY : znzlib/CMakeFiles/znz.dir/clean

znzlib/CMakeFiles/znz.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0 /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0 /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib /home/noah/Developer/visual_computing_openwalnut/nifticlib-2.0.0/znzlib/CMakeFiles/znz.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : znzlib/CMakeFiles/znz.dir/depend

