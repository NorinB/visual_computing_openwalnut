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
include modules/CMakeFiles/imageSpaceTensorLIC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include modules/CMakeFiles/imageSpaceTensorLIC.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/CMakeFiles/imageSpaceTensorLIC.dir/progress.make

# Include the compile flags for this target's objects.
include modules/CMakeFiles/imageSpaceTensorLIC.dir/flags.make

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/flags.make
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o: /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o -MF CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o.d -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o -c /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.i"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp > CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.i

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.s"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.s

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/flags.make
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o: /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WToolkit.cpp
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o -MF CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o.d -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o -c /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WToolkit.cpp

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.i"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WToolkit.cpp > CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.i

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.s"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WToolkit.cpp -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.s

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/flags.make
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o: /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WTuringTextureCreator.cpp
modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o: modules/CMakeFiles/imageSpaceTensorLIC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o -MF CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o.d -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o -c /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WTuringTextureCreator.cpp

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.i"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WTuringTextureCreator.cpp > CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.i

modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.s"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/noah/Developer/visual_computing_openwalnut/src/modules/imageSpaceTensorLIC/WTuringTextureCreator.cpp -o CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.s

# Object files for target imageSpaceTensorLIC
imageSpaceTensorLIC_OBJECTS = \
"CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o" \
"CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o" \
"CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o"

# External object files for target imageSpaceTensorLIC
imageSpaceTensorLIC_EXTERNAL_OBJECTS =

lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WMImageSpaceTensorLIC.cpp.o
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WToolkit.cpp.o
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: modules/CMakeFiles/imageSpaceTensorLIC.dir/imageSpaceTensorLIC/WTuringTextureCreator.cpp.o
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: modules/CMakeFiles/imageSpaceTensorLIC.dir/build.make
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: lib/libopenwalnut.so.1.5.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenGL.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLX.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLU.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgWidget.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgViewer.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgText.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgSim.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgGA.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgDB.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgUtil.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosg.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenThreads.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.74.0
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenGL.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLX.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libGLU.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgWidget.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgViewer.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgText.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgSim.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgGA.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgDB.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosgUtil.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libosg.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: /usr/lib/x86_64-linux-gnu/libOpenThreads.so
lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0: modules/CMakeFiles/imageSpaceTensorLIC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so"
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imageSpaceTensorLIC.dir/link.txt --verbose=$(VERBOSE)
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -E cmake_symlink_library ../lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0 ../lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1 ../lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so

lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1: lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1

lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so: lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so.1.5.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so

# Rule to build all files generated by this target.
modules/CMakeFiles/imageSpaceTensorLIC.dir/build: lib/openwalnut/imageSpaceTensorLIC/libimageSpaceTensorLIC.so
.PHONY : modules/CMakeFiles/imageSpaceTensorLIC.dir/build

modules/CMakeFiles/imageSpaceTensorLIC.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/modules && $(CMAKE_COMMAND) -P CMakeFiles/imageSpaceTensorLIC.dir/cmake_clean.cmake
.PHONY : modules/CMakeFiles/imageSpaceTensorLIC.dir/clean

modules/CMakeFiles/imageSpaceTensorLIC.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/modules /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/modules /home/noah/Developer/visual_computing_openwalnut/build/modules/CMakeFiles/imageSpaceTensorLIC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/CMakeFiles/imageSpaceTensorLIC.dir/depend

