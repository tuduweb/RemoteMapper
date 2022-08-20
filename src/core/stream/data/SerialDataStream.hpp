#pragma once

#include "base/OBCBaseHeader.hpp"
#include "base/interface/StreamInterface.hpp"
#include "qdebug.h"

#include "core/link/SerialThread.hpp"


//PortInfo req
#include <QSerialPortInfo>

class SerialDataStream : public StreamInterface
{
    public:
        SerialDataStream();
        ~SerialDataStream();

        int StreamInit() override;
        int StreamStart() override;
    public:
        static QStringList getStreamLists();


    protected:
        SerialThread* _serialThread;//QThread

};