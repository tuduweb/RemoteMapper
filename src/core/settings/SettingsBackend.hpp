#pragma once

#include <QString>

namespace OBC::core::settings
{
    void SaveGlobalSettings();
    bool LoadConfiguration();
    void SetConfigDirPath(const QString &path);
    bool CheckSettingsPathAvailability(const QString &_path, bool checkExistingConfig);
}

using namespace OBC::core::settings;