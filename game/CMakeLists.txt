#cd game
#mkdir build
#cd build
#cmake ..
#make
#./KnightsTour

cmake_minimum_required(VERSION 3.5)

project(KnightsTour)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Widgets REQUIRED)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

add_executable(KnightsTour
    ${SOURCES}
    ${MOC_SOURCES}
)

target_include_directories(KnightsTour PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(KnightsTour Qt5::Widgets)