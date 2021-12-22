cmake_minimum_required(VERSION 2.8.11)
project(TinyPasswordGenerator LANGUAGES CXX)

set(CMAKE_C_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

find_package(Qt5 COMPONENTS Core Gui Widgets)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB_RECURSE source source/*.cpp source/*.hpp)

include_directories(source)

add_executable(TinyPasswordGenerator source/Main.cpp ${source} TinyPasswordGenerator.rc TinyPasswordGenerator.qrc)

qt5_use_modules(TinyPasswordGenerator Core Gui Widgets)
