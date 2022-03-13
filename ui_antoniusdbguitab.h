/********************************************************************************
** Form generated from reading UI file 'antoniusdbguitab.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANTONIUSDBGUITAB_H
#define UI_ANTONIUSDBGUITAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>

QT_BEGIN_NAMESPACE

class Ui_AntoniusDBGUITab
{
public:

    void setupUi(QTabWidget *AntoniusDBGUITab)
    {
        if (AntoniusDBGUITab->objectName().isEmpty())
            AntoniusDBGUITab->setObjectName(QStringLiteral("AntoniusDBGUITab"));
        AntoniusDBGUITab->setEnabled(true);
        AntoniusDBGUITab->resize(1600, 800);
        AntoniusDBGUITab->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(238, 245, 255, 255), stop:1 rgba(255, 255, 255, 255));"));

        retranslateUi(AntoniusDBGUITab);

        AntoniusDBGUITab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(AntoniusDBGUITab);
    } // setupUi

    void retranslateUi(QTabWidget *AntoniusDBGUITab)
    {
        AntoniusDBGUITab->setWindowTitle(QApplication::translate("AntoniusDBGUITab", "TabWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AntoniusDBGUITab: public Ui_AntoniusDBGUITab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANTONIUSDBGUITAB_H
