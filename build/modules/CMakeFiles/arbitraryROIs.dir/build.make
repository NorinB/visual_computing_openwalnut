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

# Include any dependencies generated for this target.
include modules/CMakeFiles/arbitraryROIs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include modules/CMakeFiles/arbitraryROIs.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/arbitraryROIs.dir/progress.make

# Include the compile flags for this target's objects.
include modules/CMakeFiles/arbitraryROIs.dir/flags.make

modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o: modules/CMakeFiles/arbitraryROIs.dir/flags.make
modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o: /home/noah/Developer/visual_computing_openwalnut/src/modules/arbitraryROIs/WMArbitraryROIs.cpp
modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o: modules/CMakeFiles/arbitraryROIs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o -MF CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o.d -o CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o -c /home/noah/Developer/visual_computing_openwalnut/src/modules/arbitraryROIs/WMArbitraryROIs.cpp

modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.i"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/noah/Developer/visual_computing_openwalnut/src/modules/arbitraryROIs/WMArbitraryROIs.cpp > CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.i

modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.s"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/noah/Developer/visual_computing_openwalnut/src/modules/arbitraryROIs/WMArbitraryROIs.cpp -o CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.s

# Object files for target arbitraryROIs
arbitraryROIs_OBJECTS = \
"CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o"

# External object files for target arbitraryROIs
arbitraryROIs_EXTERNAL_OBJECTS =

lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: modules/CMakeFiles/arbitraryROIs.dir/arbitraryROIs/WMArbitraryROIs.cpp.o
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: modules/CMakeFiles/arbitraryROIs.dir/build.make
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: lib/libopenwalnut.so.1.5.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenGL.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLX.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLU.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgWidget.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgViewer.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgText.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgSim.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgGA.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgDB.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgUtil.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosg.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenThreads.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.74.0
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenGL.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLX.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLU.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgWidget.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgViewer.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgText.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgSim.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgGA.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgDB.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgUtil.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosg.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenThreads.so
lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0: modules/CMakeFiles/arbitraryROIs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../lib/openwalnut/arbitraryROIs/libarbitraryROIs.so"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arbitraryROIs.dir/link.txt --verbose=$(VERBOSE)
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -E cmake_symlink_library ../lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0 ../lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1 ../lib/openwalnut/arbitraryROIs/libarbitraryROIs.so

lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1: lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1

lib/openwalnut/arbitraryROIs/libarbitraryROIs.so: lib/openwalnut/arbitraryROIs/libarbitraryROIs.so.1.5.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/openwalnut/arbitraryROIs/libarbitraryROIs.so

# Rule to build all files generated by this target.
modules/CMakeFiles/arbitraryROIs.dir/build: lib/openwalnut/arbitraryROIs/libarbitraryROIs.so
.PHONY : modules/CMakeFiles/arbitraryROIs.dir/build

modules/CMakeFiles/arbitraryROIs.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/arbitraryROIs.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/arbitraryROIs.dir/clean

modules/CMakeFiles/arbitraryROIs.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/arbitraryROIs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/arbitraryROIs.dir/depend

