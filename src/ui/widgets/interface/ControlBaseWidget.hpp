#pragma once
#include <QWidget>

class ControlBaseWidget : public QWidget
{
    Q_OBJECT
public:
    ControlBaseWidget(QWidget* parent) : QWidget(parent) {};

signals:
	void SendEvent(const QJsonObject& event);

public:
	virtual void HandleEvent(const QJsonObject& event) {};

};