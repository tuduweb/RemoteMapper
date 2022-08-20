#pragma once
#include "../../GUIPluginInterface.hpp"

using namespace OBC::Plugin;

namespace OBC::Plugin{

    class MockPluginSettingsWidget : public ObPluginSettingsWidget
    {
        public:
        explicit MockPluginSettingsWidget(QWidget *parent = nullptr);
        void SetSettings(const QJsonObject &) override{};
        QJsonObject GetSettings() override
        {
            return {};
        };
    };

};



class MockGuiInterface : public PluginGUIInterface
{
    virtual QList<PluginGuiComponentType> GetComponents() const override
    {
        return { GUI_COMPONENT_OUTBOUND_EDITOR };
    }

    virtual std::unique_ptr<ObPluginSettingsWidget> createSettingsWidgets() const override
    {
        qDebug() << "step : " << "createSettingsWidgets";
        return std::make_unique<MockPluginSettingsWidget>();

        //return nullptr;
        //return std::make_shared<MockPluginSettingsWidget>();
    }

};