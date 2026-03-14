project(calculatorwid LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED
    include/calculator.h
    src/calculator.cpp
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Widgets
)
