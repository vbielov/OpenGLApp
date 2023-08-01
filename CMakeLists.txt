cmake_minimum_required(VERSION 3.12)

project(OpenGLApp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS "./src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src
)

include_directories( ${OPENGL_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME} ${CMAKE_LIBRARY_PATH}/libglfw3.a OpenGL::GL ${CMAKE_LIBRARY_PATH}/libGLEW.a X11)