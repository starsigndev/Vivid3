/********************************************************************************
** Form generated from reading UI file 'VContentView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCONTENTVIEW_H
#define UI_VCONTENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VContentViewClass
{
public:

    void setupUi(QWidget *VContentViewClass)
    {
        if (VContentViewClass->objectName().isEmpty())
            VContentViewClass->setObjectName("VContentViewClass");
        VContentViewClass->resize(600, 400);

        retranslateUi(VContentViewClass);

        QMetaObject::connectSlotsByName(VContentViewClass);
    } // setupUi

    void retranslateUi(QWidget *VContentViewClass)
    {
        VContentViewClass->setWindowTitle(QCoreApplication::translate("VContentViewClass", "VContentView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VContentViewClass: public Ui_VContentViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCONTENTVIEW_H
