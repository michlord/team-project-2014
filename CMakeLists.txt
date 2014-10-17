cmake_minimum_required(VERSION 2.8.9)
project(ragemage CXX)

# Set compiler flags.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(WARNINGS "-Wall -Wextra -Werror")
    set(EXTRA_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(WARNINGS "/W4 /WX /EHsc")
    # MSVC adds c++11 by default.
endif()
if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${WARNINGS} ${EXTRA_FLAGS}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


# Default build type is Release.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Type of build (Debug/Release)" FORCE)
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release.
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()


# Add cmake modules to CMAKE_MODULE_PATH.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")


# Include directories paths for the compiler.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2 COMPONENTS audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# The idea is to keep this CMakeLists.txt very simple. This is a global place where
# the source and header should be specified. The paths should be relative to the
# root folder of this project. This will be replaced with add_subdirectory() 
# once we define better project structure.

set(RAGEMAGE_SRCS
    src/main.cpp
    src/Game.cpp
    src/InputManager.cpp
    src/LibrariesManager.cpp
    src/LogicManager.cpp
    src/PhysicsManager.cpp
    src/RenderingManager.cpp
    src/Rendering/Window.cpp
)

# This is for project generation purposes so that your .h files appear
# in your IDE's project browser.

set(RAGEMAGE_H
    src/Game.h
    src/InputManager.h
    src/LibrariesManager.h
    src/LogicManager.h
    src/PhysicsManager.h
    src/RenderingManager.h
    src/Rendering/Window.h
)

add_executable(game ${RAGEMAGE_SRCS} ${RAGEMAGE_H})

target_link_libraries(game
    ${SFML_LIBRARIES}
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# install(TARGETS game
    # EXPORT "Game"
    # RUNTIME DESTINATION bin
    # LIBRARY DESTINATION lib
    # ARCHIVE DESTINATION lib
# )

# Copy dlls to executable directory. Windows makes my life hard.
if(WIN32)
    set(SFML_BIN_PATH ${SFML_ROOT}/bin)
    add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_BIN_PATH}"
        $<TARGET_FILE_DIR:game>)
endif()