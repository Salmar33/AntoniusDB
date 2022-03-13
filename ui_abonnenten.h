/********************************************************************************
** Form generated from reading UI file 'abonnenten.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABONNENTEN_H
#define UI_ABONNENTEN_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Abonnenten
{
public:
    QPushButton *buttonBuchungHinzu;
    QLineEdit *lineEditTelNr;
    QLineEdit *lineEditEmail;
    QLabel *label_12;
    QLineEdit *lineEditTitelNach;
    QLabel *label_21;
    QLabel *label_9;
    QLabel *label_5;
    QLineEdit *lineEditMobil;
    QLineEdit *lineEditMietcode;
    QComboBox *comboPLZ;
    QLabel *label_6;
    QLabel *label_25;
    QLabel *label_10;
    QLineEdit *lineEditZusatzinfo;
    QLabel *label_7;
    QLineEdit *lineEditVorname;
    QLabel *label_23;
    QLabel *label_20;
    QLabel *label_19;
    QDateTimeEdit *dateStatusGesetzt;
    QComboBox *comboStatus;
    QLabel *label_14;
    QLabel *label_24;
    QPushButton *buttonHeute;
    QLabel *label_17;
    QLabel *label;
    QLabel *label_16;
    QLabel *label_13;
    QCheckBox *checkDankschreiben;
    QLineEdit *lineEditTitelVor;
    QLabel *label_3;
    QLineEdit *lineEditOrt;
    QLineEdit *lineEditBeruf;
    QLabel *label_22;
    QLabel *label_8;
    QLineEdit *lineEditNachname;
    QLineEdit *lineEditStrasse;
    QLabel *label_18;
    QPushButton *pushButtonNewRecord;
    QLabel *label_2;
    QTextEdit *txtEditAnmerkungen;
    QSpinBox *spinAntoniusAnzahl;
    QComboBox *comboAnrede;
    QComboBox *comboAmtstitel;
    QTableView *tableBuchungen;
    QDateTimeEdit *dateLetzteAenderung;
    QLineEdit *lineEditID;
    QLabel *label_4;
    QLineEdit *lineEditOrganisation;
    QLineEdit *lineEditPLZ;
    QLabel *label_11;
    QLabel *label_15;
    QDateEdit *dateErstelltAm;
    QLineEdit *lineEditLand;
    QComboBox *comboOrt;

    void setupUi(QWidget *Abonnenten)
    {
        if (Abonnenten->objectName().isEmpty())
            Abonnenten->setObjectName(QStringLiteral("Abonnenten"));
        Abonnenten->resize(1500, 800);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        Abonnenten->setFont(font);
        buttonBuchungHinzu = new QPushButton(Abonnenten);
        buttonBuchungHinzu->setObjectName(QStringLiteral("buttonBuchungHinzu"));
        buttonBuchungHinzu->setGeometry(QRect(229, 710, 291, 51));
        lineEditTelNr = new QLineEdit(Abonnenten);
        lineEditTelNr->setObjectName(QStringLiteral("lineEditTelNr"));
        lineEditTelNr->setGeometry(QRect(936, 240, 351, 27));
        lineEditTelNr->setFont(font);
        lineEditEmail = new QLineEdit(Abonnenten);
        lineEditEmail->setObjectName(QStringLiteral("lineEditEmail"));
        lineEditEmail->setGeometry(QRect(936, 303, 351, 27));
        lineEditEmail->setFont(font);
        label_12 = new QLabel(Abonnenten);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(1, 169, 141, 31));
        label_12->setFont(font);
        lineEditTitelNach = new QLineEdit(Abonnenten);
        lineEditTitelNach->setObjectName(QStringLiteral("lineEditTitelNach"));
        lineEditTitelNach->setGeometry(QRect(149, 171, 351, 27));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(12);
        font1.setKerning(true);
        lineEditTitelNach->setFont(font1);
        label_21 = new QLabel(Abonnenten);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(800, 303, 53, 24));
        label_21->setMaximumSize(QSize(71, 16777215));
        label_21->setFont(font);
        label_9 = new QLabel(Abonnenten);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(1, 459, 141, 20));
        label_9->setFont(font);
        label_5 = new QLabel(Abonnenten);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(149, 425, 171, 20));
        label_5->setFont(font);
        lineEditMobil = new QLineEdit(Abonnenten);
        lineEditMobil->setObjectName(QStringLiteral("lineEditMobil"));
        lineEditMobil->setGeometry(QRect(936, 273, 351, 27));
        lineEditMobil->setFont(font);
        lineEditMietcode = new QLineEdit(Abonnenten);
        lineEditMietcode->setObjectName(QStringLiteral("lineEditMietcode"));
        lineEditMietcode->setGeometry(QRect(149, 459, 181, 27));
        lineEditMietcode->setMinimumSize(QSize(113, 20));
        lineEditMietcode->setFont(font);
        comboPLZ = new QComboBox(Abonnenten);
        comboPLZ->setObjectName(QStringLiteral("comboPLZ"));
        comboPLZ->setGeometry(QRect(351, 425, 79, 28));
        comboPLZ->setFont(font);
        comboPLZ->setEditable(true);
        comboPLZ->setInsertPolicy(QComboBox::NoInsert);
        label_6 = new QLabel(Abonnenten);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(1, 256, 141, 20));
        label_6->setFont(font);
        label_25 = new QLabel(Abonnenten);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(800, 336, 46, 24));
        label_25->setMaximumSize(QSize(61, 16777215));
        label_25->setFont(font);
        label_10 = new QLabel(Abonnenten);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(1, 392, 141, 20));
        label_10->setFont(font);
        lineEditZusatzinfo = new QLineEdit(Abonnenten);
        lineEditZusatzinfo->setObjectName(QStringLiteral("lineEditZusatzinfo"));
        lineEditZusatzinfo->setGeometry(QRect(936, 171, 351, 61));
        lineEditZusatzinfo->setFont(font);
        label_7 = new QLabel(Abonnenten);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(1, 305, 141, 31));
        label_7->setFont(font);
        lineEditVorname = new QLineEdit(Abonnenten);
        lineEditVorname->setObjectName(QStringLiteral("lineEditVorname"));
        lineEditVorname->setGeometry(QRect(149, 223, 351, 27));
        lineEditVorname->setMinimumSize(QSize(113, 20));
        lineEditVorname->setFont(font);
        label_23 = new QLabel(Abonnenten);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(800, 470, 121, 24));
        label_23->setMaximumSize(QSize(300, 16777215));
        label_23->setFont(font);
        label_20 = new QLabel(Abonnenten);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(800, 273, 49, 24));
        label_20->setMaximumSize(QSize(71, 16777215));
        label_20->setFont(font);
        label_19 = new QLabel(Abonnenten);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(800, 240, 43, 24));
        label_19->setMaximumSize(QSize(81, 16777215));
        label_19->setFont(font);
        dateStatusGesetzt = new QDateTimeEdit(Abonnenten);
        dateStatusGesetzt->setObjectName(QStringLiteral("dateStatusGesetzt"));
        dateStatusGesetzt->setGeometry(QRect(936, 470, 221, 28));
        dateStatusGesetzt->setFont(font);
        dateStatusGesetzt->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateStatusGesetzt->setDate(QDate(1754, 9, 14));
        dateStatusGesetzt->setMinimumDateTime(QDateTime(QDate(1752, 9, 14), QTime(0, 0, 0)));
        dateStatusGesetzt->setMinimumDate(QDate(1752, 9, 14));
        dateStatusGesetzt->setCalendarPopup(true);
        comboStatus = new QComboBox(Abonnenten);
        comboStatus->setObjectName(QStringLiteral("comboStatus"));
        comboStatus->setGeometry(QRect(936, 436, 79, 28));
        comboStatus->setFont(font);
        comboStatus->setEditable(true);
        comboStatus->setInsertPolicy(QComboBox::NoInsert);
        label_14 = new QLabel(Abonnenten);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(936, 1, 151, 31));
        label_14->setFont(font);
        label_24 = new QLabel(Abonnenten);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(800, 504, 121, 24));
        label_24->setMaximumSize(QSize(300, 16777215));
        label_24->setFont(font);
        buttonHeute = new QPushButton(Abonnenten);
        buttonHeute->setObjectName(QStringLiteral("buttonHeute"));
        buttonHeute->setGeometry(QRect(630, 1, 131, 28));
        buttonHeute->setFont(font);
        label_17 = new QLabel(Abonnenten);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(800, 137, 131, 24));
        label_17->setMinimumSize(QSize(100, 0));
        label_17->setMaximumSize(QSize(300, 16777215));
        label_17->setFont(font);
        label = new QLabel(Abonnenten);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1, 37, 31, 20));
        label->setFont(font);
        label_16 = new QLabel(Abonnenten);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(1, 107, 141, 20));
        label_16->setFont(font);
        label_13 = new QLabel(Abonnenten);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(800, 103, 131, 24));
        label_13->setMaximumSize(QSize(300, 16777215));
        label_13->setFont(font);
        checkDankschreiben = new QCheckBox(Abonnenten);
        checkDankschreiben->setObjectName(QStringLiteral("checkDankschreiben"));
        checkDankschreiben->setGeometry(QRect(936, 104, 51, 26));
        checkDankschreiben->setFont(font);
        lineEditTitelVor = new QLineEdit(Abonnenten);
        lineEditTitelVor->setObjectName(QStringLiteral("lineEditTitelVor"));
        lineEditTitelVor->setGeometry(QRect(149, 137, 351, 27));
        lineEditTitelVor->setMinimumSize(QSize(113, 20));
        lineEditTitelVor->setFont(font1);
        label_3 = new QLabel(Abonnenten);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1, 137, 141, 30));
        label_3->setFont(font);
        lineEditOrt = new QLineEdit(Abonnenten);
        lineEditOrt->setObjectName(QStringLiteral("lineEditOrt"));
        lineEditOrt->setGeometry(QRect(550, 392, 221, 27));
        lineEditOrt->setFont(font);
        lineEditBeruf = new QLineEdit(Abonnenten);
        lineEditBeruf->setObjectName(QStringLiteral("lineEditBeruf"));
        lineEditBeruf->setGeometry(QRect(936, 336, 351, 27));
        lineEditBeruf->setFont(font);
        label_22 = new QLabel(Abonnenten);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(800, 436, 52, 24));
        label_22->setMaximumSize(QSize(81, 16777215));
        label_22->setFont(font);
        label_8 = new QLabel(Abonnenten);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(1, 359, 141, 20));
        label_8->setFont(font);
        lineEditNachname = new QLineEdit(Abonnenten);
        lineEditNachname->setObjectName(QStringLiteral("lineEditNachname"));
        lineEditNachname->setGeometry(QRect(149, 256, 351, 27));
        lineEditNachname->setMinimumSize(QSize(113, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(QFont::Weight(75));
        lineEditNachname->setFont(font2);
        lineEditStrasse = new QLineEdit(Abonnenten);
        lineEditStrasse->setObjectName(QStringLiteral("lineEditStrasse"));
        lineEditStrasse->setGeometry(QRect(149, 359, 351, 27));
        lineEditStrasse->setMinimumSize(QSize(113, 20));
        lineEditStrasse->setFont(font);
        label_18 = new QLabel(Abonnenten);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(800, 171, 86, 24));
        label_18->setMaximumSize(QSize(91, 16777215));
        label_18->setFont(font);
        pushButtonNewRecord = new QPushButton(Abonnenten);
        pushButtonNewRecord->setObjectName(QStringLiteral("pushButtonNewRecord"));
        pushButtonNewRecord->setGeometry(QRect(670, 550, 111, 101));
        pushButtonNewRecord->setMinimumSize(QSize(0, 60));
        pushButtonNewRecord->setAutoDefault(false);
        pushButtonNewRecord->setFlat(false);
        label_2 = new QLabel(Abonnenten);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1, 72, 141, 20));
        label_2->setFont(font);
        txtEditAnmerkungen = new QTextEdit(Abonnenten);
        txtEditAnmerkungen->setObjectName(QStringLiteral("txtEditAnmerkungen"));
        txtEditAnmerkungen->setGeometry(QRect(936, 504, 551, 192));
        txtEditAnmerkungen->setFont(font);
        txtEditAnmerkungen->setTabChangesFocus(true);
        spinAntoniusAnzahl = new QSpinBox(Abonnenten);
        spinAntoniusAnzahl->setObjectName(QStringLiteral("spinAntoniusAnzahl"));
        spinAntoniusAnzahl->setGeometry(QRect(936, 137, 66, 28));
        spinAntoniusAnzahl->setFont(font);
        spinAntoniusAnzahl->setMinimum(1);
        spinAntoniusAnzahl->setMaximum(10000);
        spinAntoniusAnzahl->setValue(1);
        comboAnrede = new QComboBox(Abonnenten);
        comboAnrede->setObjectName(QStringLiteral("comboAnrede"));
        comboAnrede->setGeometry(QRect(149, 69, 351, 28));
        comboAnrede->setMinimumSize(QSize(69, 22));
        comboAnrede->setFont(font);
        comboAnrede->setEditable(true);
        comboAnrede->setInsertPolicy(QComboBox::NoInsert);
        comboAmtstitel = new QComboBox(Abonnenten);
        comboAmtstitel->setObjectName(QStringLiteral("comboAmtstitel"));
        comboAmtstitel->setGeometry(QRect(149, 103, 351, 28));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboAmtstitel->sizePolicy().hasHeightForWidth());
        comboAmtstitel->setSizePolicy(sizePolicy);
        comboAmtstitel->setFont(font);
        comboAmtstitel->setEditable(true);
        comboAmtstitel->setInsertPolicy(QComboBox::NoInsert);
        comboAmtstitel->setIconSize(QSize(20, 20));
        tableBuchungen = new QTableView(Abonnenten);
        tableBuchungen->setObjectName(QStringLiteral("tableBuchungen"));
        tableBuchungen->setGeometry(QRect(149, 504, 451, 192));
        tableBuchungen->setFont(font);
        tableBuchungen->setEditTriggers(QAbstractItemView::NoEditTriggers);
        dateLetzteAenderung = new QDateTimeEdit(Abonnenten);
        dateLetzteAenderung->setObjectName(QStringLiteral("dateLetzteAenderung"));
        dateLetzteAenderung->setEnabled(true);
        dateLetzteAenderung->setGeometry(QRect(936, 35, 181, 28));
        dateLetzteAenderung->setFont(font);
        dateLetzteAenderung->setReadOnly(true);
        dateLetzteAenderung->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateLetzteAenderung->setCalendarPopup(true);
        lineEditID = new QLineEdit(Abonnenten);
        lineEditID->setObjectName(QStringLiteral("lineEditID"));
        lineEditID->setGeometry(QRect(149, 35, 125, 27));
        lineEditID->setMinimumSize(QSize(113, 20));
        lineEditID->setFont(font);
        lineEditID->setReadOnly(true);
        label_4 = new QLabel(Abonnenten);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1, 223, 141, 20));
        label_4->setFont(font);
        lineEditOrganisation = new QLineEdit(Abonnenten);
        lineEditOrganisation->setObjectName(QStringLiteral("lineEditOrganisation"));
        lineEditOrganisation->setGeometry(QRect(149, 308, 351, 27));
        lineEditOrganisation->setMinimumSize(QSize(113, 20));
        lineEditOrganisation->setFont(font);
        lineEditPLZ = new QLineEdit(Abonnenten);
        lineEditPLZ->setObjectName(QStringLiteral("lineEditPLZ"));
        lineEditPLZ->setGeometry(QRect(351, 392, 81, 27));
        lineEditPLZ->setFont(font);
        label_11 = new QLabel(Abonnenten);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(451, 425, 93, 20));
        label_11->setFont(font);
        label_15 = new QLabel(Abonnenten);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(515, 35, 101, 20));
        label_15->setFont(font);
        dateErstelltAm = new QDateEdit(Abonnenten);
        dateErstelltAm->setObjectName(QStringLiteral("dateErstelltAm"));
        dateErstelltAm->setGeometry(QRect(630, 35, 131, 28));
        dateErstelltAm->setFont(font);
        dateErstelltAm->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dateErstelltAm->setCalendarPopup(true);
        lineEditLand = new QLineEdit(Abonnenten);
        lineEditLand->setObjectName(QStringLiteral("lineEditLand"));
        lineEditLand->setGeometry(QRect(149, 392, 191, 27));
        lineEditLand->setMinimumSize(QSize(31, 20));
        lineEditLand->setFont(font);
        comboOrt = new QComboBox(Abonnenten);
        comboOrt->setObjectName(QStringLiteral("comboOrt"));
        comboOrt->setGeometry(QRect(550, 425, 221, 28));
        comboOrt->setFont(font);
        comboOrt->setEditable(true);
        comboOrt->setInsertPolicy(QComboBox::NoInsert);
        QWidget::setTabOrder(lineEditID, comboAnrede);
        QWidget::setTabOrder(comboAnrede, comboAmtstitel);
        QWidget::setTabOrder(comboAmtstitel, lineEditTitelVor);
        QWidget::setTabOrder(lineEditTitelVor, lineEditTitelNach);
        QWidget::setTabOrder(lineEditTitelNach, lineEditVorname);
        QWidget::setTabOrder(lineEditVorname, lineEditNachname);
        QWidget::setTabOrder(lineEditNachname, lineEditOrganisation);
        QWidget::setTabOrder(lineEditOrganisation, lineEditStrasse);
        QWidget::setTabOrder(lineEditStrasse, lineEditLand);
        QWidget::setTabOrder(lineEditLand, lineEditPLZ);
        QWidget::setTabOrder(lineEditPLZ, lineEditOrt);
        QWidget::setTabOrder(lineEditOrt, comboPLZ);
        QWidget::setTabOrder(comboPLZ, comboOrt);
        QWidget::setTabOrder(comboOrt, lineEditMietcode);
        QWidget::setTabOrder(lineEditMietcode, checkDankschreiben);
        QWidget::setTabOrder(checkDankschreiben, spinAntoniusAnzahl);
        QWidget::setTabOrder(spinAntoniusAnzahl, lineEditZusatzinfo);
        QWidget::setTabOrder(lineEditZusatzinfo, lineEditTelNr);
        QWidget::setTabOrder(lineEditTelNr, lineEditMobil);
        QWidget::setTabOrder(lineEditMobil, lineEditEmail);
        QWidget::setTabOrder(lineEditEmail, lineEditBeruf);
        QWidget::setTabOrder(lineEditBeruf, comboStatus);
        QWidget::setTabOrder(comboStatus, dateStatusGesetzt);
        QWidget::setTabOrder(dateStatusGesetzt, txtEditAnmerkungen);
        QWidget::setTabOrder(txtEditAnmerkungen, buttonHeute);
        QWidget::setTabOrder(buttonHeute, dateErstelltAm);
        QWidget::setTabOrder(dateErstelltAm, dateLetzteAenderung);
        QWidget::setTabOrder(dateLetzteAenderung, pushButtonNewRecord);

        retranslateUi(Abonnenten);

        pushButtonNewRecord->setDefault(false);


        QMetaObject::connectSlotsByName(Abonnenten);
    } // setupUi

    void retranslateUi(QWidget *Abonnenten)
    {
        Abonnenten->setWindowTitle(QApplication::translate("Abonnenten", "Form", nullptr));
        buttonBuchungHinzu->setText(QApplication::translate("Abonnenten", "Buchung hinzuf\303\274gen", nullptr));
        label_12->setText(QApplication::translate("Abonnenten", "Titel nachgestellt", nullptr));
        label_21->setText(QApplication::translate("Abonnenten", "E-Mail", nullptr));
        label_9->setText(QApplication::translate("Abonnenten", "Mietcode", nullptr));
        label_5->setText(QApplication::translate("Abonnenten", "\303\226. PLZ", nullptr));
        label_6->setText(QApplication::translate("Abonnenten", "Nachname", nullptr));
        label_25->setText(QApplication::translate("Abonnenten", "Beruf", nullptr));
        label_10->setText(QApplication::translate("Abonnenten", "Land/Plz/Ort", nullptr));
        label_7->setText(QApplication::translate("Abonnenten", "Organisation", nullptr));
        label_23->setText(QApplication::translate("Abonnenten", "Status gesetzt", nullptr));
        label_20->setText(QApplication::translate("Abonnenten", "Mobil", nullptr));
        label_19->setText(QApplication::translate("Abonnenten", "TelNr", nullptr));
        dateStatusGesetzt->setSpecialValueText(QString());
        label_14->setText(QApplication::translate("Abonnenten", "Letzte \303\204nderung", nullptr));
        label_24->setText(QApplication::translate("Abonnenten", "Anmerkungen", nullptr));
        buttonHeute->setText(QApplication::translate("Abonnenten", "Heute", nullptr));
        label_17->setText(QApplication::translate("Abonnenten", "Antoniusanzahl", nullptr));
        label->setText(QApplication::translate("Abonnenten", "ID", nullptr));
        label_16->setText(QApplication::translate("Abonnenten", "Amtstitel", nullptr));
        label_13->setText(QApplication::translate("Abonnenten", "Dankschreiben", nullptr));
        checkDankschreiben->setText(QString());
        label_3->setText(QApplication::translate("Abonnenten", "Titel vorgestellt", nullptr));
        label_22->setText(QApplication::translate("Abonnenten", "Status", nullptr));
        label_8->setText(QApplication::translate("Abonnenten", "Stra\303\237e", nullptr));
        label_18->setText(QApplication::translate("Abonnenten", "Zusatzinfo", nullptr));
        pushButtonNewRecord->setText(QApplication::translate("Abonnenten", "Neuen\n"
"Datensatz\n"
"hinzuf\303\274gen", nullptr));
        label_2->setText(QApplication::translate("Abonnenten", "Anrede", nullptr));
        label_4->setText(QApplication::translate("Abonnenten", "Vorname", nullptr));
        label_11->setText(QApplication::translate("Abonnenten", "\303\226. Ort", nullptr));
        label_15->setText(QApplication::translate("Abonnenten", "Erstellt am", nullptr));
        lineEditLand->setPlaceholderText(QApplication::translate("Abonnenten", "A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Abonnenten: public Ui_Abonnenten {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABONNENTEN_H
