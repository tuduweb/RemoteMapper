#pragma once

#include <QWidget>



class DisplayInterface : public QWidget
{
    Q_OBJECT

public:
    DisplayInterface() {};
    ~DisplayInterface() {};


signals:
    void SendEvent(const QJsonObject& obj);
public://slots
    virtual void HandleEvent(const QJsonObject& obj) {};
    virtual void OnReceivedFrame(const QImage& frame) {};
};