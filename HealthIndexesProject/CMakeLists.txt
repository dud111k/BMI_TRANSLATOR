cmake_minimum_required(VERSION 3.16)

project(HealthIndexesProject)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

add_executable(HealthIndexesProject ${SOURCES})

target_link_libraries(HealthIndexesProject Qt5::Widgets)

# Copy qm

add_custom_command(TARGET HealthIndexesProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/app_en.qm
    $<TARGET_FILE_DIR:HealthIndexesProject>/
)
