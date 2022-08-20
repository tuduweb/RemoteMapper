#pragma once

#include "base/models/OBCSafeType.hpp"
#include "base/models/OBCIdentifier.hpp"

#include <QObject>

namespace OBC::core::handler
{
    class ConfigHandler : public QObject
    {
        Q_OBJECT

    public:
        explicit ConfigHandler(QObject *parent = nullptr);
        ~ConfigHandler() {};
    
        QHash<BundleId, BundleObject> bundles;
        QHash<CommId, CommObject> comms;
    
    
    };
};

using namespace OBC::core::handler;