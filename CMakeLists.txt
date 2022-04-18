cmake_minimum_required(VERSION 3.17)

project(memorygame)

# turn colorized makefile OFF for Emacs
set(CMAKE_COLOR_MAKEFILE OFF)
 
# compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

# set directory variables
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# add sources
set(SOURCES
  # header files
  ${SRC_DIR}/Box.h
  ${SRC_DIR}/Game.h
  ${SRC_DIR}/GameOverState.h
  ${SRC_DIR}/GameState.h
  ${SRC_DIR}/GameStateMachine.h
  ${SRC_DIR}/MenuState.h
  ${SRC_DIR}/PlayState.h
  ${SRC_DIR}/Renderer.h
  ${SRC_DIR}/TextureManager.h

  # object files
  ${SRC_DIR}/Box.cpp
  ${SRC_DIR}/Game.cpp
  ${SRC_DIR}/GameOverState.cpp
  ${SRC_DIR}/GameState.cpp
  ${SRC_DIR}/GameStateMachine.cpp
  ${SRC_DIR}/Main.cpp
  ${SRC_DIR}/MenuState.cpp
  ${SRC_DIR}/PlayState.cpp
  ${SRC_DIR}/Renderer.cpp
  ${SRC_DIR}/TextureManager.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})

# module directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

# sdl2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

# sdl2_ttf
# find_package(SDL2_ttf REQUIRED)
# include_directories(${SDL2_TTF_INCLUDE_DIRS})
# target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
