#실행시 터미널에 rm -rf build && mkdir build && cd build && cmake .. && make && ./KnightsTour

cmake_minimum_required(VERSION 3.16)
project(KnightsTour)

# C++17 사용 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 Widgets 모듈 찾기
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Qt 관련 설정 자동화
set(CMAKE_AUTOMOC ON)   # Meta-Object Compiler 자동 실행
set(CMAKE_AUTOUIC ON)   # UI 파일 자동 처리
set(CMAKE_AUTORCC ON)   # Resource 파일 자동 처리
set(CMAKE_INCLUDE_CURRENT_DIR ON) # 헤더 경로 자동 포함

# 실행 파일 생성
add_executable(KnightsTour
    src/main.cpp
    src/gamewindow.cpp
    src/examplewindow.cpp
    src/mainwindow.cpp
    include/gamewindow.h
    include/examplewindow.h
    include/mainwindow.h
)


# include 디렉토리 추가 (헤더 파일 참조 경로)
target_include_directories(KnightsTour PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Qt6 라이브러리 연결
target_link_libraries(KnightsTour PRIVATE Qt6::Widgets)
