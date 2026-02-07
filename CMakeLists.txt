cmake_minimum_required(VERSION 3.19)

project(Sonograf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(DEV_COMPILE "Enable strict compile warnings" OFF)

add_compile_options(-Wall -Wextra)

if (DEV_COMPILE)
    add_compile_options(-Werror)
endif()

set(CPM_DOWNLOAD_VERSION 0.40.2)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        "${CMAKE_BINARY_DIR}/cmake/CPM.cmake"
    )
endif()

include("${CMAKE_BINARY_DIR}/cmake/CPM.cmake")

CPMAddPackage(
    NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    GIT_TAG 3.0.x
)

include_directories(.)
include_directories(src)
include_directories(src/Graphic/Menu)
include_directories(src/Graphic/Bouton)
include_directories(src/Graphic/Osilator)
include_directories(src/Graphic/ChooseMusic)
include_directories(src/Graphic/Plan)
include_directories(src/audio/AudioInput)
include_directories(src/audio/AudioOutput)
include_directories(src/audio/AudioProcessor)

add_executable(sonograf
    src/audio/AudioInput/AudioInput.cpp
    src/audio/AudioInput/AudioManager.cpp
    src/audio/AudioOutput/AudioOutput.cpp
    src/audio/AudioProcessor/AudioProcessor.cpp
    src/Graphic/Bouton/Bouton.cpp
    src/Graphic/Menu/Menu.cpp
    src/Graphic/Plan/Plan.cpp
    src/Graphic/Osilator/Osilator.cpp
    src/Graphic/ChooseMusic/FileExplorer.cpp
    src/Graphic/ChooseMusic/ChooseMusic.cpp
    src/SonoGraf.cpp
    src/main.cpp
)

target_link_libraries(sonograf
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
