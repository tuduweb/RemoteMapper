#include "SerialThread.hpp"
#include <qDebug>
#include <QEventLoop>
#include <qcoreapplication.h>

#include <QSerialPortInfo>
#include <iostream>

SerialThread::SerialThread(QObject *parent) : QThread(parent), _serialPort(nullptr)
{

    std::cout << "hello Serial Stream" << std::endl;

    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

    for(const auto& item : infos) {
        // //MACOS
        // if(item.portName().split(".").size() > 0 && item.portName().split(".")[0] != "cu")
        //     continue;
        std::cout << "************************************" << std::endl;
        qDebug() << item.portName();
        qDebug() << item.manufacturer();
        qDebug() << item.serialNumber();
        qDebug() << item.manufacturer();
        qDebug() << item.description();
        qDebug() << item.systemLocation();
    }

}

//The run() member function is executed in a different thread
void SerialThread::run()
{

    if(_serialPort) {
        return;
    }

	QSerialPort::SerialPortError    terror;
	QString                         errorString;

    if(!_hardwareConnect(terror, errorString)) {
    
    }

    connect(_serialPort, &QSerialPort::readyRead, this, [=](){
        //qDebug() << "msg received";
        QByteArray data;
        data = _serialPort->readAll(); //读取串口数据
        //qDebug() << data;
    });

    int cnt = 0;
    while(1) {
        //
        _serialPort->write("hello world");
        for (unsigned i = 0; i < 100; i++) {
            QThread::msleep(5);
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        qDebug() << "exec" << cnt++;
    }

    qDebug() << "exec exit";

}

bool SerialThread::_hardwareConnect(QSerialPort::SerialPortError& error, QString& errorString)
{
    if(_serialPort) {
        _serialPort->close();

        delete _serialPort;
		_serialPort = nullptr;
    }

    QString portName = "cu.usbmodem0001A00000011";

    //parent's thread is QThread(0x107c041e0), current thread is SerialThread(0x111995920)
    //this in Main Thread(not QThread)
    _serialPort = new QSerialPort(portName); //_serialConfig->portName()

    // Try to open the port three times
	for (int openRetries = 0; openRetries < 3; openRetries++) {
		if (!_serialPort->open(QIODevice::ReadWrite)) {
			//qCDebug(SerialLinkLog) << "Port open failed, retrying";
			RemoteLog(tr("Port open failed, retrying %1").arg(openRetries));
			// Wait 250 ms while continuing to run the event loop
			for (unsigned i = 0; i < 50; i++) {
				QThread::msleep(5);
				qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
			}
			qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
		else {
			break;
		}
	}

    if (!_serialPort->isOpen()) {
		qDebug() << "open failed" << _serialPort->errorString() << _serialPort->error();// << _config->name() << "autconnect:" << _config->isAutoConnect();

		error = _serialPort->error();
		errorString = _serialPort->errorString();
		_serialPort->close();
		delete _serialPort;
		_serialPort = nullptr;
		return false; // couldn't open serial port
	}

    _serialPort->setDataTerminalReady(true);

    qDebug() << "device opened" << _serialPort->portName();

    return true;
}