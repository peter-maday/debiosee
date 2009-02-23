project(Debiosee)

cmake_minimum_required(VERSION 2.4.6)
mark_as_advanced(CMAKE_BACKWARDS_COMPATIBILITY)

set(DEBIOSEE_SOURCE_DIR ${${PROJECT_NAME}_SOURCE_DIR})
set(DEBIOSEE_BINARY_DIR ${${PROJECT_NAME}_BINARY_DIR})

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Find dolfin
#set(FENICS_PKG_CONFIG_DIR "/media/USB-WD-1/dev-ubuntu/FEniCS-dev/build/lib/pkgconfig" CACHE PATH "Path to FEniCS installation directory")
set(FENICS_PKG_CONFIG_DIR "/media/USB-WD-1/dev-ubuntu/FEniCS-dev/build/lib/pkgconfig")
set(ENV{PKG_CONFIG_PATH} "${FENICS_PKG_CONFIG_DIR}")
find_package(PkgConfig)
pkg_check_modules(DOLFIN dolfin)
if(NOT DOLFIN_FOUND)
	message("Package DOLFIN was not found. If it is installed in a non-standard directory, set FENICS_PKG_CONFIG_DIR to the right directory, eg, c:/fenics/build/lib/pkgconfig")
endif(NOT DOLFIN_FOUND)
link_directories(${DOLFIN_LIBRARY_DIRS})
include_directories(${DOLFIN_INCLUDE_DIRS})
add_definitions(${DOLFIN_CFLAGS} ${DOLFIN_LDFLAGS})

# Image back-ends
set(DEBIOSEE_IMAGE_BACKEND_ITK ON CACHE BOOL "Enable ITK as an image library back-end (Recommanded)")
set(IMAGE_BACKEND_FLAGS "" CACHE INTERNAL "Image back end flags")

# ITK back-end
if(DEBIOSEE_IMAGE_BACKEND_ITK)
    # Find ITK
    find_package(ITK REQUIRED)
    include(${ITK_USE_FILE})
    # Add to the flags
    set(IMAGE_BACKEND_FLAGS ${IMAGE_BACKEND_FLAGS} "-DHAS_ITK")
endif()

# Add the back-end flags
add_definitions(${IMAGE_BACKEND_FLAGS})

# Include path
include(${DEBIOSEE_SOURCE_DIR}/DebioseeIncludeDirs.cmake)
include_directories(${DEBIOSEE_INCLUDE_DIRS})

# Source files
add_subdirectory(${DEBIOSEE_SOURCE_DIR}/Source)

# Test files
set(DEBIOSSE_BUILD_TESTS ON CACHE BOOL "Enable building tests.")
if(DEBIOSSE_BUILD_TESTS)
add_subdirectory(${DEBIOSEE_SOURCE_DIR}/Tests)
endif()

# Demo files
set(DEBIOSSE_BUILD_DEMOS ON CACHE BOOL "Enable building demos.")
if(DEBIOSSE_BUILD_DEMOS)
add_subdirectory(${DEBIOSEE_SOURCE_DIR}/Demos)
endif()

# Wrapping support
set(DEBIOSSE_WRAP_PYTHON ON CACHE BOOL "Enable wrapping Debiosee to Python.")
if(DEBIOSSE_WRAP_PYTHON)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Wrap")
endif()
