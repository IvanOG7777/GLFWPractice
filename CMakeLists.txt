cmake_minimum_required(VERSION 3.28)

project(glfwPractice)

set(CMAKE_CXX_STANDARD 20)


add_executable(GLWFPractice
        Source/main.cpp
        Source/glad.c
        Header/GLUtils.h
        Source/GLUtils.cpp
        Header/Geometry.h
        Source/Geometry.cpp
        Header/Constants.h
        Header/Camera.h
        Source/Camera.cpp
        Header/Sphere.h
        Source/Sphere.cpp
)

target_include_directories(GLWFPractice PRIVATE
        ${CMAKE_SOURCE_DIR}/Libraries/include
)

target_link_libraries(GLWFPractice PRIVATE
        ${CMAKE_SOURCE_DIR}/Libraries/lib/glfw3.lib
        opengl32
)