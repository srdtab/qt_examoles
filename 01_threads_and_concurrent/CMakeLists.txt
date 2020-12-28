cmake_minimum_required(VERSION 3.5)

project(01_threads_and_concurrent LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Concurrent REQUIRED)

add_executable(01_threads_and_concurrent
    mainwindow.ui
    main.cpp
    mainwindow.cpp
    mainwindow.h
    worker.cpp
    worker.h
    )


target_link_libraries(01_threads_and_concurrent PRIVATE Qt5::Widgets Qt5::Concurrent)
