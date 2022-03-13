/********************************************************************************
** Form generated from reading UI file 'abonnentensuche.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABONNENTENSUCHE_H
#define UI_ABONNENTENSUCHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AbonnentenSuche
{
public:
    QCheckBox *checkBoxSortByChangeDate;
    QLCDNumber *lcdNumTableRows;
    QPushButton *exportButton;
    QTableView *searchTable;
    QPushButton *backupButton;

    void setupUi(QWidget *AbonnentenSuche)
    {
        if (AbonnentenSuche->objectName().isEmpty())
            AbonnentenSuche->setObjectName(QStringLiteral("AbonnentenSuche"));
        AbonnentenSuche->resize(1600, 800);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(9);
        AbonnentenSuche->setFont(font);
        AbonnentenSuche->setStyleSheet(QStringLiteral(""));
        checkBoxSortByChangeDate = new QCheckBox(AbonnentenSuche);
        checkBoxSortByChangeDate->setObjectName(QStringLiteral("checkBoxSortByChangeDate"));
        checkBoxSortByChangeDate->setGeometry(QRect(860, 3, 281, 21));
        QFont font1;
        font1.setPointSize(11);
        checkBoxSortByChangeDate->setFont(font1);
        lcdNumTableRows = new QLCDNumber(AbonnentenSuche);
        lcdNumTableRows->setObjectName(QStringLiteral("lcdNumTableRows"));
        lcdNumTableRows->setGeometry(QRect(1493, 0, 101, 31));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(0, 212, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 85, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 113, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(127, 212, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush11(QColor(0, 0, 0, 128));
        brush11.setStyle(Qt::NoBrush);
        //palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
        lcdNumTableRows->setPalette(palette);
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(QFont::Weight(50));
        lcdNumTableRows->setFont(font2);
        lcdNumTableRows->setFrameShape(QFrame::Box);
        lcdNumTableRows->setFrameShadow(QFrame::Raised);
        lcdNumTableRows->setLineWidth(2);
        exportButton = new QPushButton(AbonnentenSuche);
        exportButton->setObjectName(QStringLiteral("exportButton"));
        exportButton->setGeometry(QRect(1150, 0, 111, 30));
        searchTable = new QTableView(AbonnentenSuche);
        searchTable->setObjectName(QStringLiteral("searchTable"));
        searchTable->setGeometry(QRect(0, 59, 1590, 731));
        QFont font3;
        font3.setFamily(QStringLiteral("Calibri"));
        font3.setPointSize(12);
        searchTable->setFont(font3);
        searchTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        searchTable->horizontalHeader()->setHighlightSections(false);
        searchTable->verticalHeader()->setVisible(false);
        searchTable->verticalHeader()->setHighlightSections(false);
        backupButton = new QPushButton(AbonnentenSuche);
        backupButton->setObjectName(QStringLiteral("backupButton"));
        backupButton->setGeometry(QRect(1340, 0, 101, 31));

        retranslateUi(AbonnentenSuche);

        QMetaObject::connectSlotsByName(AbonnentenSuche);
    } // setupUi

    void retranslateUi(QWidget *AbonnentenSuche)
    {
        AbonnentenSuche->setWindowTitle(QApplication::translate("AbonnentenSuche", "Form", nullptr));
        checkBoxSortByChangeDate->setText(QApplication::translate("AbonnentenSuche", "Nach \303\204nderungsdatum sortieren", nullptr));
        exportButton->setText(QApplication::translate("AbonnentenSuche", "EXPORT", nullptr));
        backupButton->setText(QApplication::translate("AbonnentenSuche", "BACKUP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AbonnentenSuche: public Ui_AbonnentenSuche {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABONNENTENSUCHE_H
