#include "VTrackTimeLine.h"
#include "qpainter.h"
#include "qevent.h"

VTrackTimeLine::VTrackTimeLine(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void VTrackTimeLine::paintEvent(QPaintEvent* event)
{
	//QPainter painter(this);



	QPainter painter(this);

    QColor c1(0, 60, 60);
    QColor c2(0, 90, 90);

    QLinearGradient gradient(0, 0, 0, height() - 1);
    gradient.setColorAt(0, c2);    // Start color (top)
    //gradient.setColorAt(0.5, Qt::darkGray); // Middle color
    gradient.setColorAt(1, c1);   // End color (bottom)


    // Set the brush to use the gradient
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    // Draw a rectangle filled with the gradient
    painter.drawRect(rect());

    //


    QColor c3(0, 20, 20);
    QColor c4(0, 40, 40);

    QLinearGradient gradient2(0, 0, 0, height() - 1);
    gradient2.setColorAt(0, c4);    // Start color (top)
    //gradient.setColorAt(0.5, Qt::darkGray); // Middle color
    gradient2.setColorAt(1, c3);   // End color (bottom)


    // Set the brush to use the gradient
    painter.setBrush(gradient2);
    painter.setPen(Qt::NoPen);
    // Draw a rectangle filled with the gradient
    painter.drawRect(QRect(2,2,size().width()-4,size().height()-4));

}


VTrackTimeLine::~VTrackTimeLine()
{}
