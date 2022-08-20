cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME OBCFoundation)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF (APPLE)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/opt/qt5/lib/cmake")
ENDIF()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING OFF)
include(OBCFoundation.cmake)

enable_testing()


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)
#Quick WebSockets Network


set(PROJECT_SOURCES
        src/main.cpp
        ${OBCFOUNDATION_SOURCES}
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

### add extra qt library
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)
#Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::Network


# ==================================================================================
# Qv2ray Unit Tests
# ==================================================================================

if(BUILD_TESTING)
    #include(CTest) #Dashboard Preparation
    add_subdirectory(test)
endif()