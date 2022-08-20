#include "NormalDisplayWidget.hpp"

#include <QPainter>

namespace OBC::ui
{
    NormalDisplayWidget::NormalDisplayWidget(QWidget *parent) :
        QWidget(parent)
    {
        setupUi(this);

        update();
    }

    NormalDisplayWidget::~NormalDisplayWidget()
    {

    }

    void NormalDisplayWidget::paintEvent(QPaintEvent* event)
    {
	    QPainter pp(this);


        pp.setPen(QPen(QColor("red")));
        pp.drawText(QPoint(30, 30), "Hello world");

    }

}
