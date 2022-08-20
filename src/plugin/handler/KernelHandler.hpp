#pragma once
#include <QObject>
#include "../PluginBase.hpp"


class PluginKernel : public QObject
{
        Q_OBJECT
    
    public:
        explicit PluginKernel() : QObject(){};
        virtual ~PluginKernel(){};
        virtual void SetConnectionSettings(const QMap<KernelOptionFlags, QVariant> &settings, const QJsonObject &connectionInfo) = 0;
        virtual bool StartKernel() = 0;
        virtual bool StopKernel() = 0;
        virtual QString GetKernelName() const = 0;

    signals:
        void OnKernelCrashed(const QString &);
        void OnKernelLogAvailable(const QString &);
        void OnKernelStatsAvailable(quint64 upSpeed, quint64 downSpeed);

        //images
        void OnKernelFrameReceived(const QImage &);
        void OnKernelDataReceived();

    private:
        QString __qvKernelId;
        QString kernelType;
};