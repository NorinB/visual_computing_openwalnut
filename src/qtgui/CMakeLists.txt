#---------------------------------------------------------------------------
#
# Project: OpenWalnut ( http://www.openwalnut.org )
#
# Copyright 2009 OpenWalnut Community, BSV@Uni-Leipzig and CNCF@MPI-CBS
# For more information see http:#www.openwalnut.org/copying
#
# This file is part of OpenWalnut.
#
# OpenWalnut is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OpenWalnut is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with OpenWalnut. If not, see <http:#www.gnu.org/licenses/>.
#
#---------------------------------------------------------------------------

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
IF( POLICY CMP0020 )
    cmake_policy( SET CMP0020 NEW )
ENDIF()

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Some common setup
# ---------------------------------------------------------------------------------------------------------------------------------------------------

SET( LibName "qtgui" )
SET( BinName "openwalnut-qt" )

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Setup QT
# ---------------------------------------------------------------------------------------------------------------------------------------------------

OPTION( OW_GUI_QT5_WebKit "If building with Qt5 use deprecated WebKit" OFF )

OPTION( OW_GUI_FORCE_QT6 "Enable this to build the QT6-based OpenWalnut GUI." OFF )

IF( OW_GUI_FORCE_QT6 )
    FIND_PACKAGE( Qt6 REQUIRED COMPONENTS Gui Widgets OpenGLWidgets OPTIONAL_COMPONENTS WebEngineWidgets )
    SET( QT_Link_Libs )

    IF( NOT Qt6WebEngineWidgets_FOUND )
        # Sadly there is no WebEngineWidget support for mingw (Chromium does not compile in mingw) and WebKit has been removed
        # Windows can only use it with msvc (which openwalnut does not support)
        # Maybe switch WebEngineWidget to WebView, which is not based on chromium
        ADD_DEFINITIONS( "-DOW_QT6_NO_WEBENGINE" )
    ELSE()
        LIST( APPEND QT_Link_Libs Qt6::WebEngineWidgets )
    ENDIF()

    # Using '+' to concatenate keys for a key sequence is deprecated
    # For modifiers like SHIFT or CTRL it has already been removed -> use '|' now
    ADD_DEFINITIONS( "-DOW_QT6_MODIFIER_ADD" )

    # QRegExp was removed, now use QRegularExpression
    ADD_DEFINITIONS( "-DOW_QT6_REGEXP" )

    # QGLWidget was removed, now use QOpenGLWidget
    ADD_DEFINITIONS( "-DOW_QT_GLWIDGET" )

    # There is no signal mapping for QWidget anymore
    ADD_DEFINITIONS( "-DOW_QT6_SIGNALMAPPER" )

    LIST( APPEND QT_Link_Libs Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets )
ELSE()
    IF( OW_GUI_QT5_WebKit )
        ADD_DEFINITIONS( "-DOW_FORCE_WEBKIT" )
    ENDIF()

    # Use QOpenGLWidget instead of deprecated QGLWidget
    ADD_DEFINITIONS( "-DOW_QT_GLWIDGET" )

    # Special handling if the user specified a QT path manually. Useful when using multiple installations of Qt.
    IF( DEFINED ENV{QTDIR} )
        MESSAGE( "Using custom Qt path. Ensure you set the path to the directory containing the bin and lib directories." )
        SET( CMAKE_PREFIX_PATH "$ENV{QTDIR}/lib/cmake/Qt5Widgets" ${CMAKE_PREFIX_PATH} )
        SET( CMAKE_PREFIX_PATH "$ENV{QTDIR}/lib/cmake/Qt5OpenGL" ${CMAKE_PREFIX_PATH} )
        SET( CMAKE_PREFIX_PATH "$ENV{QTDIR}/lib/cmake/Qt5WebKitWidgets" ${CMAKE_PREFIX_PATH} )
        SET( CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH} )
    endif()

    # Package dependencies:
    FIND_PACKAGE( Qt5Widgets REQUIRED )
    FIND_PACKAGE( Qt5OpenGL REQUIRED )
    IF( OW_GUI_QT5_WebKit )    
        FIND_PACKAGE( Qt5WebKitWidgets REQUIRED )
    ELSE()
        FIND_PACKAGE( Qt5WebEngineWidgets REQUIRED )
    ENDIF()

    INCLUDE_DIRECTORIES( SYSTEM ${Qt5Widgets_INCLUDE_DIRS} )
    INCLUDE_DIRECTORIES( SYSTEM ${Qt5OpenGL_INCLUDE_DIRS} )
    IF( OW_GUI_QT5_WebKit )    
        INCLUDE_DIRECTORIES( SYSTEM ${Qt5WebKitWidgets_INCLUDE_DIRS} )
    ELSE()
        INCLUDE_DIRECTORIES( SYSTEM ${Qt5WebEngineWidgets_INCLUDE_DIRS} )
    ENDIF()

    # Compiling with Qt5 requires some special definitions and flags to be set.

    # Collect and set definitions
    SET( _QT5_DEFINITIONS "" )
    LIST( APPEND _QT5_DEFINITIONS ${Qt5Widgets_DEFINITIONS} )
    LIST( APPEND _QT5_DEFINITIONS ${Qt5OpenGL_DEFINITIONS} )
    IF( OW_GUI_QT5_WebKit )    
        LIST( APPEND _QT5_DEFINITIONS ${Qt5WebKitWidgets_DEFINITIONS} )
    ELSE()
        LIST( APPEND _QT5_DEFINITIONS ${Qt5WebEngineWidgets_DEFINITIONS} )
    ENDIF()
    LIST( REMOVE_DUPLICATES _QT5_DEFINITIONS )
    ADD_DEFINITIONS( ${_QT5_DEFINITIONS} )

    # Collect and set compiler flags
    SET( _QT5_EXECUTABLE_COMPILE_FLAGS "" )
    LIST( APPEND _QT5_EXECUTABLE_COMPILE_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} )
    LIST( APPEND _QT5_EXECUTABLE_COMPILE_FLAGS ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS} )
    IF( OW_GUI_QT5_WebKit )    
        LIST( APPEND _QT5_EXECUTABLE_COMPILE_FLAGS ${Qt5WebKitWidgets_EXECUTABLE_COMPILE_FLAGS} )
    ELSE()    
        LIST( APPEND _QT5_EXECUTABLE_COMPILE_FLAGS ${Qt5WebEngineWidgets_EXECUTABLE_COMPILE_FLAGS} )
    ENDIF()
    LIST( REMOVE_DUPLICATES _QT5_EXECUTABLE_COMPILE_FLAGS )
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_QT5_EXECUTABLE_COMPILE_FLAGS}" )

    IF( OW_GUI_QT5_WebKit )    
        SET( QT_Link_Libs Qt5::Widgets Qt5::OpenGL Qt5::WebKitWidgets ) 
    ELSE()  
        SET( QT_Link_Libs Qt5::Widgets Qt5::OpenGL Qt5::WebEngineWidgets ) 
    ENDIF()
ENDIF()

# Includes:
INCLUDE_DIRECTORIES( SYSTEM ${QT_INCLUDE_DIR} )

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Add sources as target
# ---------------------------------------------------------------------------------------------------------------------------------------------------

IF( OW_BOOST_PO_FIX )
    # Disable if you get errors relating to program_options::arg when linking the binary
    ADD_DEFINITIONS( "-DOW_BOOST_PROGRAM_OPTIONS_FIX" )
ENDIF()

# Collect the compile-files for this target
COLLECT_COMPILE_FILES( "${CMAKE_CURRENT_SOURCE_DIR}" TARGET_CPP_FILES TARGET_H_FILES TARGET_TEST_FILES )

# Qt Requires all classes with a QWidget stuff inside to be put into the MOC mechanism. We utilize the automoc mechanism here.
SET( CMAKE_AUTOMOC ON )
SET( AUTOMOC_MOC_OPTIONS "${OW_CPP_FLAGS_INJECT}" )

# Exclude autogenerated WVersion.h (usally in versionHeader/core) from AUTOMOC mechanism to avoid cmake warning CMP0071 which comes with cmake version 3.10.
SET_PROPERTY(SOURCE  "${CMAKE_BINARY_DIR}/${OW_VERSION_HEADER_DIRECTORY_RELATIVE}/${OW_INTERNAL_VERSION_HEADER_FILENAME}" PROPERTY SKIP_AUTOMOC ON)

# This is needed since the mocs will be generated there
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

# Setup the target
ADD_EXECUTABLE( ${BinName} ${TARGET_CPP_FILES} ${TARGET_H_FILES} ${OW_VERSION_HEADER} )

# Some Linux distributions need to explicitly link against X11. We add this lib here.
IF( CMAKE_HOST_SYSTEM MATCHES "Linux" )
    SET( ADDITIONAL_TARGET_LINK_LIBRARIES "X11" )
ENDIF()
TARGET_LINK_LIBRARIES( ${BinName} ${OW_LIB_OPENWALNUT}
                                  ${QT_Link_Libs} 
                                  ${Boost_LIBRARIES} 
                                  ${ADDITIONAL_TARGET_LINK_LIBRARIES} )

# Tell CMake that someone creates this file for us. See doc of SETUP_VERSION_HEADER for details why this is needed.
# NOTE: this needs to be placed AFTER ADD_EXECUTABLE or ADD_LIBRARY
SETUP_USE_VERSION_HEADER( ${BinName} )

# Do not forget the install targets
INSTALL( TARGETS ${BinName}
            RUNTIME
                DESTINATION ${OW_RUNTIME_DIR_RELATIVE}
                PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                            GROUP_READ GROUP_EXECUTE
                            WORLD_READ WORLD_EXECUTE
         COMPONENT "QTGUI"
        )

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Test Setup
# ---------------------------------------------------------------------------------------------------------------------------------------------------

# Setup tests of this target
SETUP_TESTS( "${TARGET_TEST_FILES}" "${BinName}" "" )

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Copy local resources
# ---------------------------------------------------------------------------------------------------------------------------------------------------

# copy our own resources
SETUP_GLOBAL_RESOURCES( ${LibName} "QTGUI" )

# where to put doc files?
SET( OW_DOC_DIR_RELATIVE "share/doc/openwalnut-qt" )
SETUP_COMMON_DOC( ${OW_DOC_DIR_RELATIVE} "QTGUI" )

# also copy all the user documentation we have for qtgui
SETUP_ADDITIONAL_DIRECTORY( ${OW_DOC_DIR_RELATIVE}
                            ${PROJECT_SOURCE_DIR}/../doc/${LibName}/help/
                            "QTGUI"
                            TRUE    # this denotes that the contents of doc/user should be copied instead of user directly
                          )  
SETUP_ADDITIONAL_DIRECTORY( ${OW_MAN_DIR_RELATIVE}
                            ${PROJECT_SOURCE_DIR}/../doc/${LibName}/man/
                            "QTGUI"
                            TRUE    # this denotes that the contents of doc/man should be copied instead of user directly
                          )

# ---------------------------------------------------------------------------------------------------------------------------------------------------
# Style Checker
# ---------------------------------------------------------------------------------------------------------------------------------------------------

# setup the stylechecker. Ignore the platform specific stuff.
SETUP_STYLECHECKER( "${BinName}"
                    "${TARGET_CPP_FILES};${TARGET_H_FILES};${TARGET_TEST_FILES};${TARGET_GLSL_FILES}"  # add all these files to the stylechecker
                    "" )                                                                               # exlude some ugly files
