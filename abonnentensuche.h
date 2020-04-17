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
#include <QFile>
#include "columnwidthposx.h"
#include "ErrorManagement/ErrorManagement.h"
#include "defaultmeasures.h"
#include "dbinterface.h"
#include "abonnenten.h"
#include "antoniusdbguitab.h"

extern ErrorManagement errorMan;

#define INLAND_SUCHE_COLUMN_COUNT	15

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
#define LAND_WIDTH					120
#define ANTONIUSANZAHL_WIDTH		100
#define ZUSATZINFO_WIDTH			80


extern const QString EXPORT_SQL_PREFIX;

namespace Ui {
class AbonnentenSuche;
}

class AbonnentenSuche : public QWidget
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
        AbonnentenSuche *outerClassInstance;
    public:
        ModQLineEdit(QWidget *parent, AbonnentenSuche *outerClassInstance);
        ~ModQLineEdit();
        void keyPressEvent(QKeyEvent *event);
    };
    /**
     * @brief The ModQComboBox class is a subclass of QComboBox, which reimplements keyPressEvent()
     */
    class ModQComboBox : public QComboBox
    {
    private:
        AbonnentenSuche *outerClassInstance;
    public:
        ModQComboBox(QWidget *parent, AbonnentenSuche *outerClassInstance);
        ~ModQComboBox();
        void keyPressEvent(QKeyEvent *event);
    };

    explicit AbonnentenSuche(DBInterface *dbInterface, QWidget *parent);
    ~AbonnentenSuche();

private slots:
    void FiltersChanged(const QString& text);
    void on_checkBoxSortByChangeDate_stateChanged(int arg1);

    void on_exportButton_clicked(void);
    void ExportRoutine(void);
    void WriteExportQueryOutputToCSVFile(QString fileName, QString queryString, unsigned int numberOfColumns);

    void on_searchTable_clicked(const QModelIndex &index);

private:
    Ui::AbonnentenSuche *ui;
    QWidget *parent;
    bool prFilterChange;

    DBInterface *dbInterface;

    ModQLineEdit *IDFilter;
    ModQLineEdit *titelVorFilter;
    ModQLineEdit *titelNachFilter;
    ModQLineEdit *vornameFilter;
    ModQLineEdit *nachnameFilter;
    ModQLineEdit *organisationFilter;
    ModQLineEdit *strasseFilter;
    ModQLineEdit *PLZFilter;
    ModQLineEdit *ortFilter;
    ModQLineEdit *landFilter;

    ModQComboBox *statusFilter;
    ModQComboBox *anredeFilter;
    ModQComboBox *amtstitelFilter;

    QSqlTableModel *statusModel;
    QSqlTableModel *anredeModel;
    QSqlTableModel *amtstitelModel;

    QSqlQueryModel *searchTableModel;

    QStringList tableHeaderList;

    QString BuildQueryString(void);
    void ComboboxBuildQueryString(QString& sqlString, QComboBox *comboBox, QString columnName, bool& firstWhereClause);
    void BuildQueryStringPart(QString& sqlString, bool& firstWhereClause, QString columnName, QString filterContent, bool strictComparison);
    void ResetFilters(void);
    void ExecuteQueryUpdateTable(QString sqlString);
    void UpdateLCDNum(void);
    void ResetTableViewSizes(void);
    void RefreshComboboxModels(void);
    void RefreshComboBoxModel(QComboBox *comboBox);

    QString GetStatusName(QString statusID);
    QString GetAnredeName(QString anredeID);
    QString GetAmtstitelName(QString amtstitelID);

    //overridden event handler
    void keyPressEvent(QKeyEvent *event);
};

#endif // ABONNENTENINLANDSUCHE_H
