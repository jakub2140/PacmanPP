cmake_minimum_required(VERSION 3.16)
project(Pacman_plusplus LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
include_directories(Pacman_plusplus ${CMAKE_SOURCE_DIR}/header)
include_directories(Pacman_plusplus PUBLIC ${CMAKE_SOURCE_DIR}/graphics)
set(SOURCES src/main.cpp
			src/map_creator.cpp
            src/Pacman.cpp
            src/Ghosts.cpp
           
            src/Manager.cpp

			
            
            header/constants.h
			header/map_creator.h
			header/Pacman.h
            header/Ghosts.h
            header/collision.h
            header/Manager.h

			)

add_executable(Pacman_plusplus ${SOURCES})
target_link_libraries(Pacman_plusplus PRIVATE sfml-graphics ${CMAKE_SOURCE_DIR}/Collision_library.lib)
target_compile_features(Pacman_plusplus PRIVATE cxx_std_20)



if(WIN32)
    add_custom_command(
        TARGET Pacman_plusplus
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Pacman_plusplus>
        VERBATIM)
endif()

install(TARGETS Pacman_plusplus)
