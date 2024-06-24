/********************************************************************************
** Form generated from reading UI file 'VTimeTrack.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VTIMETRACK_H
#define UI_VTIMETRACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VTimeTrackClass
{
public:

    void setupUi(QWidget *VTimeTrackClass)
    {
        if (VTimeTrackClass->objectName().isEmpty())
            VTimeTrackClass->setObjectName("VTimeTrackClass");
        VTimeTrackClass->resize(600, 400);

        retranslateUi(VTimeTrackClass);

        QMetaObject::connectSlotsByName(VTimeTrackClass);
    } // setupUi

    void retranslateUi(QWidget *VTimeTrackClass)
    {
        VTimeTrackClass->setWindowTitle(QCoreApplication::translate("VTimeTrackClass", "VTimeTrack", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VTimeTrackClass: public Ui_VTimeTrackClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VTIMETRACK_H
