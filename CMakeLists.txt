cmake_minimum_required(VERSION 3.29)
project(midterm_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 設置靜態連結選項
set(BUILD_SHARED_LIBS OFF)

# 針對不同編譯器的靜態連結設定
if (MSVC)
    # MSVC 編譯器的靜態連結設定
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options("/MT$<$<CONFIG:Debug>:d>")
else ()
    # MinGW/GCC 編譯器的靜態連結設定
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif ()

include(FetchContent)
# 設置SFML為靜態庫
set(SFML_BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Enable static libraries" FORCE)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp" "${CMAKE_SOURCE_DIR}/headers/*.h")
if (SRC_FILES)
    add_executable(${PROJECT_NAME} ${SRC_FILES}
            src/Button.cpp
            headers/Button.h
            src/GameState.cpp
            headers/GameState.h
            src/ResourceManager.cpp
            headers/ResourceManager.h
            src/ReversiGame.cpp
            headers/ReversiGame.h
            src/SplashScreen.cpp
            headers/SplashScreen.h
            src/MainMenu.cpp
            headers/MainMenu.h
            src/NewGameMenu.cpp
            headers/NewGameMenu.h
            src/TextInput.cpp
            headers/TextInput.h
            src/GameScreen.cpp
            headers/GameScreen.h
            src/VictoryScreen.cpp
            headers/VictoryScreen.h
            src/AboutScreen.cpp
            headers/AboutScreen.h
            src/LoadGameMenu.cpp
            headers/LoadGameMenu.h
            src/Timer.cpp
            headers/Timer.h
            src/SaveGame.cpp
            headers/SaveGame.h
    )
endif ()


target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

file(COPY assets/textures DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY assets/fonts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY assets/sounds DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY assets/music DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
