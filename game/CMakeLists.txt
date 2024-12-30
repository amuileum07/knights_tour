# for building the project with cmake do the following:
# cd game 
# mkdir build
# cd build
# cmake ..
# make
# ./knights_tour_app

cmake_minimum_required(VERSION 3.5)

project(knights_tour)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(knights_tour_app main.cpp)

target_link_libraries(knights_tour_app Qt5::Widgets)
