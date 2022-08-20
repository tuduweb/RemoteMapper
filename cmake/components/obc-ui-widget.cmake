set(OBC_WIDGETS_UI_BASEDIR ${CMAKE_SOURCE_DIR}/src/ui/widgets)
add_definitions(-DQAPPLICATION_CLASS=QApplication)

set(_OBC_UI_FORMS
    #
    ${OBC_WIDGETS_UI_BASEDIR}/windows/w_MainWindow.ui
    ${OBC_WIDGETS_UI_BASEDIR}/widgets/NormalDisplayWidget.ui

    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_RemoteEditor.ui

    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_JsonEditor.ui
)

set(_OBC_UI_SOURCES
    ${OBC_WIDGETS_UI_BASEDIR}/windows/w_MainWindow.hpp
    ${OBC_WIDGETS_UI_BASEDIR}/windows/w_MainWindow.cpp


    ${OBC_WIDGETS_UI_BASEDIR}/widgets/NormalDisplayWidget.hpp
    ${OBC_WIDGETS_UI_BASEDIR}/widgets/NormalDisplayWidget.cpp
    ${OBC_WIDGETS_UI_BASEDIR}/widgets/FrameDisplayWidget.cpp
    ${OBC_WIDGETS_UI_BASEDIR}/widgets/FrameDisplayWidget.hpp

    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_RemoteEditor.cpp
    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_RemoteEditor.hpp

    # from v2ray
    ${OBC_WIDGETS_UI_BASEDIR}/common/QJsonModel.cpp
    ${OBC_WIDGETS_UI_BASEDIR}/common/QJsonModel.hpp
    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_JsonEditor.cpp
    ${OBC_WIDGETS_UI_BASEDIR}/editors/w_JsonEditor.hpp

    #interface
    ${OBC_WIDGETS_UI_BASEDIR}/interface/ControlBaseWidget.hpp
    ${OBC_WIDGETS_UI_BASEDIR}/interface/ConfigureBaseWidget.hpp
)

set(OBC_UI_WIDGET_SOURCES ${_OBC_UI_FORMS} ${_OBC_UI_SOURCES})
