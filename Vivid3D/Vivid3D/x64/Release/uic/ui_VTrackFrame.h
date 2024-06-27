/********************************************************************************
** Form generated from reading UI file 'VTrackFrame.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTRACKFRAME_H
#define UI_VTRACKFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTrackFrameClass
{
public:

    void setupUi(QWidget *VTrackFrameClass)
    {
        if (VTrackFrameClass->objectName().isEmpty())
            VTrackFrameClass->setObjectName("VTrackFrameClass");
        VTrackFrameClass->resize(600, 400);

        retranslateUi(VTrackFrameClass);

        QMetaObject::connectSlotsByName(VTrackFrameClass);
    } // setupUi

    void retranslateUi(QWidget *VTrackFrameClass)
    {
        VTrackFrameClass->setWindowTitle(QCoreApplication::translate("VTrackFrameClass", "VTrackFrame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTrackFrameClass: public Ui_VTrackFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTRACKFRAME_H
