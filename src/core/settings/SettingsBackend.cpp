#include "SettingsBackend.hpp"

#include "base/OBCBaseHeader.hpp"

#include "utils/OBCHelpers.hpp"

#include <QFile>
#include <QDir>
#define QSTRN(num) QString::number(num)

constexpr auto OBC_CONFIG_PATH_ENV_NAME = "OBC_CONFIG_PATH";

namespace OBC::core::settings
{

    void SaveGlobalSettings()
    {
        const auto str = JsonToString(GlobalConfig.toJson());
        StringToFile(str, OBC_CONFIG_FILE);
    }

    bool LoadConfiguration()
    {
        //export PATH=1222
        //add_definitions(-DOBC_CONFIG_PATH="${QV2RAY_DEFAULT_VCORE_PATH}")
        const auto usePath = qEnvironmentVariableIsSet("PATH");

        //const auto currentPathConfig = qApp->applicationDirPath() + "/config" OBC_CONFIG_DIR_SUFFIX;

        const auto currentPathConfig = qApp->applicationDirPath() + "/config" OBC_CONFIG_DIR_SUFFIX;
        const auto homeOBC = QDir::homePath() + "/.obc" OBC_CONFIG_DIR_SUFFIX;

        // Standard paths already handles the "_debug" suffix for us.
        const auto configOBC = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

        // Some built-in search paths for Qv2ray to find configs. (load the first one if possible).
        auto useManualConfigPath = qEnvironmentVariableIsSet(OBC_CONFIG_PATH_ENV_NAME);//const
        auto manualConfigPath = qEnvironmentVariable(OBC_CONFIG_PATH_ENV_NAME);//const

        if(!useManualConfigPath) {
            if(!QString(OBC_CONFIG_PATH).isEmpty()) {
                useManualConfigPath = true;
                manualConfigPath = OBC_CONFIG_PATH;
            }
        }

        //
        QStringList configFilePaths;
        if (useManualConfigPath)
        {
            qDebug() << QString("Using config path from env: " + manualConfigPath);
            configFilePaths << manualConfigPath;
        }
        else
        {
            configFilePaths << currentPathConfig;
            configFilePaths << configOBC;
            configFilePaths << homeOBC;
        }

        qDebug() << configFilePaths;

        QString configPath = "";
        bool hasExistingConfig = false;

        for (const auto &path : configFilePaths)
        {
            // Verify the config path, check if the config file exists and in the
            // correct JSON format. True means we check for config existence as
            // well. ---------------------------------------------|HERE|
            bool isValidConfigPath = CheckSettingsPathAvailability(path, true);

            // If we already found a valid config file. just simply load it...
            if (hasExistingConfig)
                break;

            if (isValidConfigPath)
            {
                qDebug() << QString("Path:" + path + " is valid.");
                configPath = path;
                hasExistingConfig = true;
            }
            else
            {
                qDebug() << QString("Path:" + path + "does not contain a valid config file.");
            }
        }

        if (hasExistingConfig)
        {
            // Use the config path found by the checks above
            SetConfigDirPath(configPath);
            qDebug() << ("Using " + OBC_CONFIG_DIR + " as the config path.");
        }
        else
        {
            // If there's no existing config.
            //
            // Create new config at these dirs, these are default values for each platform.
            if (useManualConfigPath)
            {
                configPath = manualConfigPath;
            }
            else
            {
#if defined(Q_OS_WIN) && !defined(OBC_NO_ASIDECONFIG)
                configPath = currentPathConfig;
#else
                configPath = configOBC;
#endif
            }
            bool hasPossibleNewLocation = QDir().mkpath(configPath) && CheckSettingsPathAvailability(configPath, false);
            // Check if the dirs are write-able
            if (!hasPossibleNewLocation)
            {
                // None of the path above can be used as a dir for storing config.
                // Even the last folder failed to pass the check.
                qDebug() << ("FATAL");
                qDebug() << (" ---> CANNOT find a proper place to store Qv2ray config files.");
                // QvMessageBoxWarn(nullptr, QObject::tr("Cannot Start Qv2ray"),
                //                  QObject::tr("Cannot find a place to store config files.") + NEWLINE +                                          //
                //                      QObject::tr("Qv2ray has searched these paths below:") + NEWLINE + NEWLINE +                                //
                //                      configFilePaths.join(NEWLINE) + NEWLINE +                                                                  //
                //                      QObject::tr("It usually means you don't have the write permission to all of those locations.") + NEWLINE + //
                //                      QObject::tr("Qv2ray will now exit."));                                                                     //
                return false;
            }

            // Found a valid config dir, with write permission, but assume no config is located in it.
            qDebug() << ("Set " + configPath + " as the config path.");
            SetConfigDirPath(configPath);


            if (QFile::exists(OBC_CONFIG_FILE))
            {
                // As we already tried to load config from every possible dir.
                //
                // This condition branch (!hasExistingConfig check) holds the fact that current config dir,
                // should NOT contain any valid file (at least in the same name)
                //
                // It usually means that QV2RAY_CONFIG_FILE here has a corrupted JSON format.
                //
                // Otherwise would have loaded this config already instead of notifying to create a new config in this folder.
                //

                qDebug() << QString("This should not occur: Qv2ray config exists but failed to load.");
                return false;
            }


            // Save initial config.
            SaveGlobalSettings();
            qDebug() << ("Created initial config file.");

        }


        if (!QDir(OBC_GENERATED_DIR).exists())
        {
            // The dir used to generate final config file, for V2Ray interaction.
            QDir().mkdir(OBC_GENERATED_DIR);
            qDebug() << QString("Created config generation dir at: " + OBC_GENERATED_DIR);
        }

        //
        // BEGIN LOAD CONFIGURATIONS
        //
        {
            // Load the config for upgrade, but do not parse it to the struct.
            auto conf = JsonFromString(StringFromFile(OBC_CONFIG_FILE));



            // Let's save the config.
            GlobalConfig.loadJson(conf);
            SaveGlobalSettings();
        }


        return true;
    }

    /**
     * @name 设置配置根目录
     */
    void SetConfigDirPath(const QString &path)
    {
        OBC::ObCoreApplication->ConfigPath = path;

        if (!path.endsWith("/"))
        {
            OBC::ObCoreApplication->ConfigPath += "/";
        }
    }

    bool CheckSettingsPathAvailability(const QString &_path, bool checkExistingConfig)
    {
        auto path = _path;

        if (!path.endsWith("/"))
            path.append("/");

        // Does not exist.
        if (!QDir(path).exists())
            return false;

        {
            // A temp file used to test file permissions in that folder.
            QFile testFile(path + ".obc_test_file" + QSTRN(QTime::currentTime().msecsSinceStartOfDay()));

            if (!testFile.open(QFile::OpenModeFlag::ReadWrite))
            {
                //LOG("Directory at: " + path + " cannot be used as a valid config file path.");
                //LOG("---> Cannot create a new file or open a file for writing.");
                return false;
            }

            testFile.write("OBC test file, feel free to remove.");
            testFile.flush();
            testFile.close();

            if (!testFile.remove())
            {
                // This is rare, as we can create a file but failed to remove it.
                //LOG("Directory at: " + path + " cannot be used as a valid config file path.");
                //LOG("---> Cannot remove a file.");
                return false;
            }
        }

        if (!checkExistingConfig)
        {
            // Just pass the test
            return true;
        }

        // Check if an existing config is found.
        QFile configFile(path + "obc.conf");

        // No such config file.
        if (!configFile.exists())
            return false;

        if (!configFile.open(QIODevice::ReadWrite))
        {
            //LOG("File: " + configFile.fileName() + " cannot be opened!");
            return false;
        }

        const auto err = VerifyJsonString(StringFromFile(configFile));
        if (!err.isEmpty())
        {
            //LOG("Json parse returns:", err);
            return false;
        }

        // If the file format is valid.
        const auto conf = JsonFromString(StringFromFile(configFile));
        //LOG("Found a config file," A(conf["config_version"].toString()) A(path));
        configFile.close();
        return true;
    }

}