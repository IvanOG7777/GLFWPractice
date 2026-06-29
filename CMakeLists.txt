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
        Header/Vector3.h
        Source/Vector3.cpp
        Header/Constants.h
        Header/Matrix4.h
        Source/Matrix4.cpp
        Header/Vector4.h
        Source/Vector4.cpp
)

target_include_directories(GLWFPractice PRIVATE
        ${CMAKE_SOURCE_DIR}/Libraries/include
)

target_link_libraries(GLWFPractice PRIVATE
        ${CMAKE_SOURCE_DIR}/Libraries/lib/glfw3.lib
        opengl32
)