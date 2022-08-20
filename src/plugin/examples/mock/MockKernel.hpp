#pragma once

#include "PluginProcessor.hpp"
#include <QDebug>

#include <QImage>
#include <QPixmap>
#include <QPainter>

class MockKernel : public OBC::Plugin::PluginKernel
{
    public:
        explicit MockKernel() {
            startTimer(50);
        };
        ~MockKernel() {};
        QString GetKernelName() const override
        {
            return "Mock";
        }

    protected:
        void timerEvent(QTimerEvent* event) override {
            static QImage image(100, 100, QImage::Format_BGR888);
            qDebug() << "hello timer";
        
            makeRandomImage(image);

            emit OnKernelFrameReceived(image);
        }

        void makeRandomImage(QImage& image) {
            static int color = 0;
            QPainter p;
            image.fill(QColor(color, color, color));

            p.begin(&image);
            color++;
            color = color % 256;
            qDebug() << color;

            p.drawLine(0, 0, 100, 100);
            
            QFont font("宋体",18,75);
            p.setFont(font);
            QString title(QString::number(color));
            int widthOfTitle = p.fontMetrics().width(title);//字符串显示的像素大小
            p.drawText(image.width()/2-widthOfTitle/2, 50,title);

            p.end();
        }
};

//rename to MockKernelInterface
class MockKernelInterface : public OBC::Plugin::PluginKernelInterface
{
  public:
    virtual std::unique_ptr<OBC::Plugin::PluginKernel> CreateKernel() const override
    {
        qDebug() << "Create Kernel";
        return std::make_unique<MockKernel>();
    }
    virtual QList<QString> GetKernelProtocols() const override
    {
        return { "mocktest" };
    }
};