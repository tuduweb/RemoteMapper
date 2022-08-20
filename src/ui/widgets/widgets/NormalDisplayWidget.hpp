#pragma once
#include <QWidget>
#include "ui_NormalDisplayWidget.h"

namespace OBC::ui
{
    class NormalDisplayWidget : public QWidget, public Ui::NormalDisplayWidget
    {
        Q_OBJECT

    public:
        explicit NormalDisplayWidget(QWidget *parent = nullptr);
        ~NormalDisplayWidget();

    protected:
        void paintEvent(QPaintEvent* event) override;


    private:

    };

};