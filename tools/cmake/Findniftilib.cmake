# This script searches niftilib. See  http://niftilib.sourceforge.net
#
# The following variables will be filled:
#   * NIFTILIB_FOUND - if nifti1.h and lib was found
#   * NIFTILIB_INCLUDE_DIR - the path of nifti1.h if found
#   * NIFTILIB_LIBRARY - the path to the library
#

FIND_PATH( NIFTILIB_INCLUDE_DIR nifti1.h 
        $ENV{NIFTILIB_INCLUDE_DIR}/nifti
        $ENV{NIFTILIB_INCLUDE_DIR}
        $ENV{HOME}/.local/include/nifti
        /usr/include/nifti
        /usr/local/include/nifti )

# This hack is inspired by FindBoost.cmake. It ensures that only shared objects are found. Linking a SO with a static lib is not possible 
# in Linux. On other systems, this should be no problem.
SET( _ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
IF( CMAKE_HOST_SYSTEM MATCHES "Linux" )
    SET( CMAKE_FIND_LIBRARY_SUFFIXES .so )
ENDIF()
FIND_LIBRARY( NIFTILIB_LIBRARY NAMES niftiio HINTS $ENV{NIFTILIB_LIBRARY_DIR}/niftilib $ENV{NIFTILIB_LIBRARY_DIR} /usr/lib /usr/local/lib )
FIND_LIBRARY( NIFTIZNZ_LIBRARY NAMES znz HINTS $ENV{NIFTILIB_LIBRARY_DIR}/znzlib $ENV{NIFTILIB_LIBRARY_DIR} /usr/lib /usr/local/lib )
FIND_LIBRARY( ZLIB_LIBRARY NAMES z zlib HINTS $ENV{ZLIB_LIBRARY_DIR} /usr/lib /usr/local/lib )

SET( CMAKE_FIND_LIBRARY_SUFFIXES ${_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES} )

SET( NIFTILIB_FOUND FALSE )
IF( NIFTILIB_INCLUDE_DIR AND NIFTILIB_LIBRARY AND NIFTIZNZ_LIBRARY AND ZLIB_LIBRARY )
    SET( NIFTILIB_FOUND TRUE )
ENDIF()

IF( NIFTILIB_FOUND )
   IF( NOT niftilib_FIND_QUIETLY )
       MESSAGE( STATUS "Found niftilib: ${NIFTILIB_LIBRARY}, ${NIFTIZNZ_LIBRARY}, ${ZLIB_LIBRARY} and include in ${NIFTILIB_INCLUDE_DIR}" )
   ENDIF()
ELSE()
   IF( niftilib_FIND_REQUIRED )
       MESSAGE( FATAL_ERROR "Could not find niftilib. You can specify NIFTILIB_INCLUDE_DIR and NIFTILIB_LIBRARY_DIR environment variables to help
       OpenWalnut finding it. Also ensure to install the zlib development headers." )
   ENDIF()
ENDIF()

