#include "FrameDisplayWidget.hpp"

#include <QPainter>


void FrameDisplayWidget::paintEvent(QPaintEvent* event) {
    QPainter pp(this);
    QRect tempRect(0, 0, this->height() * 1920 / 1080, this->height());

    QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
    pen.setColor(QColor(255,0,0,255)); 
    
    QBrush brush;   //画刷。填充几何图形的调色板，由颜色和填充风格组成
    brush.setColor(QColor(0,255,0,120));
    brush.setStyle(Qt::SolidPattern);
    pp.setBrush(brush);

    qDebug() << "renderRect" << renderRect;
    pp.drawRect(renderRect);

    pp.drawImage(tempRect, frame);

    //fps count
}

void FrameDisplayWidget::resizeEvent(QResizeEvent* event) {
    ResizeUI(event->oldSize(), event->size());
}

void FrameDisplayWidget::ResizeUI() {
    ResizeUI(this->size(), this->size());
}

void FrameDisplayWidget::ResizeUI(const QSize& oldSize, const QSize& newSize) {
	//计算比例尺
	scale = newSize.width() * 1.0 / newSize.height();
	qDebug() << newSize;
	//窗口更宽一点,以高度为基尺度
	if (scale > sourceScale)
	{
		renderSize = QSize(newSize.height() * sourceScale, newSize.height());
	}
	else {
		renderSize = QSize(newSize.width(), newSize.width() / sourceScale);
	}

	int al = (newSize.width() - renderSize.width()) / 2;
	int at = (newSize.height() - renderSize.height()) / 2;
	int br = renderSize.width();
	int bb = renderSize.height();

	renderRect = QRect(al, at, br, bb);

	double coefficient = newSize.width() * 1.0f / oldSize.width();
}