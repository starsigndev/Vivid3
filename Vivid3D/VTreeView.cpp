#include "VTreeView.h"
#include <QPainter>
#include "Node.h"
#include "Editor.h"

VTreeView::VTreeView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    m_Root = new TreeItem;
    m_Root->m_Text = "Scene";
    auto i1 = m_Root->AddItem("Test 1");
    auto i2 = m_Root->AddItem("Test 2");
    i2->AddItem("Other 1");
    i2->AddItem("Other 2");
    m_Root->AddItem("Test 3");
    setMouseTracking(true);
    //m_OverItem = i1;
    for (int i = 0; i < 50; i++) {
        m_Root->AddItem("YEAH!");
    }
    m_Root->AddItem("Done");

   

}

int VTreeView::CheckItem(TreeItem* item, int x, int y, int px, int py) {

    if (px >= 0 && px < width())
    {
        if (py > y && py < y + 20)
        {
            m_OverItem = item;
            return y;
        }
    }


    if (item->m_Open) {
        for (auto it : item->m_Items) {

            y = CheckItem(it, x + 20, y + 20, px, py);


        }

    }

    return y;
}


void VTreeView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_OverItem != nullptr)
        {
            if (m_OverItem->m_Items.size() > 0) {
                m_OverItem->m_Open = m_OverItem->m_Open ? false : true;
                update();
            }
            else {
                auto node = (Node*)m_OverItem->m_Data;
                if (node != nullptr) {
                    Editor::m_CurrentNode = (NodeEntity*)node;
                    
                }
                m_ActiveItem = m_OverItem;
            }
        }
        // Handle left mouse button press

    }
}

void VTreeView::mouseMoveEvent(QMouseEvent* event)
{

    m_OverItem = nullptr;
    auto pos = event->position();
    printf("PX:%d PY:%d \n", (int)pos.x(), (int)pos.y());
    int y = CheckItem(m_Root,25,5, (int)pos.x(), (int)pos.y());
    update();
    setMinimumSize(width(), y+40);
    update();

 //   QPoint delta = event->pos() - m_MouseLast;
//    m_MouseLast = event->pos();
    // Handle mouse move event
    // Use event->pos() or event->globalPos() to get the cursor position
    //if (m_CamRotate) {
       // m_ViewYaw += delta.x() * 0.2f;
       // m_ViewPitch += delta.y() * 0.2f;


        //  update();
    //

    // Call base class implementation if necessary
    //QWidget::mouseMoveEvent(event);
}


void VTreeView::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    // Create a QPainter object
    QPainter painter(this);
    QColor bg(40, 40, 40);
    // Set background color
    painter.fillRect(rect(), bg);

    RenderItem(m_Root, 25, 20);

    /*
    // Set pen and brush
    QPen pen(Qt::black);
    painter.setPen(pen);
    QBrush brush(Qt::blue);
    painter.setBrush(brush);

    // Draw shapes
    painter.drawRect(50, 50, 100, 100);       // Draw a rectangle
    painter.drawEllipse(200, 50, 100, 100);   // Draw an ellipse
    painter.drawLine(50, 200, 300, 200);      // Draw a line

    // Draw text
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(50, 250, "Hello, Qt!");
    */
}

int VTreeView::RenderItem(TreeItem* item, int x, int y) {

    QPainter painter(this);

    if (item == m_OverItem || item == m_ActiveItem) {

        QBrush brush(Qt::gray);
        painter.setBrush(brush);

        // Set the pen (optional, for the outline of the rectangle)
        QPen pen(Qt::white);
        painter.setPen(pen);

        // Draw the filled rectangle
        QRect rect(0, y - 15, size().width()-2, 20); // x, y, width, height
        painter.drawRect(rect);

        if (item->m_Open) {

        }


    }

    if (item->m_Items.size() > 0) {
        // Set the brush for filling the rectangle
        QBrush brush(Qt::black);
        painter.setBrush(brush);

        // Set the pen (optional, for the outline of the rectangle)
        QPen pen(Qt::white);
        painter.setPen(pen);

        // Draw the filled rectangle
        QRect rect(x - 16, y - 10, 10, 10); // x, y, width, height
        painter.drawRect(rect);

        if (item->m_Open) {
            QBrush brush1(Qt::white);
            painter.setBrush(brush1);

            // Set the pen (optional, for the outline of the rectangle)
            QPen pen1(Qt::white);
            painter.setPen(pen1);

            // Draw the filled rectangle
            QRect rect1(x - 14, y - 8, 6, 6); // x, y, width, height
            painter.drawRect(rect1);
        }
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10));
    painter.drawText( x, y, item->m_Text.c_str());

    if (item->m_Open) {

        for (auto it : item->m_Items) {

            y = RenderItem(it, x + 20, y + 20);


        }

    }

    return y;

}

VTreeView::~VTreeView()
{}
