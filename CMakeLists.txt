cmake_minimum_required(VERSION 3.17)

project(memorygame)

# turn colorized makefile OFF for Emacs
set(CMAKE_COLOR_MAKEFILE OFF)
 
# compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -pedantic)
endif()

# set directory variables
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

include_directories(${INC_DIR})

# add sources
set(SOURCES
  ${SRC_DIR}/Game.cpp
  ${SRC_DIR}/Main.cpp
  ${SRC_DIR}/Renderer.cpp
  ${SRC_DIR}/Square.cpp
  ${SRC_DIR}/GameOverState.cpp
  ${SRC_DIR}/GameState.cpp
  ${SRC_DIR}/GameStateMachine.cpp
  ${SRC_DIR}/MenuState.cpp
  ${SRC_DIR}/PlayState.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# sdl2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})

# sdl2_ttf
# find_package(SDL2_ttf REQUIRED)
# include_directories(${SDL2_TTF_INCLUDE_DIRS})
# target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

