cmake_minimum_required(VERSION 4.1)
project(3d_game)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_DIR "C:/Users/david/Documents/libs/glfw")

add_executable(3d_game main.cpp)


target_include_directories(3d_game PRIVATE
        "${GLFW_DIR}/include"
)

target_link_directories(3d_game PRIVATE
        "${GLFW_DIR}/lib-mingw-w64"
)

target_link_libraries(3d_game PRIVATE
        glfw3 opengl32 gdi32 user32 kernel32 winmm
)