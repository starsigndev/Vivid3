/********************************************************************************
** Form generated from reading UI file 'VTrackNode.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTRACKNODE_H
#define UI_VTRACKNODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTrackNodeClass
{
public:

    void setupUi(QWidget *VTrackNodeClass)
    {
        if (VTrackNodeClass->objectName().isEmpty())
            VTrackNodeClass->setObjectName("VTrackNodeClass");
        VTrackNodeClass->resize(600, 400);

        retranslateUi(VTrackNodeClass);

        QMetaObject::connectSlotsByName(VTrackNodeClass);
    } // setupUi

    void retranslateUi(QWidget *VTrackNodeClass)
    {
        VTrackNodeClass->setWindowTitle(QCoreApplication::translate("VTrackNodeClass", "VTrackNode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTrackNodeClass: public Ui_VTrackNodeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTRACKNODE_H
