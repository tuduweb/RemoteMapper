set(OBC_BASEDIR_COMPONENTS ${CMAKE_SOURCE_DIR}/src/components)
set(OBC_BASEDIR_CORE ${CMAKE_SOURCE_DIR}/src/core)
set(OBC_BASEDIR_BASE ${CMAKE_SOURCE_DIR}/src/base)
set(OBC_BASEDIR_BASE_INTERFACE ${CMAKE_SOURCE_DIR}/src/base/interface)
set(OBC_BASEDIR_UI ${CMAKE_SOURCE_DIR}/src/ui)

set(OBC_BASE_SOURCES
    #
    #${CMAKE_SOURCE_DIR}/src/utils/OBCHelpers.cpp
    #${CMAKE_SOURCE_DIR}/src/utils/OBCHelpers.hpp

    ${OBC_BASEDIR_BASE}/OBCBaseHeader.hpp

    ${CMAKE_SOURCE_DIR}/src/base/models/OBCSafeType.hpp
    ${CMAKE_SOURCE_DIR}/src/base/models/OBCIdentifier.hpp
    ${CMAKE_SOURCE_DIR}/src/base/models/OBCSettingsObject.hpp

    # APPLICAITONS
    ${OBC_BASEDIR_BASE}/OBCBaseApplication.hpp
    ${OBC_BASEDIR_BASE}/OBCBaseApplication.cpp
    ${OBC_BASEDIR_UI}/OBCPlatformApplication.hpp
    ${OBC_BASEDIR_UI}/widgets/OBCWidgetApplication.hpp
    ${OBC_BASEDIR_UI}/widgets/OBCWidgetApplication.cpp

    # move to extra file
    ${OBC_BASEDIR_CORE}/settings/SettingsBackend.cpp
    ${OBC_BASEDIR_CORE}/settings/SettingsBackend.hpp


    ${OBC_BASEDIR_CORE}/handler/ConfigHandler.cpp
    ${OBC_BASEDIR_CORE}/handler/ConfigHandler.hpp

    ## Links
    ${OBC_BASEDIR_CORE}/link/LinkInterface.cpp
    ${OBC_BASEDIR_CORE}/link/LinkInterface.hpp

    #${OBC_BASEDIR_CORE}/link/SerialLink.hpp
    #${OBC_BASEDIR_CORE}/link/SerialLink.cpp

    ${OBC_BASEDIR_CORE}/link/SerialThread.hpp
    ${OBC_BASEDIR_CORE}/link/SerialThread.cpp

    #interfaces
    ${OBC_BASEDIR_BASE_INTERFACE}/StreamInterface.hpp
    ${OBC_BASEDIR_BASE_INTERFACE}/ControlInterface.hpp
    ${OBC_BASEDIR_BASE_INTERFACE}/DisplayInterface.hpp

    ${OBC_BASEDIR_BASE_INTERFACE}/DeviceInterface.hpp

    #stream
    ${OBC_BASEDIR_CORE}/stream/data/SerialDataStream.hpp
    ${OBC_BASEDIR_CORE}/stream/data/SerialDataStream.cpp

    #end
)