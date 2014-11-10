cmake_minimum_required(VERSION 2.7 FATAL_ERROR)

project(GAME)

set(CMAKE_MODULE_PATH ${GAME_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(${CMAKE_MODULE_PATH} "\n" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
#find_package(OpenGL REQUIRED)

set( GAME_INCLUDE_DIR
	"src/"
	${SDL2_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
#	${OPENGL_INCLUDE_DIR} 
)
set( GAME_LIB_DIR
	${SDL2_LIBRARY_DIRS}
	${GLEW_LIBRARY_DIRS}
	${GLM_LIBRARY_DIRS}
#	${OPENGL_LIBRARY_DIRS} 
)
set( GAME_LIBRARIES
	${SDL2_LIBRARY}
	${GLEW_LIBRARIES}
	${GLM_LIBRARIES}
#	${OPENGL_LIBRARIES} 
)

file(GLOB GAME_SRC
	"src/*.cpp"
	"src/*/*.cpp" )

set(CMAKE_CXX_FLAGS "-g -std=c++11" ${MAKE_CXX_FLAGS})

include_directories(${GAME_INCLUDE_DIR})
link_directories(${GAME_LIB_DIR})
add_executable(sdl-app ${GAME_SRC})
target_link_libraries(sdl-app ${GAME_LIBRARIES})




