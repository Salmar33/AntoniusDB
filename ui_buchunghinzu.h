/********************************************************************************
** Form generated from reading UI file 'buchunghinzu.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUCHUNGHINZU_H
#define UI_BUCHUNGHINZU_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_BuchungHinzu
{
public:
    QLabel *label;
    QDateEdit *dateEdit;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;
    QLabel *label_3;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QDialog *BuchungHinzu)
    {
        if (BuchungHinzu->objectName().isEmpty())
            BuchungHinzu->setObjectName(QStringLiteral("BuchungHinzu"));
        BuchungHinzu->resize(400, 300);
        label = new QLabel(BuchungHinzu);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 291, 31));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(QFont::Weight(75));
        label->setFont(font);
        dateEdit = new QDateEdit(BuchungHinzu);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(142, 102, 93, 24));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(14);
        dateEdit->setFont(font1);
        dateEdit->setAlignment(Qt::AlignCenter);
        dateEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateEdit->setDate(QDate(2020, 1, 1));
        buttonOK = new QPushButton(BuchungHinzu);
        buttonOK->setObjectName(QStringLiteral("buttonOK"));
        buttonOK->setGeometry(QRect(50, 240, 131, 41));
        buttonOK->setFont(font1);
        buttonCancel = new QPushButton(BuchungHinzu);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(220, 240, 121, 41));
        buttonCancel->setFont(font1);
        label_3 = new QLabel(BuchungHinzu);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 102, 131, 21));
        label_3->setFont(font1);
        label_4 = new QLabel(BuchungHinzu);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 81, 21));
        label_4->setFont(font1);
        doubleSpinBox = new QDoubleSpinBox(BuchungHinzu);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(142, 150, 91, 25));
        doubleSpinBox->setFont(font1);
        doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        doubleSpinBox->setMaximum(1e+7);
        doubleSpinBox->setValue(10);
        QWidget::setTabOrder(dateEdit, doubleSpinBox);
        QWidget::setTabOrder(doubleSpinBox, buttonOK);
        QWidget::setTabOrder(buttonOK, buttonCancel);

        retranslateUi(BuchungHinzu);

        QMetaObject::connectSlotsByName(BuchungHinzu);
    } // setupUi

    void retranslateUi(QDialog *BuchungHinzu)
    {
        BuchungHinzu->setWindowTitle(QApplication::translate("BuchungHinzu", "Dialog", nullptr));
        label->setText(QApplication::translate("BuchungHinzu", "Buchung hinzuf\303\274gen", nullptr));
        buttonOK->setText(QApplication::translate("BuchungHinzu", "OK", nullptr));
        buttonCancel->setText(QApplication::translate("BuchungHinzu", "Cancel", nullptr));
        label_3->setText(QApplication::translate("BuchungHinzu", "Buchungsdatum", nullptr));
        label_4->setText(QApplication::translate("BuchungHinzu", "Betrag", nullptr));
        doubleSpinBox->setSuffix(QApplication::translate("BuchungHinzu", "\342\202\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuchungHinzu: public Ui_BuchungHinzu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUCHUNGHINZU_H
