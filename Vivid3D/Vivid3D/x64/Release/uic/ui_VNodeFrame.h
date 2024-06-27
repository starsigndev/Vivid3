/********************************************************************************
** Form generated from reading UI file 'VNodeFrame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VNODEFRAME_H
#define UI_VNODEFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VNodeFrameClass
{
public:

    void setupUi(QWidget *VNodeFrameClass)
    {
        if (VNodeFrameClass->objectName().isEmpty())
            VNodeFrameClass->setObjectName("VNodeFrameClass");
        VNodeFrameClass->resize(600, 400);

        retranslateUi(VNodeFrameClass);

        QMetaObject::connectSlotsByName(VNodeFrameClass);
    } // setupUi

    void retranslateUi(QWidget *VNodeFrameClass)
    {
        VNodeFrameClass->setWindowTitle(QCoreApplication::translate("VNodeFrameClass", "VNodeFrame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VNodeFrameClass: public Ui_VNodeFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VNODEFRAME_H
