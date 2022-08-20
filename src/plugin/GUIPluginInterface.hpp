#pragma once
#include "PluginBase.hpp"
#include <QWidget>
#include <QJsonObject>
#include <QDebug>

namespace OBC::Plugin
{
    class ObPluginSettingsWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit ObPluginSettingsWidget(QWidget *parent) : QWidget(parent){};
        virtual ~ObPluginSettingsWidget(){ qDebug() << "settings widget destory;"; };
        virtual void SetSettings(const QJsonObject &) = 0;
        virtual QJsonObject GetSettings() = 0;
    };

    class PluginGUIInterface
    {
        public:
            explicit PluginGUIInterface(){};
            virtual ~PluginGUIInterface(){};

            virtual QList<PluginGuiComponentType> GetComponents() const = 0;
            virtual std::unique_ptr<ObPluginSettingsWidget> GetSettingsWidget() const final
            {
                return createSettingsWidgets();
            }
        protected:
            virtual std::unique_ptr<ObPluginSettingsWidget> createSettingsWidgets() const = 0;

    };
};