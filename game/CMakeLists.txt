cmake_minimum_required(VERSION 3.16)

# 프로젝트 이름
project(knight's tour)

# Qt 패키지 찾기
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# 소스 파일 설정
set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

# 실행 파일 빌드
add_executable(${PROJECT_NAME} ${SOURCES})

# Qt 라이브러리 연결
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
