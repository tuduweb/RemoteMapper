cmake_minimum_required(VERSION 3.14)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
    FATAL: In-source builds are not allowed.
           You should create a separate directory for build files.
           ")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # doesnt work
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

IF (APPLE)
set(QT_DIR "/usr/local/opt/qt5/lib/cmake")
set(QT5_DIR ${QT_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/opt/qt5/lib/cmake")
ENDIF()

project(OBCApp VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets SerialPort Quick WebSockets Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets SerialPort Quick WebSockets Network LinguistTools REQUIRED)

if(ANDROID)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS AndroidExtras REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS AndroidExtras REQUIRED)
endif()


#### base & core
include(cmake/components/obc-base.cmake)

include(cmake/components/obc-plugin.cmake)


include(3rdparty/obc-foundation/OBCFoundation.cmake)
#message(${OBCFOUNDATION_SOURCES})
#add_subdirectory(3rdparty/obc-foundation/)
#target_link_libraries(OBCApp PRIVATE spdlog::spdlog)

add_definitions(-DOBC_GUI_QWIDGETS)
include(cmake/components/obc-ui-widget.cmake)
list(APPEND OBC_UI_SOURCES ${OBC_UI_WIDGET_SOURCES})

add_library(obc_baselib STATIC
    ${OBCFOUNDATION_SOURCES}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/plugin/)

target_include_directories(obc_baselib
    PUBLIC
    ${OBCFOUNDATION_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#### ui
#include(cmake/components/obc-ui.cmake)
#include(cmake/components/obc-ui-qml.cmake)

#### 3rdparty
### include(3rdparty/QJsonStruct/QJsonStruct.cmake)
#add_subdirectory(3rdparty/spdlog/)

#set(TS_FILES translations/OBCApp_zh_CN.ts)

set(PROJECT_SOURCES
        #resources.qrc
        src/main.cpp
        #src/painteditem.h src/painteditem.cpp
        #src/PaintingBoard.hpp src/PaintingBoard.cpp
        #src/ui/qml/qml.qrc
        #${OBC_QML_SOURCES}
        ${OBC_BASE_SOURCES}
        ${OBC_PLUGIN_SOURCES}
        ${OBC_UI_SOURCES}
        #${TS_FILES}

        src/core/settings/SettingsBackend.cpp
        src/core/settings/SettingsBackend.hpp

        src/core/handler/BundleHandler.cpp
        src/core/handler/BundleHandler.hpp

        src/core/handler/LinkHandler.cpp
        src/core/handler/LinkHandler.hpp

)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OBCApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(OBCApp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(OBCApp
        ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


### add extra qt library
target_link_libraries(obc_baselib
    PUBLIC Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(OBCApp
    PRIVATE obc_baselib
)


if(FALSE)
    target_compile_definitions(OBCApp
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)


    if(ANDROID)
        target_link_libraries(OBCApp
        PRIVATE Qt${QT_VERSION_MAJOR}::AndroidExtras)
    endif()

    set_target_properties(OBCApp PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )

endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(OBCApp)
    qt_finalize_executable(OBCApp)
endif()


# 项目中使用第三方库, spdlog
# target_link_libraries(OBCApp PRIVATE spdlog::spdlog)

include(3rdparty/QJsonStruct/QJsonStruct.cmake)

############
get_property(dirs DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message(">>> include_dirs=${dirs}") #打印一下目录情况

# # The setting of the environment variable only happens at cmake time, and not at build time.
set(ENV{OBC_CONFIG_PATH} "/Users/bin/qt-project/OBCApp/asserts/config")
if(DEFINED ENV{OBC_CONFIG_PATH})
    add_definitions(-DOBC_CONFIG_PATH="$ENV{OBC_CONFIG_PATH}")
else()
add_definitions(-DOBC_CONFIG_PATH="")
endif()

add_subdirectory(./examples)