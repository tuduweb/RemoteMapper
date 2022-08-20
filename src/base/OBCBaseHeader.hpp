#pragma once

#include <QMap>
#include <QtCore>
#include <QString>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <optional>
#include <vector>


// Base folder suffix.
#ifdef QT_DEBUG
#define OBC_CONFIG_DIR_SUFFIX "_debug/"
#define _BOMB_ (static_cast<QObject *>(nullptr)->event(nullptr))
#else
#define _BOMB_
#define OBC_CONFIG_DIR_SUFFIX "/"
#endif

#ifdef Q_OS_WIN
#define OBC_EXECUTABLE_SUFFIX ".exe"
#else
#define OBC_EXECUTABLE_SUFFIX ""
#endif

#ifdef Q_OS_WIN
#define OBC_LIBRARY_SUFFIX ".dll"
#else
#define OBC_LIBRARY_SUFFIX ".so"
#endif

// cores
#include "base/OBCBaseApplication.hpp"

//#define OBC_CONFIG_DIR QString("/Users/bin/qt-project/OBCApp/build/config/")

#define OBC_CONFIG_DIR (ObCoreApplication->ConfigPath)
#define OBC_CONFIG_FILE (OBC_CONFIG_DIR + "obc.conf")
#define OBC_PLUGIN_SETTINGS_DIR (OBC_CONFIG_DIR + "plugin_settings/")
#define OBC_CONFIG_FILE_EXTENSION ".obc.json"
#define OBC_GENERATED_DIR (OBC_CONFIG_DIR + "generated/")
