#cd build
#cmake ..
#make
#./KnightsTour

cmake_minimum_required(VERSION 3.16)

# 프로젝트 이름 및 설정
project(KnightsTour VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 Widgets 모듈 찾기
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Qt의 자동화된 처리 활성화
set(CMAKE_AUTOMOC ON)   # moc 파일 자동 생성
set(CMAKE_AUTOUIC ON)   # .ui 파일 자동 처리
set(CMAKE_AUTORCC ON)   # .qrc 파일 자동 처리
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # 현재 디렉토리 포함

# 소스 파일 설정
set(SOURCES
    main.cpp
    gamewindow.cpp
    examplewindow.cpp
    mainwindow.cpp
)

# 실행 파일 생성
qt_add_executable(KnightsTour
    ${SOURCES}
)

# Qt 라이브러리 연결
target_link_libraries(KnightsTour PRIVATE Qt6::Widgets)
