# Install script for directory: /home/noah/Developer/visual_computing_openwalnut/src/modules/template

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

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/openwalnut/template/libtemplate.so.1.5.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/openwalnut/template/libtemplate.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/openwalnut/template" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/home/noah/Developer/visual_computing_openwalnut/build/lib/openwalnut/template/libtemplate.so.1.5.0"
    "/home/noah/Developer/visual_computing_openwalnut/build/lib/openwalnut/template/libtemplate.so.1"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/openwalnut/template/libtemplate.so.1.5.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/openwalnut/template/libtemplate.so.1"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/noah/Developer/visual_computing_openwalnut/build/lib:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateColormapping-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateColormapping-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Cel-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Cel-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Edge-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Edge-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Merge-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Merge-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Render-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateRenderPipelines-Render-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateShaders-Plane-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateShaders-Plane-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateShaders-Spheres-fragment.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template/shaders" TYPE FILE FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/shaders/WMTemplateShaders-Spheres-vertex.glsl")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "MODULES" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/openwalnut/modules/template" TYPE DIRECTORY FILES "/home/noah/Developer/visual_computing_openwalnut/src/modules/template/resources/" REGEX "/bin\\/[^/]*$" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif()

