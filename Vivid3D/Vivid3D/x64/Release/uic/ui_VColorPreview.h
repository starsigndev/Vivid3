/********************************************************************************
** Form generated from reading UI file 'VColorPreview.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCOLORPREVIEW_H
#define UI_VCOLORPREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VColorPreviewClass
{
public:

    void setupUi(QWidget *VColorPreviewClass)
    {
        if (VColorPreviewClass->objectName().isEmpty())
            VColorPreviewClass->setObjectName("VColorPreviewClass");
        VColorPreviewClass->resize(600, 400);

        retranslateUi(VColorPreviewClass);

        QMetaObject::connectSlotsByName(VColorPreviewClass);
    } // setupUi

    void retranslateUi(QWidget *VColorPreviewClass)
    {
        VColorPreviewClass->setWindowTitle(QCoreApplication::translate("VColorPreviewClass", "VColorPreview", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VColorPreviewClass: public Ui_VColorPreviewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCOLORPREVIEW_H
