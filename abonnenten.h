#ifndef ABONNENTENINLAND_H
#define ABONNENTENINLAND_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlQuery>
#include <QComboBox>
#include <QDebug>
#include <QSqlError>
#include <QApplication>
#include <QEvent>

#include "ErrorManagement/ErrorManagement.h"
#include "defaultmeasures.h"
#include "dbinterface.h"
#include "buchunghinzu.h"

extern ErrorManagement errorMan;

namespace Ui {
class AbonnentenInland;
}

class AbonnentenInland : public QWidget
{
    Q_OBJECT

public:
    explicit AbonnentenInland(DBInterface *dbInterface, QWidget *parent = nullptr);
    ~AbonnentenInland();
    void SetActiveID(unsigned int newActiveID);
    void LoadActiveRecord(void);

private:
    Ui::AbonnentenInland *ui;

    unsigned int activeID;			//contains the ID of the currently active record that is displayed on this form
    bool prChange;					//should always be set to true before any changes of values in this form are done programmatically (e.g. for setup purposes)
                                    //and then back to false so that we can differentiate whether changes happened due to the input of the user changing entries

    DBInterface *dbInterface;
    QSqlTableModel *amtstitelModel;
    QSqlTableModel *anredeModel;
    QSqlRelationalTableModel *ortModel;
    QSqlTableModel *plzModel;
    QSqlTableModel *statusModel;

    QSqlTableModel *buchungenModel;

    void SetUpdateDateTimeLastChangeToCurrentDateTime(void);
    void SetUpdateDateTimeForStatusChangeToCurrentDateTime(void);
    void MoveToAnmerkungen(void);
    void SetNextRecordActive(void);
    void SetPreviousRecordActive(void);
    bool HandleComboBoxManipulationTableModel(QComboBox *comboBox, QString comboBoxTable, QString comboBoxColumnName, QString comboBoxColumnID, QString tableMain, QString columnMain, unsigned int currentID, bool allowNew, std::atomic_flag& atomicFlag);
    void HandleComboBoxManipulationRelationalTableModel(QComboBox *comboBox, QString comboBoxTable, QString comboBoxColumnName, QString tableMain, QString columnMain, unsigned int currentID, bool allowNew, std::atomic_flag& atomicFlag, QString juncTable, QString thisJuncColumnID, QString otherJuncColumnID, unsigned int otherCurrentID);

    /********* Event handlers ******/
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    bool eventFilter(QObject *object, QEvent *event);


private slots:
    void on_buttonHeute_released();
    void on_pushButtonNewRecord_clicked();
    void on_lineEditTitelVor_textEdited(const QString &arg1);
    void on_txtEditAnmerkungen_textChanged();
    void on_lineEditTitelNach_textEdited(const QString &arg1);
    void on_lineEditVorname_textEdited(const QString &arg1);
    void on_lineEditNachname_textEdited(const QString &arg1);
    void on_lineEditOrganisation_textEdited(const QString &arg1);
    void on_lineEditStrasse_textEdited(const QString &arg1);
    void on_lineEditLand_textEdited(const QString &arg1);
    void on_lineEditPLZ_textEdited(const QString &arg1);
    void on_lineEditOrt_textEdited(const QString &arg1);
    void on_lineEditMietcode_textEdited(const QString &arg1);
    void on_lineEditZusatzinfo_textEdited(const QString &arg1);
    void on_lineEditTelNr_textEdited(const QString &arg1);
    void on_lineEditMobil_textEdited(const QString &arg1);
    void on_lineEditEmail_textEdited(const QString &arg1);
    void on_lineEditBeruf_textEdited(const QString &arg1);
    void on_checkDankschreiben_clicked(bool checked);
    void on_spinAntoniusAnzahl_editingFinished();
    void on_dateErstelltAm_dateTimeChanged(const QDateTime &dateTime);
    void on_dateStatusGesetzt_dateTimeChanged(const QDateTime &dateTime);
};

#endif // ABONNENTENINLAND_H
