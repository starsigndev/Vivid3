/********************************************************************************
** Form generated from reading UI file 'VOutput.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOUTPUT_H
#define UI_VOUTPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VOutputClass
{
public:

    void setupUi(QWidget *VOutputClass)
    {
        if (VOutputClass->objectName().isEmpty())
            VOutputClass->setObjectName("VOutputClass");
        VOutputClass->resize(600, 400);

        retranslateUi(VOutputClass);

        QMetaObject::connectSlotsByName(VOutputClass);
    } // setupUi

    void retranslateUi(QWidget *VOutputClass)
    {
        VOutputClass->setWindowTitle(QCoreApplication::translate("VOutputClass", "VOutput", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VOutputClass: public Ui_VOutputClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOUTPUT_H
