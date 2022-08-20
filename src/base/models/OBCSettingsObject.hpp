#pragma once

#include "base/models/OBCIdentifier.hpp"
#include "base/models/OBCSafeType.hpp"

constexpr int OBC_CONFIG_VERSION = 1;

namespace OBC::base::config
{
    struct OBCConfigObject
    {
        int config_version;
        int logLevel = 0;

        explicit OBCConfigObject()
        {
            config_version = OBC_CONFIG_VERSION;
        }
#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
        Q_DISABLE_COPY(OBCConfigObject);
#else
        Q_DISABLE_COPY_MOVE(OBCConfigObject);
#endif
        JSONSTRUCT_COMPARE(OBCConfigObject, config_version, logLevel)
        JSONSTRUCT_REGISTER_NOCOPYMOVE(OBCConfigObject,                                                                   //
                                       A(config_version, logLevel))
    };
}