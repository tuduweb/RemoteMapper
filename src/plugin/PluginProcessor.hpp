#pragma once

#include <QObject>
#include <QString>

namespace OBC::Plugin{
    class PluginKernel : public QObject{
        Q_OBJECT
    public:
        explicit PluginKernel() : QObject(){};
        virtual ~PluginKernel(){};

        virtual QString GetKernelName() const = 0;
    
    signals:
        void OnKernelLogAvailable(const QString &);
        void OnKernelFrameReceived(const QImage &);
    
    private:
        QString __qvKernelId;
    };

    class PluginKernelInterface
    {
      public:
        //return kernel // ex: // return std::make_unique<TrojanKernel>();
        virtual std::unique_ptr<PluginKernel> CreateKernel() const = 0;
        //return support protocols
        virtual QList<QString> GetKernelProtocols() const = 0;
    };

};