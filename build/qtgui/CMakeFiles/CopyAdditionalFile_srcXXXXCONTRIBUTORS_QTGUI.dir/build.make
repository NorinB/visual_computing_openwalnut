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

# Utility rule file for CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.

# Include any custom commands dependencies for this target.
include qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/compiler_depend.make

# Include the progress variables for this target.
include qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/progress.make

qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/noah/Developer/visual_computing_openwalnut/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying file /home/noah/Developer/visual_computing_openwalnut/src/../CONTRIBUTORS"
	cd /home/noah/Developer/visual_computing_openwalnut/build/qtgui && /usr/bin/cmake -E make_directory /home/noah/Developer/visual_computing_openwalnut/build/share/doc/openwalnut-qt/
	cd /home/noah/Developer/visual_computing_openwalnut/build/qtgui && /usr/bin/cmake -E copy /home/noah/Developer/visual_computing_openwalnut/src/../CONTRIBUTORS /home/noah/Developer/visual_computing_openwalnut/build/share/doc/openwalnut-qt/

CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI: qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI
CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI: qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/build.make
.PHONY : CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI

# Rule to build all files generated by this target.
qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/build: CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI
.PHONY : qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/build

qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/clean:
	cd /home/noah/Developer/visual_computing_openwalnut/build/qtgui && $(CMAKE_COMMAND) -P CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/cmake_clean.cmake
.PHONY : qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/clean

qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/depend:
	cd /home/noah/Developer/visual_computing_openwalnut/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/noah/Developer/visual_computing_openwalnut/src /home/noah/Developer/visual_computing_openwalnut/src/qtgui /home/noah/Developer/visual_computing_openwalnut/build /home/noah/Developer/visual_computing_openwalnut/build/qtgui /home/noah/Developer/visual_computing_openwalnut/build/qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : qtgui/CMakeFiles/CopyAdditionalFile_srcXXXXCONTRIBUTORS_QTGUI.dir/depend

