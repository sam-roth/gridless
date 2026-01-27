cmake_minimum_required(VERSION 3.16)
project(gridless_gui VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SRC
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.hpp
    src/Canvas.cpp
    src/Canvas.hpp
    src/Point.cpp
    src/Point.hpp
    src/CreatePointCommand.cpp
    src/CreatePointCommand.hpp
    src/DeletePointsCommand.cpp
    src/DeletePointsCommand.hpp
    src/UpdatePointCommand.cpp
    src/UpdatePointCommand.hpp
    src/Inspector.cpp
    src/Inspector.hpp
    src/InspectorWidget.cpp
    src/InspectorWidget.hpp
    src/PointInspectorWidget.cpp
    src/PointInspectorWidget.hpp
    src/InspectorWidgetFactory.cpp
    src/InspectorWidgetFactory.hpp
)

add_executable(gridless ${SRC})

target_include_directories(gridless PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(gridless PRIVATE Qt6::Widgets)

if(MSVC)
  target_compile_options(gridless PRIVATE /W4 /permissive-)
else()
  target_compile_options(gridless PRIVATE -Wall -Wextra -Wpedantic)
endif()
