#include "MockGUI.hpp"

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

namespace OBC::Plugin{

    MockPluginSettingsWidget::MockPluginSettingsWidget(QWidget *parent) : OBC::Plugin::ObPluginSettingsWidget(parent)
    {
        qDebug() << "hello plugin gui : mock plugin";
        QLabel* label = new QLabel("hello world!", this);
        QLabel* label2 = new QLabel("Plugin Test", this);
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        layout->addWidget(label);
        layout->addWidget(label2);
    }
};