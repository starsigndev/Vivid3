#include "VContentView.h"
#include <QPainter>
#include <QDir>
#include <qevent.h>
#include <QDirIterator>
VContentView::VContentView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    setMouseTracking(true);
}

VContentView::~VContentView()
{}


void VContentView::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    // Create a QPainter object
    QPainter painter(this);
    QColor bg(40, 40, 40);
    // Set background color
    painter.fillRect(rect(),bg);

    QImage folder("edit/icons/folder.png");
    QImage file("edit/icons/file.png");

    for (auto item : m_All) {

        QRectF rect(item->m_DrawX, item->m_DrawY, 64, 64);

        if (item == m_OverItem) {

            QColor bg(70, 70, 70);
            // Set background color
            QRectF rect2(item->m_DrawX-8,item->m_DrawY-8,64+16,64+16);

            painter.fillRect(rect2, bg);
           // painter.drawRect(rect);


        }

        if (item->m_Folder) {
            painter.drawImage(rect, folder);
        }
        else {
            painter.drawImage(rect, file);
        }

        painter.drawText(item->m_DrawX, item->m_DrawY + 70, 120, 30, 0, item->m_Name.c_str());

    };
    
  //  RenderItem(m_Root, 25, 20);

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

//


void VContentView::mousePressEvent(QMouseEvent* event)
{
    /*
    if (event->button() == Qt::LeftButton)
    {
        if (m_OverItem != nullptr)
        {
            if (m_OverItem->m_Items.size() > 0) {
                m_OverItem->m_Open = m_OverItem->m_Open ? false : true;
                update();
            }
        }
        // Handle left mouse button press

    }
    */
}

void VContentView::mouseMoveEvent(QMouseEvent* event)
{
    auto pos = event->position();
    m_OverItem = nullptr;

    for (auto item : m_All) {
    
        if (pos.x() > item->m_DrawX-16 && pos.y() > item->m_DrawY-8) {
            if (pos.x() < item->m_DrawX + 64+16 && pos.y() < item->m_DrawY + 64+16)
            {
                m_OverItem = item;
                update();
                return;
            }
        }

    }
    /*
    m_OverItem = nullptr;
    auto pos = event->position();
    printf("PX:%d PY:%d \n", (int)pos.x(), (int)pos.y());
    int y = CheckItem(m_Root, 25, 5, (int)pos.x(), (int)pos.y());
    update();
    setMinimumSize(width(), y + 40);
    update();
    */
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

QString extractFileName(const QString& filePath)
{
    // Find the last occurrence of the path separator '/'
    int lastIndex = filePath.lastIndexOf('/');
    if (lastIndex == -1) {
        // If no separator found, return the original file path
        return filePath;
    }

    // Extract the file name (including extension) from the file path
    return filePath.mid(lastIndex + 1);
}

void VContentView::Browse(std::string path) {

    QDir directory(path.c_str());

    // Check if the directory exists
    if (!directory.exists()) {
        qDebug() << "Directory does not exist.";
        return;
    }

    // Create a QDirIterator to iterate through the directory
    QFileInfoList fileInfoList = directory.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

    // Iterate through the entries
    for (const QFileInfo& fileInfo : fileInfoList) {
        if (fileInfo.isFile()) {
            //qDebug() << "File:" << fileInfo.absoluteFilePath();
            ContentItem* item = new ContentItem;
            item->m_Name = extractFileName(fileInfo.absoluteFilePath()).toStdString();
            item->m_FullPath = fileInfo.absoluteFilePath().toStdString();
            item->m_Folder = false;
            m_Files.push_back(item);
        }
        else if (fileInfo.isDir()) {
            qDebug() << "Directory:" << fileInfo.absoluteFilePath();
            ContentItem* item = new ContentItem;
            item->m_Name = extractFileName(fileInfo.absoluteFilePath()).toStdString();
            item->m_FullPath = fileInfo.absoluteFilePath().toStdString();
            item->m_Folder = true;
            m_Folders.push_back(item);
        }
    }

    UpdateView();

}

void VContentView::UpdateView() {

    auto p = (QWidget*)this->parent();
    int max_w = p->width();

    int dx, dy;

    m_All.clear();

    dx = 15;
    dy = 15;

    for (auto folder : m_Folders) {

        folder->m_DrawX = dx;
        folder->m_DrawY = dy;
        dx = dx + 128;
        if (dx >= max_w-64)
        {
            dx = 5;
            dy = dy + 128;
        }
        m_All.push_back(folder);


    }

    for (auto file : m_Files) {

        file->m_DrawX = dx;
        file->m_DrawY = dy;

        dx = dx + 128;
        if (dx >= max_w-64)
        {
            dx = 5;
            dy = dy + 128;
        }
        m_All.push_back(file);
    }

   // setMaximumSize(max_w, dy);
    setMinimumHeight(dy+64);
    int b = 5;

}

void VContentView::resizeEvent(QResizeEvent* event)
{

    UpdateView();
    update();
    /// Call the base class implementation (optional, but good practice)
    /*
    QWidget::resizeEvent(event);

    // Handle the resize event
    QSize newSize = event->size();
    QSize oldSize = event->oldSize();
    //  if (pSelf->m_pSwapChain != nullptr)
    m_pSwapChain->Resize(static_cast<Uint32>(newSize.width()), static_cast<Uint32>(newSize.height()));
    // For demonstration, print the new size to the debug output
    qDebug() << "Widget resized from" << oldSize << "to" << newSize;
    Engine::m_FrameWidth = newSize.width();
    Engine::m_FrameHeight = newSize.height();
    */
}