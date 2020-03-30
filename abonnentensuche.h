#ifndef ABONNENTENINLANDSUCHE_H
#define ABONNENTENINLANDSUCHE_H

#include <QWidget>
#include <QTableWidget>
#include <QStringList>
#include <QLineEdit>
#include <QComboBox>
#include <QLCDNumber>
#include <QKeyEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QFileDialog>
#include "columnwidthposx.h"
#include "ErrorManagement/ErrorManagement.h"
#include "defaultmeasures.h"
#include "dbinterface.h"
#include "abonnenten.h"
#include "antoniusdbguitab.h"

extern ErrorManagement errorMan;

#define INLAND_SUCHE_COLUMN_COUNT	14

#define FILTER_QLINEEDIT_Y			30

#define ID_WIDTH					70
#define STATUS_WIDTH				50
#define ANREDE_WIDTH				80
#define AMTSTITEL_WIDTH				100
#define TITEL_VOR_WIDTH				100
#define TITEL_NACH_WIDTH			100
#define VORNAME_WIDTH				150
#define NACHNAME_WIDTH				150
#define ORGANISATION_WIDTH			180
#define STRASSE_WIDTH				200
#define PLZ_WIDTH					70
#define ORT_WIDTH					120
#define ANTONIUSANZAHL_WIDTH		100
#define ZUSATZINFO_WIDTH			80

namespace Ui {
class AbonnentenInlandSuche;
}

class AbonnentenInlandSuche : public QWidget
{
    Q_OBJECT

public:
    struct TableRowData
    {
        TableRowData(void);
        TableRowData(QString ID, QString status, QString anrede, QString amtstitel, QString titelVor, QString titelNach, QString vorname, QString nachname, QString organisation, QString strasse, QString plz, QString ort, QString antoniusanzahl, QString zusatzinfo);

        QString ID;
        QString status;
        QString anrede;
        QString amtstitel;
        QString titelVor;
        QString titelNach;
        QString vorname;
        QString nachname;
        QString organisation;
        QString strasse;
        QString plz;
        QString ort;
        QString antoniusanzahl;
        QString zusatzinfo;
    };

    /**
     * @brief The ModQLineEdit class is a subclass of QLineEdit, which reimplements keyPressEvent()
     */
    class ModQLineEdit : public QLineEdit
    {
    private:
        AbonnentenInlandSuche *outerClassInstance;
    public:
        ModQLineEdit(QWidget *parent, AbonnentenInlandSuche *outerClassInstance);
        ~ModQLineEdit();
        void keyPressEvent(QKeyEvent *event);
    };
    /**
     * @brief The ModQComboBox class is a subclass of QComboBox, which reimplements keyPressEvent()
     */
    class ModQComboBox : public QComboBox
    {
    private:
        AbonnentenInlandSuche *outerClassInstance;
    public:
        ModQComboBox(QWidget *parent, AbonnentenInlandSuche *outerClassInstance);
        ~ModQComboBox();
        void keyPressEvent(QKeyEvent *event);
    };

    explicit AbonnentenInlandSuche(DBInterface *dbInterface, QWidget *parent);
    ~AbonnentenInlandSuche();

    void ClearTable(void);
    void AddRow(TableRowData, bool update);
    void AddRowTest(void);

private slots:
    void FiltersChanged(const QString& text);
    void on_checkBoxSortByChangeDate_stateChanged(int arg1);

    void on_tableWidget_cellClicked(int row, int column);

    void on_exportButton_clicked();

private:
    Ui::AbonnentenInlandSuche *ui;
    QWidget *parent;

    QString BuildQueryString(void);
    void ComboboxBuildQueryString(QString& sqlString, QString tableName, QString comboboxColumnName, QString comboboxText, QString columnName, bool& firstWhereClause);
    void BuildQueryStringPart(QString& sqlString, bool& firstWhereClause, QString columnName, QString filterContent);
    void ResetFilters(void);
    void ExecuteQueryUpdateTable(QString sqlString);
    void UpdateLCDNum(void);

    QString GetStatusName(QString statusID);
    QString GetAnredeName(QString anredeID);
    QString GetAmtstitelName(QString amtstitelID);

    //overridden event handler
    void keyPressEvent(QKeyEvent *event);

    DBInterface *dbInterface;

    ModQLineEdit *IDFilter;
    ModQLineEdit *TitelVorFilter;
    ModQLineEdit *TitelNachFilter;
    ModQLineEdit *VornameFilter;
    ModQLineEdit *NachnameFilter;
    ModQLineEdit *OrganisationFilter;
    ModQLineEdit *StrasseFilter;
    ModQLineEdit *PLZFilter;
    ModQLineEdit *OrtFilter;

    ModQComboBox *StatusFilter;
    ModQComboBox *AnredeFilter;
    ModQComboBox *AmtstitelFilter;

    QStringList tableHeaderList;
};

#endif // ABONNENTENINLANDSUCHE_H
