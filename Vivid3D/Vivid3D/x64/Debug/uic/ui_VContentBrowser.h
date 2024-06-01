/********************************************************************************
** Form generated from reading UI file 'VContentBrowser.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCONTENTBROWSER_H
#define UI_VCONTENTBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VContentBrowserClass
{
public:

    void setupUi(QWidget *VContentBrowserClass)
    {
        if (VContentBrowserClass->objectName().isEmpty())
            VContentBrowserClass->setObjectName("VContentBrowserClass");
        VContentBrowserClass->resize(600, 400);

        retranslateUi(VContentBrowserClass);

        QMetaObject::connectSlotsByName(VContentBrowserClass);
    } // setupUi

    void retranslateUi(QWidget *VContentBrowserClass)
    {
        VContentBrowserClass->setWindowTitle(QCoreApplication::translate("VContentBrowserClass", "VContentBrowser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VContentBrowserClass: public Ui_VContentBrowserClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCONTENTBROWSER_H
