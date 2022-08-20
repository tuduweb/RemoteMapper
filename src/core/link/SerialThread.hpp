#pragma once
#include <QObject>
#include <QThread>

#include <QByteArray>
#include <QSerialPort>

#define RemoteLog(log) qDebug() << log

class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
protected:
    void run() override;

    bool _hardwareConnect(QSerialPort::SerialPortError& error, QString& errorString);

signals:
    void NewDataArrived(const QByteArray& data);

protected:
    QSerialPort* _serialPort;

};