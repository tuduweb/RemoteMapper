#include "SerialLink.hpp"

void SerialLink::run()
{

    if(_serialPort) {
        return;
    }

	QSerialPort::SerialPortError    terror;
	QString                         errorString;

    if(!_hardwareConnect(terror, errorString)) {
        
        if(_requests) {
            //
        }

    }


    while(true) {
        //
    }

}

bool SerialLink::_hardwareConnect(QSerialPort::SerialPortError& error, QString& errorString)
{
    if(_serialPort) {
        _serialPort->close();
		//暂停的同时运行主线程循环,防止程序假死
		// Wait 50 ms while continuing to run the event queue
		for (unsigned i = 0; i < 10; i++) {
			//QGC::SLEEP::usleep(5000);
			//qgcApp()->processEvents(QEventLoop::ExcludeUserInputEvents);
		}
        delete _serialPort;
		_serialPort = nullptr;
    }


	_serialPort = new QSerialPort(_serialConfig->portName(), this);

	//QObject::connect(serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this, &SerialThreadLink::linkError);

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
		qDebug() << "open failed" << _serialPort->errorString() << _serialPort->error() << _config->name() << "autconnect:" << _config->isAutoConnect();

		//RemoteLog(QString("端口打开失败:%1 错误代码:%2").arg(serialPort->errorString()).arg(serialPort->error()));

		error = _serialPort->error();
		errorString = _serialPort->errorString();
		_serialPort->close();
		delete _serialPort;
		_serialPort = nullptr;
		return false; // couldn't open serial port
	}

    _serialPort->setDataTerminalReady(true);


    //////////////////set config
	// serialPort->setBaudRate(_serialConfig->baud());
	// serialPort->setDataBits(static_cast<QSerialPort::DataBits>     (_serialConfig->dataBits()));
	// serialPort->setFlowControl(static_cast<QSerialPort::FlowControl>  (_serialConfig->flowControl()));
	// serialPort->setStopBits(static_cast<QSerialPort::StopBits>     (_serialConfig->stopBits()));
	// serialPort->setParity(static_cast<QSerialPort::Parity>       (_serialConfig->parity()));


    //绑定发送槽
	//connect(this, &SerialThreadLink::SendBytes, this, &SerialThreadLink::_writeBytes);

    //改变当前状态

    return true;
}

/**
 * 处理错误
 */
void SerialLink::linkError(QSerialPort::SerialPortError error)
{
	switch (error) {
	case QSerialPort::NoError:
		break;
	case QSerialPort::ResourceError:
		// This indicates the hardware was pulled from the computer. For example usb cable unplugged.
		//_connectionRemoved();
		qDebug() << error << _serialPort->errorString();
		break;
	default:
		qDebug() << error << _serialPort->errorString();
		// You can use the following qDebug output as needed during development. Make sure to comment it back out
		// when you are done. The reason for this is that this signal is very noisy. For example if you try to
		// connect to a PixHawk before it is ready to accept the connection it will output a continuous stream
		// of errors until the Pixhawk responds.
		//qCDebug(SerialLinkLog) << "SerialLink::linkError" << error;
		break;
	}
	//错误基本没打印出来 有个锤子用阿..
}

void SerialLink::_writeBytes(const QByteArray data) {

    // if (this->isRunning())
	// 	Request(data);
	// else {
	// 	// Error occurred
	// 	qWarning() << "Serial port not writeable";
	// 	//_emitLinkError(tr("Could not send data - link %1 is disconnected!").arg(_config->name()));
	// }
}
