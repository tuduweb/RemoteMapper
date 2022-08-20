#pragma once

#include <QObject>
#include <QJsonObject>
#include <QString>

#include "StreamInterface.hpp"

#include "ui/widgets/interface/ControlBaseWidget.hpp"
#include "ui/widgets/interface/ConfigureBaseWidget.hpp"

class DeviceInterface : public QObject
{
public:
    enum DeviceProperty{
        HAS_VIDEOSTREAM = 1u,
        HAS_DATASTREAM = (1u << 1)
    };

public:
    //property s
    const QString DeviceId() const { return _deviceId; };
    const QString DeviceName() const { return _deviceName; }

public:
    DeviceInterface(QObject *parent = nullptr) : QObject(parent) {};
    ~DeviceInterface() {};
    virtual int DeviceInit() = 0;
    virtual int DeviceDeinit() = 0;

    //check current ins avaliable
    virtual int checkAvaliable() { return 0; };

    QWidget* configureWidget() const { return _configureWidget; }
    QWidget* controlWidget() const { return _controlWidget; };

public:
    virtual std::unique_ptr<ConfigureBaseWidget> GetConfigureWidget() const final
    {
        return createConfigureWidget();
    }
protected:
    virtual std::unique_ptr<ConfigureBaseWidget> createConfigureWidget() const = 0;

signals:
    void DataArrived(const QJsonObject& data);
    void FrameArrived(const QJsonObject& frame);
    void SendEvent(const QJsonObject& event);

protected:
    QString _deviceId;// must unique in system
    QString _deviceName;

    std::shared_ptr<StreamInterface> dataStreamer;
    std::shared_ptr<StreamInterface> videoStreamer;

    QVector<StreamInterface*> _streamInstances;

    ConfigureBaseWidget* _configureWidget;
    ControlBaseWidget* _controlWidget;
};