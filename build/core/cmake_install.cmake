# Install script for directory: /home/noah/Developer/visual_computing_openwalnut/src/core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so.1.5.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/home/noah/Developer/visual_computing_openwalnut/build/lib/libopenwalnut.so.1.5.0"
    "/home/noah/Developer/visual_computing_openwalnut/build/lib/libopenwalnut.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so.1.5.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "/home/noah/Developer/visual_computing_openwalnut/build/lib/libopenwalnut.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenwalnut.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/W2DTFMapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WAssert.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WBoundingBox.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WColor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WCondition.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WConditionOneShot.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WConditionSet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WCounter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WDefines.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WException.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WFlag.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WFlagForwarder.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHierarchicalTree.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHierarchicalTreeFibers.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHierarchicalTreeVoxels.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHistogram.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHistogram2D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHistogramBasic.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WHistogramND.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WIOTools.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WItemSelection.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WItemSelectionItem.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WItemSelectionItemTyped.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WItemSelector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WLimits.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WLogEntry.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WLogStream.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WLogger.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WMixinVector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WObjectNDIP.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPathHelper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPredicateHelper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WProgress.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WProgressCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WProjectFileIO.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WProperties.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WProperties_Fwd.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyBase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyGroup.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyGroupBase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyHelper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyList.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyObserver.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyStruct.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyTypes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPropertyVariable.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WPrototyped.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WRealtimeTimer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WRequirement.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSegmentationFault.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedAssociativeContainer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedLib.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedObject.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedObjectTicket.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedObjectTicketRead.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedObjectTicketWrite.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WSharedSequenceContainer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WStrategyHelper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WStringUtils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WStructuredTextParser.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTerminalColor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WThreadedFunction.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WThreadedJobs.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WThreadedRunner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WThreadedRunnerSignals.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTimer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTransferFunction.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTransferFunction2D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTransferable.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WTypeTraits.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/WWorkerThread.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/algorithms" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/algorithms/WMarchingCubesAlgorithm.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/algorithms" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/algorithms/WMarchingCubesCaseTables.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/algorithms" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/algorithms/WMarchingLegoAlgorithm.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintConfirmOverwrite.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintIsDirectory.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintIsValid.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintMax.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintMin.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintNotEmpty.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintPathExists.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintSelectOnlyOne.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/constraints" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/constraints/WPropertyConstraintTypes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/datastructures/WColoredVertices.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/datastructures/WDendrogram.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/datastructures/WFiber.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/datastructures/WSinglePosition.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/datastructures/WUnionFind.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WEquationHasNoRoots.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WFileNotFound.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WFileOpenFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WInvalidBoundingBox.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WInvalidID.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WLibraryFetchFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WLibraryLoadFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WNameNotUnique.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WNotFound.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WNotImplemented.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WOutOfBounds.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WParseError.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WPreconditionNotMet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WPropertyNameMalformed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WPropertyNotUnique.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WPropertyUnknown.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WSignalSubscriptionFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WSignalSubscriptionInvalid.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WSignalUnknown.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/exceptions/WTypeMismatch.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WCompileTimeFunctions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WGeometryFunctions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WInterval.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WLine.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WLinearAlgebraFunctions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WMath.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WMatrix.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WMatrixSym.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WOSSIMHelper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WPlane.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WPolynomialEquationSolvers.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WSymmetricSphericalHarmonic.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WTensor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WTensorBase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WTensorFunctions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WTensorMeta.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WTensorSym.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WUnitSphereCoordinates.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/WValue.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/linearAlgebra" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/linearAlgebra/WMatrixFixed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/linearAlgebra" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/linearAlgebra/WMatrixInitializers.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/linearAlgebra" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/linearAlgebra/WPosition.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/linearAlgebra" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/linearAlgebra/WVectorFixed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/principalComponentAnalysis" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/principalComponentAnalysis/WCovarianceSolver.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/common/math/principalComponentAnalysis" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/common/math/principalComponentAnalysis/WPrincipalComponentAnalysis.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WCreateColorArraysThread.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataHandler.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataHandlerEnums.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetCSV.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetDTI.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetDipoles.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetFiberClustering.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetFiberVector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetFibers.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetHierarchicalClustering.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetHistogram1D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetMatrix.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetPoints.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetRawHARDI.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetScalar.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetSegmentation.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetSingle.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetSphericalHarmonics.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetTimeSeries.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataSetVector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WDataTexture3D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WEEG.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WEEGChannelInfo.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WEEGPositionsLibrary.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WEEGSegment.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WEEGValueMatrix.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WFiberAccumulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WGrid.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WGridRegular3D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WGridTransformOrtho.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WITKImageConversion.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WIteratorRange.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WPersonalInformation.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WRecording.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WSubject.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WThreadedPerVoxelOperation.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WThreadedTrackingFunction.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WTractAdapter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WTractData.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WValueSet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/WValueSetBase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/datastructures/WFiberCluster.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/datastructures/WJoinContourTree.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/datastructures/WTreeNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/datastructures" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/datastructures/WValueSetHistogram.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHException.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHIOFailure.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHNoSuchDataSet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHNoSuchFile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHNoSuchSubject.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHParseError.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/exceptions/WDHValueSetMismatch.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WPagerEEG.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WPagerEEGDummy.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WReader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WReaderMatrixSymVTK.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WWriter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WWriterDendrogram.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WWriterFiberVTK.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/dataHandler/io" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/dataHandler/io/WWriterMatrixSymVTK.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WFiberDrawable.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGE2DManipulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEAdvancedManipulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGECamera.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEColormapping.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEGeodeUtils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEGeometryUtils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEGraphicsWindow.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEGroupNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEImage.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEManagedGroupNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGENoOpManipulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEProjectFileIO.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGERequirement.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEScene.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEScreenCapture.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGESignals.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGESubdividedPlane.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGETexture.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGETextureHud.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGETextureUtils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGETypeTraits.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEUtils.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEViewer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEViewerEffect.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEViewerEffectHorizon.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEViewerEffectImageOverlay.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEViewerEffectVignette.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEZoomTrackballManipulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGEZoomTrackballNodeVisitor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WGraphicsEngine.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WMouseLocationHandler.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WPickHandler.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WPickHandler3D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WPickInfo.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WPickInfo3D.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WROI.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WROIArbitrary.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WROIBox.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WROISphere.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WStaticOSGSetup.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/WTriangleMesh.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/animation" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/animation/WGEAnimationFrameTimer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/animation" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/animation/WGEAnimationManipulator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGECallbackTraits.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGEFunctorCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGELinearTranslationCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGENodeMaskCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGEPropertyTransformationCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGEPropertyUniformCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGEShaderAnimationCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGESwitchCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGETexMatUniformCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/callbacks" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/callbacks/WGEViewportCallback.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/exceptions/WGEException.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/exceptions/WGEInitFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/exceptions/WGESignalSubscriptionFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/geodes" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/geodes/WDendrogramGeode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/geodes" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/geodes/WGEGridNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/offscreen" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/offscreen/WGEOffscreenFinalPass.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/offscreen" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/offscreen/WGEOffscreenRenderNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/offscreen" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/offscreen/WGEOffscreenRenderPass.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/offscreen" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/offscreen/WGEOffscreenTexturePass.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/onscreenSelection" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/onscreenSelection/WOnscreenSelection.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/onscreenSelection" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/onscreenSelection/WOnscreenSelectionHandler.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessingNode.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorCelShading.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorEdgeEnhance.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorGauss.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorHalftone.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorLineAO.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorMergeOp.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/postprocessing" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/postprocessing/WGEPostprocessorSSAO.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEPropertyUniform.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderCodeInjector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderDefine.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderDefineOptions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderPreprocessor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderPropertyDefine.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderPropertyDefineOptions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEShaderVersionPreprocessor.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/WGEUniformTypeTraits.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/widgets" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/widgets/WOSGButton.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/widgets" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/widgets/WOSGButtonLabel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/widgets/labeling" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/widgets/labeling/WGEBorderLayout.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/widgets/labeling" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/widgets/labeling/WGELabel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/graphicsEngine/widgets/labeling" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/widgets/labeling/WGELayoutableItem.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WBatchLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WCrosshair.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WDataModule.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WDataModuleInput.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WDataModuleInputFile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WDataModuleInputFilter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WDataModuleInputFilterFile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WFiberSelector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WKdTree.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WKernel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModule.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleCombinerTypes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleConnector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleConnectorSignals.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleContainer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleFactory.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleInputConnector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleInputData.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleInputForwardData.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleLoader.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleMetaInformation.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleOutputConnector.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleOutputData.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleOutputForwardData.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleSignals.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WModuleTypes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WProjectFile.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WPrototypeRequirement.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WRMBranch.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WROIManager.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WRoiProjectFileIO.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WSelectionManager.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WSelectorBranch.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/WSelectorRoi.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/combiner" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/combiner/WApplyCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/combiner" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/combiner/WDisconnectCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/combiner" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/combiner/WModuleOneToOneCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/combiner" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/combiner/WModuleProjectFileCombiner.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WKernelException.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleAlreadyAssociated.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectionFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectionInvalid.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectorInitFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectorModuleLockFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectorNotFound.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectorUnconnected.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleConnectorsIncompatible.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleDisconnectFailed.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleException.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleRequirementNotMet.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WModuleUninitialized.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WPrototypeNotUnique.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/kernel/exceptions" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/kernel/exceptions/WPrototypeUnknown.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/WScriptEngine.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/WScriptInterpreter.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/python" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/python/WScriptInterpreterPython.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WColorWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WInputConnectorWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WLoggerWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WModuleContainerWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WModuleWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WOutputConnectorWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WPropertyGroupWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WPropertyWrapper.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/scripting/wrappers" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/scripting/wrappers/WUtilityFunctions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUI.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIGridWidget.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIPropertyGroupWidget.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIRequirement.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUITabbedWidget.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIViewEventHandler.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIViewWidget.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIWidgetBase.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core/ui" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/ui/WUIWidgetFactory.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/openwalnut/core" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/build/versionHeader/core/WVersion.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DEV" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/build/lib/pkgconfig/openwalnut.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/home/noah/Developer/visual_computing_openwalnut/src/../resources/core/" REGEX "/bin\\/[^/]*$" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libopenwalnut1" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/../AUTHORS")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libopenwalnut1" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/../CONTRIBUTORS")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libopenwalnut1" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/../COPYING")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libopenwalnut1" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/../COPYING.LESSER")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE_DOC" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/libopenwalnut1" TYPE DIRECTORY OPTIONAL FILES "/home/noah/Developer/visual_computing_openwalnut/src/../doc/core/html")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/onscreenSelection/shaders/WOnscreenSelection-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/onscreenSelection/shaders/WOnscreenSelection-geometry.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/onscreenSelection/shaders/WOnscreenSelection-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraHorizon-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraHorizon-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraOverlayTexture-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraOverlayTexture-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraVignette-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECameraVignette-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEColorMapsImproved.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEColormapping-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEColormapping-uniforms.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEColormapping-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECoordinateSystem-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECoordinateSystem-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECullProxyShader-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGECullProxyShader-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGELighting-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGELighting-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessing.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessor-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessor-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessorCombiner-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessorCombiner-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessorUtils-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEPostprocessorUtils-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEShader-attributes.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEShader-uniforms.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEShadingTools.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGETensorTools.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGETextureTools.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGETransformationTools.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "CORE" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/core/graphicsEngine/shaders/shaders/WGEUtils.glsl")
endif()

