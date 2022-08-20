#include "ConfigHandler.hpp"

#include "base/OBCBaseHeader.hpp"

#include "utils/OBCHelpers.hpp"

#include <QDebug>

namespace OBC::core::handler{

    ConfigHandler::ConfigHandler(QObject *parent) : QObject(parent)
    {
        QString configPath = OBC_CONFIG_DIR;

        //DEBUG("ConnectionHandler Constructor.");
        const auto bundleJson = JsonFromString(StringFromFile(configPath + "bundles.json"));
        const auto commJson = JsonFromString(StringFromFile(configPath + "links.json"));

        qDebug() << JsonToString(bundleJson);

        qDebug() << bundleJson.count();

        //qDebug() << JsonToString(commJson);


        for (const auto &commId : commJson.keys())
        {
            auto commObject = CommObject::fromJson(commJson.value(commId).toObject());
            //qDebug() << JsonToString(commObject.toJson());

            if(commObject.displayName.isEmpty())
            {
                commObject.displayName = tr("comm%1").arg(GenerateRandomString(5));
            }

            comms.insert(CommId{ commId }, commObject);
        }

        for(const auto &commId : comms.keys()) {
            auto comm = comms.value(commId);
            qDebug() << commId.toString() << comm.displayName << comm.type;
        }

        qDebug() << "hello instance config handler";


    }

};