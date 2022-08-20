#pragma once

#include "base/models/OBCSettingsObject.hpp"

#include <QCoreApplication>
#include <QObject>
#include "qstring.h"

namespace OBC
{

    enum MessageOpt
    {
        OK,
        Cancel,
        Yes,
        No,
        Ignore
    };

    enum OBCExitReason
    {
        EXIT_NORMAL = 0,
        EXIT_NEW_VERSION_TRIGGER = EXIT_NORMAL,
        EXIT_SECONDARY_INSTANCE = EXIT_NORMAL,
        EXIT_INITIALIZATION_FAILED = -1,
        EXIT_PRECONDITION_FAILED = -2,
    };

    class OBCApplicationInterface
    {
        public:
            OBC::base::config::OBCConfigObject *ConfigObject;
            QString ConfigPath;

        public:
            explicit OBCApplicationInterface();
            ~OBCApplicationInterface();

        public:
            virtual QStringList GetAssetsPaths(const QString &dirName) const final;

    };

    inline OBCApplicationInterface *ObCoreApplication = nullptr;
};

using namespace OBC;

#define GlobalConfig (*OBC::ObCoreApplication->ConfigObject)
