#pragma once
#include "plugin/PluginBase.hpp"

#include <QThread>
#include <QJsonObject>

namespace OBC::core::link{

	class LinkInterface : public QThread
	{
        Q_OBJECT

    public:
        LinkInterface() {}
        ~LinkInterface() {}

        //获取meta
        virtual const PluginMetadata GetMetadata() const = 0;
        //初始化插件
        virtual bool InitializePlugin(const QString &, const QJsonObject &) = 0;

        bool isConnected() const { return false; }


        //settings
        virtual void UpdateSettings(const QJsonObject &_settings) final
        {
            settings = _settings;
        }
        virtual const QJsonObject GetSettngs() const final
        {
            return settings;
        }
        //////


        virtual bool SendMessage(const QByteArray& message) = 0;

    //signals:
        void OnLinkReceivedMessage(const QByteArray& message);
        void OnLinkLogAvailable(const QString&);

    protected:
        QJsonObject settings;
    };

};
