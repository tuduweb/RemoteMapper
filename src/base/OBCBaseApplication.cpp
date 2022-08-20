#include "OBCBaseApplication.hpp"

#include "core/settings/SettingsBackend.hpp"

#include <QDir>
#include <QStandardPaths>

inline QString makeAbsDir(const QString &p)
{
    return QDir(p).absolutePath();
}

OBCApplicationInterface::OBCApplicationInterface()
{
    ConfigObject = new OBC::base::config::OBCConfigObject; // global config object
    ObCoreApplication = this;
}

OBCApplicationInterface::~OBCApplicationInterface()
{
    ObCoreApplication = nullptr;
}

QStringList OBCApplicationInterface::GetAssetsPaths(const QString &dirName) const
{
    // Configuration Path
    QStringList list;

    if (qEnvironmentVariableIsSet("OBC_RESOURCES_PATH"))
        list << makeAbsDir(qEnvironmentVariable("OBC_RESOURCES_PATH") + "/" + dirName);

    // Default behavior on Windows
    list << makeAbsDir(QCoreApplication::applicationDirPath() + "/" + dirName);
    list << makeAbsDir("QV2RAY_CONFIG_DIR" + dirName);
    list << ":/" + dirName;

    list << QStandardPaths::locateAll(QStandardPaths::AppDataLocation, dirName, QStandardPaths::LocateDirectory);
    list << QStandardPaths::locateAll(QStandardPaths::AppConfigLocation, dirName, QStandardPaths::LocateDirectory);

#ifdef Q_OS_UNIX
#endif

#ifdef Q_OS_MAC
#endif

    list.removeDuplicates();

    return list;
}