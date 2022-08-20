#pragma once

#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QMutex>
#include <QVector>

namespace OBC::core::link
{
    class SerialLink : public QThread
    {
        SerialLink() : _serialPort(nullptr) {}
        ~SerialLink() {}

    public slots:
        void SendMessage(const QByteArray& message) { qDebug() << message; }
        //void OnLinkLogAvailable(const QString&) {}

    protected:
        void run() override;

        
    private:
        bool _hardwareConnect(QSerialPort::SerialPortError& error, QString& errorString);
        void _writeBytes(const QByteArray& data);


    private slots:
        void linkError(QSerialPort::SerialPortError error);

    private:
        QSerialPort* _serialPort;
		QMutex _mutex;
        QVector<QByteArray> _requests;

    };
};

using namespace OBC::core::link;