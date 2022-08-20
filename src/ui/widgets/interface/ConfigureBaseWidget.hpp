#pragma once
#include <QWidget>

#include <QJsonObject>

class ConfigureBaseWidget : public QWidget
{
    Q_OBJECT
public:
    ConfigureBaseWidget(QWidget* parent) : QWidget(parent) {};
    virtual void ReloadUI() = 0;
    virtual QJsonObject GenerateConfigObject(){ return {}; };
};