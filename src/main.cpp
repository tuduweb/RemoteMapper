#include <iostream>
#include <QDebug>

#include "utils/OBCHelpers.hpp"

#include <QApplication>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include <QSerialPort>
#include <QSerialPortInfo>

#include "core/handler/ConfigHandler.hpp"

#include "core/link/SerialLink.hpp"

//#include "plugin/examples/mock/MockKernel.hpp"

#include "plugin/PluginInterface.hpp"
#include "plugin/GUIPluginInterface.hpp"

#include "plugin/examples/mock/MockPlugin.hpp"
#include "plugin/examples/mock/MockGUI.hpp"
#include "plugin/PluginProcessor.hpp"
#include <QPluginLoader>

#include <QObject>

#include "core/handler/ConfigHandler.hpp"
#include "core/settings/SettingsBackend.hpp"

#include "base/OBCBaseHeader.hpp"

#include "ui/widgets/OBCWidgetApplication.hpp"

#define OBC_VERSION_STRING "1.2.3"

int main(int argc, char *argv[])
{

    //
    // This line must be called before any other ones, since we are using these
    // values to identify instances.
    QCoreApplication::setApplicationVersion(OBC_VERSION_STRING);

#ifdef QT_DEBUG
    QCoreApplication::setApplicationName("obc_debug");
#else
    QCoreApplication::setApplicationName("obc");
#endif

#ifdef OBC_GUI
    QApplication::setApplicationDisplayName("obc");
#endif

#ifdef QT_DEBUG
    std::cerr << "WARNING: ================ This is a debug build, many features are not stable enough. ================" << std::endl;
#endif

    if (qEnvironmentVariableIsSet("OBC_NO_SCALE_FACTORS"))
    {
        //LOG("Force set QT_SCALE_FACTOR to 1.");
        //DEBUG("UI", "Original QT_SCALE_FACTOR was:", qEnvironmentVariable("QT_SCALE_FACTOR"));
        qputenv("QT_SCALE_FACTOR", "1");
    }
    else
    {
        //DEBUG("High DPI scaling is enabled.");
#ifndef OBC_QT6
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#ifdef OBC_GUI
        QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif
    }

#ifndef OBC_QT6
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif

    OBCApplication app(argc, argv);

    if (!app.Initialize())
    {
        qDebug() << "init error";
        return -1;
    }

    app.RunOBC();
    const auto reason = app.GetExitReason();



    return reason;
}
