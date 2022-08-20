#include "SerialDataStream.hpp"

SerialDataStream::SerialDataStream()
{
    _serialThread = new SerialThread(this);
}

SerialDataStream::~SerialDataStream()
{
    //
}

int SerialDataStream::StreamInit()
{
    return 0;
}

int SerialDataStream::StreamStart()
{
    _serialThread->start();
    return 0;
}

QStringList SerialDataStream::getStreamLists()
{

    QStringList streamList{};

    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

    for(const auto& item : infos) {
        //MACOS
        if(item.portName().split(".").size() > 0 && item.portName().split(".")[0] != "cu")
            continue;

        qDebug() << item.portName();
        qDebug() << item.manufacturer();
        qDebug() << item.serialNumber();
        qDebug() << item.manufacturer();
        qDebug() << item.description();
        qDebug() << item.systemLocation();

        streamList.append(item.portName());
    }

    return streamList;
}
