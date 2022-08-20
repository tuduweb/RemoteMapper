#pragma once

#include <QString>
#include <QList>
#include <QVariant>


namespace OBC::plugin
{

    enum GlobalPluginOptions
    {
        OPTION_SET_TLS_ALLOW_INSECURE = 0,
        OPTION_SET_TLS_SESSION_RESUMPTION = 1,
        OPTION_SET_TLS_DISABLE_SYSTEM_CERTS = 2
    };

    using Qv2rayPluginOption = QMap<GlobalPluginOptions, QVariant>;

    enum PluginUpdateType
    {
        UPDATE_NONE = 0,
        UPDATE_GITHUB_RELEASE = 1,
        UPDATE_URL = 2
    };

    enum PluginGuiComponentType
    {
        GUI_COMPONENT_SETTINGS = 0,
        GUI_COMPONENT_OUTBOUND_EDITOR = 1,
        GUI_COMPONENT_INBOUND_EDITOR = 2,
        GUI_COMPONENT_MAINWINDOW_WIDGET = 3
    };

    enum PluginComponentType
    {
        COMPONENT_EVENT_HANDLER = 0,
        COMPONENT_GUI = 1,
        COMPONENT_KERNEL = 2,
        COMPONENT_OUTBOUND_HANDLER = 3,
        COMPONENT_SUBSCRIPTION_ADAPTER = 4,
    };

    enum OutboundInfoFlags
    {
        INFO_DISPLAYNAME = 0,
        INFO_PROTOCOL = 1,
        INFO_SERVER = 2,
        INFO_PORT = 3,
        INFO_SNI = 4
    };

    enum KernelOptionFlags
    {
        KERNEL_HTTP_ENABLED,
        KERNEL_HTTP_PORT,
        KERNEL_SOCKS_ENABLED,
        KERNEL_SOCKS_PORT,
        KERNEL_SOCKS_UDP_ENABLED,
        KERNEL_SOCKS_LOCAL_ADDRESS,
        KERNEL_LISTEN_ADDRESS
    };

    struct PluginMetadata
    {
        QString Name;
        QString Author;
        QString InternalName;
        QString Description;
        QString VersionString;
        QString UpdateLocation;
        PluginUpdateType UpdateType;
        QList<PluginComponentType> Components;
        PluginMetadata(const QString &name,                                   //
                         const QString &author,                                 //
                         const QString &internalName,                           //
                         const QString &description,                            //
                         const QString &versionString,                          //
                         const QString &updateUrl,                              //
                         const QList<PluginComponentType> &supportedComponents, //
                         const PluginUpdateType updateType)                     //
            : Name(name),                                                       //
              Author(author),                                                   //
              InternalName(internalName),                                       //
              Description(description),                                         //
              VersionString(versionString),                                     //
              UpdateLocation(updateUrl),                                        //
              UpdateType(updateType),                                           //
              Components(supportedComponents){};                                //
        PluginMetadata(){};
    };
};

using namespace OBC::plugin;