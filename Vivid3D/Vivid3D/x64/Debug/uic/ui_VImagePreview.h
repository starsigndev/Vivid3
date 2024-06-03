/********************************************************************************
** Form generated from reading UI file 'VImagePreview.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIMAGEPREVIEW_H
#define UI_VIMAGEPREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VImagePreviewClass
{
public:

    void setupUi(QWidget *VImagePreviewClass)
    {
        if (VImagePreviewClass->objectName().isEmpty())
            VImagePreviewClass->setObjectName("VImagePreviewClass");
        VImagePreviewClass->resize(600, 400);

        retranslateUi(VImagePreviewClass);

        QMetaObject::connectSlotsByName(VImagePreviewClass);
    } // setupUi

    void retranslateUi(QWidget *VImagePreviewClass)
    {
        VImagePreviewClass->setWindowTitle(QCoreApplication::translate("VImagePreviewClass", "VImagePreview", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VImagePreviewClass: public Ui_VImagePreviewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIMAGEPREVIEW_H
