cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


if(NOT OB_QT_LIBNAME)
    set(OB_QT_LIBNAME Qt5)
endif()

message("PlugInterface DIR : " ${CMAKE_CURRENT_LIST_DIR})

set(OBPLUGIN_INTERFACE_HEADERS

    ${CMAKE_CURRENT_LIST_DIR}/PluginBase.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PluginInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/GUIPluginInterface.hpp
    #${CMAKE_CURRENT_LIST_DIR}/PluginInterfaceModels.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PluginProcessor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/handler/KernelHandler.hpp
)

set(OBPLUGIN_INTERFACE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
