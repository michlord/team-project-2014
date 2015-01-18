cmake_minimum_required(VERSION 3.1.0-rc1)
project(ragemage CXX)
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )
cmake_policy(SET CMP0054 NEW)

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



find_package(GLM)

if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
else()
    set(GLM_ROOT_DIR "" CACHE PATH "The path to the glm library root folder.")
    message("\n-> GLM library not found. Set GLM_ROOT_DIR to GLM top-level path.")
endif()


# The idea is to keep this CMakeLists.txt very simple. This is a global place where
# the source and header should be specified. The paths should be relative to the
# root folder of this project. This will be replaced with add_subdirectory()
# once we define better project structure.

set(GAMELIB_SRC
    "src/EngineApp/EngineApp.cpp"
    "src/EngineApp/WindowContext.cpp"
    "src/EngineApp/FrameContext.cpp"
    "src/EngineApp/FrameListener.cpp"
    "src/EngineApp/SceneStack.cpp"

    "src/EngineSystem/Input/Input.cpp"
    "src/EngineSystem/Input/BinaryInput.cpp"
    "src/EngineSystem/Input/AxisInput.cpp"

    "src/EngineSystem/Input/InputHandler.cpp"
    "src/EngineSystem/Input/Context.cpp"

    "src/EngineSystem/Sound/SoundManager.cpp"

    "src/EngineSystem/Config/Config.cpp"
    "src/EngineSystem/Log/Log.cpp"

    "src/EngineSystem/Video/Render/Sprite.cpp"
    "src/EngineSystem/Video/Render/AnimatedSprite.cpp"
    "src/EngineSystem/Video/Render/Animation.cpp"

    "src/EngineSystem/Entity/BaseEntity.cpp"
    "src/EngineSystem/Entity/EntityManager.cpp"
    "src/EngineSystem/Entity/Message.cpp"
    "src/EngineSystem/Entity/MessageDispatcher.cpp"

    "src/EngineSystem/Assets/AssetsManager.cpp"

    "src/EngineSystem/Physics/Physics.cpp"
    "src/EngineSystem/Physics/Rectangle.cpp"
    "src/EngineSystem/Physics/Point.cpp"
    "src/EngineSystem/Physics/Circle.cpp"
    "src/EngineSystem/Physics/LinearFunction.cpp"
)

# This is for project generation purposes so that your .h files appear
# in your IDE's project browser.

set(GAMELIB_H
    "include/EngineApp/EngineApp.h"
    "include/EngineApp/WindowContext.h"
    "include/EngineApp/FrameContext.h"
    "include/EngineApp/FrameListener.h"
    "include/EngineApp/SceneStack.h"

    "include/EngineSystem/Input/Input.h"
    "include/EngineSystem/Input/BinaryInput.h"
    "include/EngineSystem/Input/AxisInput.h"

    "include/EngineSystem/Input/InputHandler.h"
    "include/EngineSystem/Input/Context.h"

    "include/EngineSystem/Sound/SoundManager.h"

    "include/EngineSystem/Config/Config.h"

    "include/EngineSystem/Log/Log.h"

    "include/EngineSystem/Video/Render/Sprite.h"
    "include/EngineSystem/Video/Render/AnimatedSprite.h"
    "include/EngineSystem/Video/Render/Animation.h"

    "include/EngineSystem/Entity/BaseEntity.h"
    "include/EngineSystem/Entity/StateMachine.h"
    "include/EngineSystem/Entity/State.h"
    "include/EngineSystem/Entity/EntityManager.h"
    "include/EngineSystem/Entity/Message.h"
    "include/EngineSystem/Entity/MessageDispatcher.h"

    "include/EngineSystem/Assets/AssetsManager.h"

    "include/EngineSystem/Physics/Physics.h"
    "include/EngineSystem/Physics/Rectangle.h"
    "include/EngineSystem/Physics/Point.h"
    "include/EngineSystem/Physics/Circle.h"
    "include/EngineSystem/Physics/LinearFunction.h"
)

set(GAME_SRC
    "src/Game/main.cpp"
    "src/Game/Scene/Intro.cpp"
    "src/Game/Scene/MainMenu.cpp"
    "src/Game/Scene/Gameplay.cpp"
    "src/Game/Menu/List.cpp"
    "src/Game/Menu/ListItem.cpp"
    "src/Game/Level/Decoration.cpp"
    "src/Game/Level/Level.cpp"
    "src/Game/Level/LevelManager.cpp"
    "src/Game/Level/Tile.cpp"
)

SET(GAME_H
    "include/Game/Scene/Intro.h"
    "include/Game/Scene/MainMenu.h"
    "include/Game/Scene/Gameplay.h"
    "include/Game/Menu/List.h"
    "include/Game/Menu/ListItem.h"
    "include/Game/Level/Decoration.h"
    "include/Game/Level/Level.h"
    "include/Game/Level/LevelManager.h"
    "include/Game/Level/Tile.h"
)

add_library(gamelib ${GAMELIB_SRC} ${GAMELIB_H})

target_link_libraries(gamelib
    ${SFML_LIBRARIES}
)

add_executable(game ${GAME_SRC} ${GAME_H})

target_link_libraries(game
    gamelib
)

include(CopyDistDlls)
copy_dist_dlls(game)

enable_testing()
add_subdirectory(test/examples)


file(GLOB_RECURSE ASSETS_DIRECTORY RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/assets/*)
message("${ASSETS_DIRECTORY}")
foreach(asset ${ASSETS_DIRECTORY})
    STRING(REGEX REPLACE "/" "_" asset_idx ${asset})
    add_custom_target("copy_${asset_idx}" ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/"${asset}"
        ${CMAKE_CURRENT_BINARY_DIR}/"${asset}")
endforeach(asset)



# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
# install(TARGETS game
    # EXPORT "Game"
    # RUNTIME DESTINATION bin
    # LIBRARY DESTINATION lib
    # ARCHIVE DESTINATION lib
# )
