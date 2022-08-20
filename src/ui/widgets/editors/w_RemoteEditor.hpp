#pragma once

// #include "base/Qv2rayBase.hpp"
// #include "ui/common/QvMessageBus.hpp"
// #include "ui/widgets/common/QJsonModel.hpp"
#include "ui_w_RemoteEditor.h"

#include "base/interface/DeviceInterface.hpp"

#include <QDialog>
#include <QJsonObject>

class RemoteEditor
    : public QDialog,
      private Ui::RemoteEditor
{
    Q_OBJECT

public:
    explicit RemoteEditor(const QJsonObject &rootObject, QWidget *parent = nullptr);
    explicit RemoteEditor(DeviceInterface* deviceIns, QWidget *parent = nullptr);
    ~RemoteEditor();
    QJsonObject OpenEditor();

    std::shared_ptr<ConfigureBaseWidget> configure;

private:
    QJsonObject originalConfig;
    QJsonObject resultConfig;
    // private:
    //   QvMessageBusSlotDecl;

    // private slots:
    //   void on_jsonEditor_textChanged();

    //   void on_formatJsonBtn_clicked();

    //   void on_removeCommentsBtn_clicked();

    // private:
    //   QJsonModel model;
    //   QJsonObject original;
    //   QJsonObject final;
};
