#pragma once

#include <QObject>
#include <QJsonObject>

#include "base/OBCBaseHeader.hpp"
#include "utils/OBCHelpers.hpp"

class BundleHandler : public QObject
{
    Q_OBJECT
    
public:
    BundleHandler() {
        //temp to load global configs
        const auto bundleJson = JsonFromString(StringFromFile(OBC_CONFIG_DIR + "remotes.json"));

        for (const auto &bundleId : bundleJson.keys()) {
            _bundleLists.push_back(bundleJson.value(bundleId).toObject().value("displayName").toString());
        }

    };

    void loadConfig(const QJsonObject &config) {
        //
    }

public:
    QStringList GetBundleLists()
    {
        return _bundleLists;
    }

protected:
    QStringList _bundleLists;

};

inline BundleHandler *BundleManager = nullptr;
