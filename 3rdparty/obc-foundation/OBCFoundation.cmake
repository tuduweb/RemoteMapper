# include当前目录到工程中
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

set(OBCFOUNDATION_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/OBCHelpers.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/OBCHelpers.hpp
        ${CMAKE_CURRENT_LIST_DIR}/src/utils/PureJson.hpp
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Gui Svg REQUIRED)
add_library(obc_fondation STATIC ${OBCFOUNDATION_SOURCES})
target_link_libraries(obc_fondation
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Svg)