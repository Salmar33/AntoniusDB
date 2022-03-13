#include "abonnentensuche.h"
#include "ui_abonnentensuche.h"
#include "columnwidthposx.h"
#include <QInputDialog>
#include <cstdlib>

//for testing only
#include <QThread>

const QString EXPORT_SQL_PREFIX("SELECT " +
        ABONNENTEN_TABLE + "." + ABONNENTEN_ID + ", " +
        ANREDE_TABLE + "." + ANREDE_ANREDE + ", " +
        AMTSTITEL_TABLE + "." + AMTSTITEL_AMTSTITEL + ", " +
        ABONNENTEN_TITELVOR + ", " +
        ABONNENTEN_VORNAME + ", " +
        ABONNENTEN_NACHNAME + ", " +
        ABONNENTEN_TITELNACH + ", " +
        ABONNENTEN_ORGANISATION + ", `" +
        ABONNENTEN_STRASSE + "`, " +
        ABONNENTEN_PLZALLGEMEIN + ", " +
        ABONNENTEN_ORTALLGEMEIN + ", " +
        ABONNENTEN_LAND + ", " +
        ABONNENTEN_ANTONIUSANZAHL + ", " +
        ABONNENTEN_ZUSATZINFO +
        " FROM " + ABONNENTEN_TABLE +
        " LEFT JOIN " + ANREDE_TABLE + " ON " + ANREDE_TABLE + "." + ANREDE_ID + " = " + ABONNENTEN_TABLE + "." + ABONNENTEN_ANREDE +
        " LEFT JOIN " + AMTSTITEL_TABLE + " ON " + AMTSTITEL_TABLE + "." + AMTSTITEL_ID + " = " + ABONNENTEN_TABLE + "." + ABONNENTEN_AMTSTITEL +
        " WHERE (" +
        ABONNENTEN_STATUS + " = '0' OR " + ABONNENTEN_STATUS + " IS NULL) AND ");

const QString SEARCH_TABLE_SQL_PREFIX("SELECT " +
        ABONNENTEN_TABLE + "." + ABONNENTEN_ID + ", " +
        STATUS_TABLE + "." + STATUS_STATUS + ", " +
        ANREDE_TABLE + "." + ANREDE_ANREDE + ", " +
        AMTSTITEL_TABLE + "." + AMTSTITEL_AMTSTITEL + ", " +
        ABONNENTEN_TITELVOR + ", " +
        ABONNENTEN_TITELNACH + ", " +
        ABONNENTEN_VORNAME + ", " +
        ABONNENTEN_NACHNAME + ", " +
        ABONNENTEN_ORGANISATION + ", `" +
        ABONNENTEN_STRASSE + "`, " +
        ABONNENTEN_PLZALLGEMEIN + ", " +
        ABONNENTEN_ORTALLGEMEIN + ", " +
        ABONNENTEN_LAND + ", " +
        ABONNENTEN_ANTONIUSANZAHL + ", " +
        //ABONNENTEN_ZUSATZINFO + ", " +
        ABONNENTEN_TABLE + "." + ABONNENTEN_STATUS + ", " +
        ABONNENTEN_TABLE + "." + ABONNENTEN_ANREDE + ", " +
        ABONNENTEN_TABLE + "." + ABONNENTEN_AMTSTITEL +
        " FROM " + ABONNENTEN_TABLE +
        " LEFT JOIN " + STATUS_TABLE + " ON " + STATUS_TABLE + "." + STATUS_ID + " = " + ABONNENTEN_TABLE + "." + ABONNENTEN_STATUS +
        " LEFT JOIN " + ANREDE_TABLE + " ON " + ANREDE_TABLE + "." + ANREDE_ID + " = " + ABONNENTEN_TABLE + "." + ABONNENTEN_ANREDE +
        " LEFT JOIN " + AMTSTITEL_TABLE + " ON " + AMTSTITEL_TABLE + "." + AMTSTITEL_ID + " = " + ABONNENTEN_TABLE + "." + ABONNENTEN_AMTSTITEL);


AbonnentenSuche::AbonnentenSuche(DBInterface *dbInterface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbonnentenSuche)
{
    ui->setupUi(this);
    this->dbInterface = dbInterface;
    this->parent = parent;

    prFilterChange = false;
    /********** set the horizontal headers for the table **********/

    //setup and set the SQL model (with relations) of the table
    try{ searchTableModel = new QSqlQueryModel(this); }
    catch(std::bad_alloc exc)
    {
        errorMan.BailOut("Error, std::bad_alloc exception", __FILE__, __LINE__, FAILURE);
    }

    ui->searchTable->setModel(searchTableModel);

    ui->searchTable->verticalHeader()->hide();


    //set positions of the search fields (we also refer to them as "filters")
    ColumnWidthPosX colWPosX;		//this object is used to correctly position the search fields (filters) over the corresponding columns
    colWPosX.Append(ID_WIDTH, QString("ID"));
    colWPosX.Append(STATUS_WIDTH, QString("Status"));
    colWPosX.Append(ANREDE_WIDTH, QString("Anrede"));
    colWPosX.Append(AMTSTITEL_WIDTH, QString("Amtstitel"));
    colWPosX.Append(TITEL_VOR_WIDTH, QString("Titel vorgestellt"));
    colWPosX.Append(TITEL_NACH_WIDTH, QString("Titel nachgestellt"));
    colWPosX.Append(VORNAME_WIDTH, QString("Vorname"));
    colWPosX.Append(NACHNAME_WIDTH, QString("Nachname"));
    colWPosX.Append(ORGANISATION_WIDTH, QString("Organisation"));
    colWPosX.Append(STRASSE_WIDTH, QString("Straße"));
    colWPosX.Append(PLZ_WIDTH, QString("Plz"));
    colWPosX.Append(ORT_WIDTH, QString("Ort"));
    colWPosX.Append(LAND_WIDTH, QString("Land"));
    colWPosX.Append(ANTONIUSANZAHL_WIDTH, QString("Antoniusanzahl"));
    //colWPosX.Append(ZUSATZINFO_WIDTH, QString("Zusatzinfo"));

    QFont font(QString("Calibri"), DEFAULT_FONT_SIZE);
    QFont comboBoxfont(QString("Calibri"), COMBOBOX_FONT_SIZE);

    // create the line edit and combobox objects (for entering the filter criteria for the table) and move them to their correct position
    try
    {
        IDFilter = new ModQLineEdit(this, this);
        IDFilter->move(QPoint(colWPosX.CalcPosX(QString("ID")), FILTER_QLINEEDIT_Y));
        IDFilter->setFont(font);
        IDFilter->setFixedWidth(ID_WIDTH);

        titelVorFilter = new ModQLineEdit(this, this);
        titelVorFilter->move(QPoint(colWPosX.CalcPosX(QString("Titel vorgestellt")), FILTER_QLINEEDIT_Y));
        titelVorFilter->setFont(font);
        titelVorFilter->setFixedWidth(TITEL_VOR_WIDTH);

        titelNachFilter = new ModQLineEdit(this, this);
        titelNachFilter->move(QPoint(colWPosX.CalcPosX(QString("Titel nachgestellt")), FILTER_QLINEEDIT_Y));
        titelNachFilter->setFont(font);
        titelNachFilter->setFixedWidth(TITEL_NACH_WIDTH);

        vornameFilter = new ModQLineEdit(this, this);
        vornameFilter->move(QPoint(colWPosX.CalcPosX(QString("Vorname")), FILTER_QLINEEDIT_Y));
        vornameFilter->setFont(font);
        vornameFilter->setFixedWidth(VORNAME_WIDTH);

        nachnameFilter = new ModQLineEdit(this, this);
        nachnameFilter->move(QPoint(colWPosX.CalcPosX(QString("Nachname")), FILTER_QLINEEDIT_Y));
        nachnameFilter->setFont(font);
        nachnameFilter->setFixedWidth(NACHNAME_WIDTH);

        organisationFilter = new ModQLineEdit(this, this);
        organisationFilter->move(QPoint(colWPosX.CalcPosX(QString("Organisation")), FILTER_QLINEEDIT_Y));
        organisationFilter->setFont(font);
        organisationFilter->setFixedWidth(ORGANISATION_WIDTH);

        strasseFilter = new ModQLineEdit(this, this);
        strasseFilter->move(QPoint(colWPosX.CalcPosX(QString("Straße")), FILTER_QLINEEDIT_Y));
        strasseFilter->setFont(font);
        strasseFilter->setFixedWidth(STRASSE_WIDTH);

        PLZFilter = new ModQLineEdit(this, this);
        PLZFilter->move(QPoint(colWPosX.CalcPosX(QString("Plz")), FILTER_QLINEEDIT_Y));
        PLZFilter->setFont(font);
        PLZFilter->setFixedWidth(PLZ_WIDTH);

        ortFilter = new ModQLineEdit(this, this);
        ortFilter->move(QPoint(colWPosX.CalcPosX(QString("Ort")), FILTER_QLINEEDIT_Y));
        ortFilter->setFont(font);
        ortFilter->setFixedWidth(ORT_WIDTH);

        landFilter = new ModQLineEdit(this, this);
        landFilter->move(QPoint(colWPosX.CalcPosX(QString("Land")), FILTER_QLINEEDIT_Y));
        landFilter->setFont(font);
        landFilter->setFixedWidth(ORT_WIDTH);


        statusFilter = new ModQComboBox(this, this);
        statusFilter->setEditable(true);
        statusFilter->setInsertPolicy(QComboBox::NoInsert);
        statusFilter->move(QPoint(colWPosX.CalcPosX(QString("Status")), FILTER_QLINEEDIT_Y));
        statusFilter->setFont(font);
        statusFilter->setFixedWidth(STATUS_WIDTH);
        statusModel = new QSqlTableModel(this, dbInterface->GetDatabase());
        statusModel->setTable(STATUS_TABLE);
        statusFilter->setModel(statusModel);
        statusFilter->setModelColumn(STATUS_STATUS_POS);
        statusModel->select();

        anredeFilter = new ModQComboBox(this, this);
        anredeFilter->setEditable(true);
        anredeFilter->setInsertPolicy(QComboBox::NoInsert);
        anredeFilter->move(QPoint(colWPosX.CalcPosX(QString("Anrede")), FILTER_QLINEEDIT_Y));
        anredeFilter->setFont(font);
        anredeFilter->setFixedWidth(ANREDE_WIDTH);
        anredeModel = new QSqlTableModel(this, dbInterface->GetDatabase());
        anredeModel->setTable(ANREDE_TABLE);
        anredeFilter->setModel(anredeModel);
        anredeFilter->setModelColumn(ANREDE_ANREDE_POS);
        anredeModel->select();

        amtstitelFilter = new ModQComboBox(this, this);
        amtstitelFilter->setEditable(true);
        amtstitelFilter->setInsertPolicy(QComboBox::NoInsert);
        amtstitelFilter->move(QPoint(colWPosX.CalcPosX(QString("Amtstitel")), FILTER_QLINEEDIT_Y));
        amtstitelFilter->setFont(font);
        amtstitelFilter->setFixedWidth(AMTSTITEL_WIDTH);
        amtstitelModel = new QSqlTableModel(this, dbInterface->GetDatabase());
        amtstitelModel->setTable(AMTSTITEL_TABLE);
        amtstitelFilter->setModel(amtstitelModel);
        amtstitelFilter->setModelColumn(AMTSTITEL_AMTSTITEL_POS);
        amtstitelModel->select();

    }
    catch(std::bad_alloc exc)
    {
        errorMan.BailOut("Thrown std::bad_alloc exception", __FILE__, __LINE__, FAILURE);
    }

    //set tab order
    this->setTabOrder(IDFilter, statusFilter);
    this->setTabOrder(statusFilter, anredeFilter);
    this->setTabOrder(anredeFilter, amtstitelFilter);
    this->setTabOrder(amtstitelFilter, titelVorFilter);
    this->setTabOrder(titelVorFilter, titelNachFilter);
    this->setTabOrder(titelNachFilter, vornameFilter);
    this->setTabOrder(vornameFilter, nachnameFilter);
    this->setTabOrder(nachnameFilter, organisationFilter);
    this->setTabOrder(organisationFilter, strasseFilter);
    this->setTabOrder(strasseFilter, PLZFilter);
    this->setTabOrder(PLZFilter, ortFilter);
    this->setTabOrder(ortFilter, landFilter);
    //this->setTabOrder(landFilter, IDFilter);	//apparently circular tab ordering does not work in Qt! - this results in weird behavior

    //connect signal with slots
    QObject::connect(this->IDFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->titelVorFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->titelNachFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->vornameFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->nachnameFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->organisationFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->strasseFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->PLZFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->ortFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->landFilter, &ModQLineEdit::textEdited, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->statusFilter, &ModQComboBox::editTextChanged, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->anredeFilter, &ModQComboBox::editTextChanged, this, &AbonnentenSuche::FiltersChanged);
    QObject::connect(this->amtstitelFilter, &ModQComboBox::editTextChanged, this, &AbonnentenSuche::FiltersChanged);

    ResetFilters();
}

AbonnentenSuche::~AbonnentenSuche()
{
    delete IDFilter;
    delete titelVorFilter;
    delete titelNachFilter;
    delete vornameFilter;
    delete nachnameFilter;
    delete organisationFilter;
    delete strasseFilter;
    delete PLZFilter;
    delete ortFilter;
    delete landFilter;
    delete statusFilter;
    delete anredeFilter;
    delete amtstitelFilter;
    delete ui;
}

/**
 * @brief AbonnentenSuche::TableRowData::TableRowData Standard constructor without arguments
 */
AbonnentenSuche::TableRowData::TableRowData()
{
    this->ID = "";
    this->status = "";
    this->anrede = "";
    this->amtstitel = "";
    this->titelVor = "";
    this->titelNach = "";
    this->vorname = "";
    this->nachname = "";
    this->organisation = "";
    this->strasse = "";
    this->plz = "";
    this->ort = "";
    this->antoniusanzahl = "";
    this->zusatzinfo = "";
}
/**
 * @brief AbonnentenSuche::TableRowData Simple Constructor for a TableRowData struct
 * @param ID
 * @param status
 * @param anrede
 * @param amtstitel
 * @param titelVor
 * @param titelNach
 * @param organisation
 * @param strasse
 * @param plz
 * @param ort
 * @param antoniusanzahl
 * @param zusatzinfo
 */
AbonnentenSuche::TableRowData::TableRowData(QString ID, QString status, QString anrede, QString amtstitel, QString titelVor, QString titelNach, QString vorname, QString nachname, QString organisation, QString strasse, QString plz, QString ort, QString antoniusanzahl, QString zusatzinfo)
{
    this->ID = ID;
    this->status = status;
    this->anrede = anrede;
    this->amtstitel = amtstitel;
    this->titelVor = titelVor;
    this->titelNach = titelNach;
    this->vorname = vorname;
    this->nachname = nachname;
    this->organisation = organisation;
    this->strasse = strasse;
    this->plz = plz;
    this->ort = ort;
    this->antoniusanzahl = antoniusanzahl;
    this->zusatzinfo = zusatzinfo;
}

/**
 * @brief AbonnentenSuche::ModQLineEdit::ModQLineEdit Constructor for the from QLineEdit inherited class ModQLineEdit
 * @param parent QWidget that "owns" this object (passed on to base class)
 * @param outerClassInstance Instance of enclosing class object
 */
AbonnentenSuche::ModQLineEdit::ModQLineEdit(QWidget *parent, AbonnentenSuche *outerClassInstance) : QLineEdit(parent)
{
    this->outerClassInstance = outerClassInstance;
}
AbonnentenSuche::ModQLineEdit::~ModQLineEdit() {}

void AbonnentenSuche::ModQLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(outerClassInstance->HandleKeyEvents(event))
        QLineEdit::keyPressEvent(event);
}

/**
 * @brief AbonnentenSuche::ModQComboBox::ModQComboBox Constructor for the from QComboBox inherited class ModQComboBox
 * @param parent QWidget that "owns" this object (passed on to base class)
 * @param outerClassInstance Instance of enclosing class object
 */
AbonnentenSuche::ModQComboBox::ModQComboBox(QWidget *parent, AbonnentenSuche *outerClassInstance) : QComboBox(parent)
{
    this->outerClassInstance = outerClassInstance;
}
AbonnentenSuche::ModQComboBox::~ModQComboBox() {}

void AbonnentenSuche::ModQComboBox::keyPressEvent(QKeyEvent *event)
{
    if(outerClassInstance->HandleKeyEvents(event))
        QComboBox::keyPressEvent(event);
}

/**
 * @brief AbonnentenSuche::FiltersChanged Slot function that is called, whenever a filter (line edit or combobox) is changed
 * @details Also refreshes the models of the combo boxes!
 * @param text The new text that changed
 */
void AbonnentenSuche::FiltersChanged(const QString &text)
{
    if(prFilterChange == false)
    {
        QString sqlString = BuildQueryString();
        ExecuteQueryUpdateTable(sqlString);
    }
    return;
}

/**
 * @brief AbonnentenSuche::BuildQueryStringPart Builds part of an sql string for a query
 * @param sqlString The string to which to append an SQL statement
 * @param firstWhereClause States whether there already exsists a clause in the supplied string \sqlString
 * @param columnName Name of the column for which this clause implements a criteria
 * @param filterContent Content of the filter for the column \c columnName (line edit or combobox)
 * @param strictComparison If true searches for the exact string in \c filterContent, otherwise only looks for the substring \c filterContent
 */
void AbonnentenSuche::BuildQueryStringPart(QString& sqlString, bool& firstWhereClause, QString columnName, QString filterContent, bool strictComparison)
{
    if(!filterContent.isNull() && !filterContent.isEmpty())
    {
        if(firstWhereClause == true)
        {
            sqlString.append(" WHERE");
            firstWhereClause = false;
        }
        else
            sqlString.append(" AND");

        sqlString.append(QString(" (") + ABONNENTEN_TABLE + ".`");
        sqlString.append(columnName);
        if(strictComparison)
        {
            sqlString.append(QString("` LIKE \'"));
            sqlString.append(filterContent);
            sqlString.append(QString("\')"));
        }
        else
        {
            sqlString.append(QString("` LIKE \'%"));
            sqlString.append(filterContent);
            sqlString.append(QString("%\')"));
        }
    }
}


/**
 * @brief AbonnentenSuche::BuildQueryString Builds a query depending on the content of the filters (line edit and combobox elements on the search form)
 * @return Returns a QString containing an SQL query
 */
QString AbonnentenSuche::BuildQueryString(void)
{
    bool firstWhereClause = true;
    QString sqlString(SEARCH_TABLE_SQL_PREFIX);
    QString text;


    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ID, IDFilter->text(), true);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_TITELVOR, titelVorFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_TITELNACH, titelNachFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_VORNAME, vornameFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_NACHNAME, nachnameFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ORGANISATION, organisationFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_STRASSE, strasseFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_PLZALLGEMEIN, PLZFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ORTALLGEMEIN, ortFilter->text(), false);
    BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_LAND, landFilter->text(), false);
    ComboboxBuildQueryString(sqlString, statusFilter, ABONNENTEN_STATUS, firstWhereClause);
    ComboboxBuildQueryString(sqlString, anredeFilter, ABONNENTEN_ANREDE, firstWhereClause);
    ComboboxBuildQueryString(sqlString, amtstitelFilter, ABONNENTEN_AMTSTITEL, firstWhereClause);

    //set the sort order
    if(ui->checkBoxSortByChangeDate->isChecked() == true)
        sqlString.append(QString(" ORDER BY `" + ABONNENTEN_LETZTEAENDERUNG + "` DESC, `" + ABONNENTEN_NACHNAME + "` ASC, `" + ABONNENTEN_VORNAME + "` ASC"));
    else
        sqlString.append(" ORDER BY `" + ABONNENTEN_NACHNAME + "` ASC, `" + ABONNENTEN_VORNAME + "` ASC");

    return sqlString;
}


/**
 * @brief AbonnentenSuche::ComboboxBuildQueryString Builds a query part for \c sqlString given content from a combo box with an underlying QSqlTableModel
 * 		  This method assumes that the primary key element column of the comboboxes underlying table is called "ID"
 * @param sqlString SQL string for which to build a query part
 * @param comboBox Combo box with a QSqlTableModel
 * @param columnName Name of the "main" table's column
 * @param firstWhereClause States whether this is the first "WHERE-clause" in \c sqlString
 */
void AbonnentenSuche::ComboboxBuildQueryString(QString& sqlString, QComboBox *comboBox, QString columnName, bool& firstWhereClause)
{
    //if the current text in the combo box is part of its content table (comparison is case-insensitive)
    int indexOfCurrentText = comboBox->findText(comboBox->currentText(), Qt::MatchFixedString);
    if(indexOfCurrentText != -1)
    {
        //extract the ID of the currently set entry of the combo box
        //note that regarding the combo box we do not use its "current index", but the index its current text would have
        //intuitively these two should be the same, however Qt does not update combo box indices immediately or not at all, when the current text is empty ...
        QString ID = static_cast<QSqlTableModel*>(comboBox->model())->record(indexOfCurrentText).value(ID_POS).toString();
        BuildQueryStringPart(sqlString, firstWhereClause, columnName, ID, true);
    }
    return;
}


/**
 * @brief AbonnentenSuche::on_checkBoxSortByChangeDate_stateChanged This slot is activated when the state of the "SortByChangeDate" checkbox is changed
 * @note This slot was automatically created by the UI wizard
 * @param arg1
 */
void AbonnentenSuche::on_checkBoxSortByChangeDate_stateChanged(int arg1)
{
    FiltersChanged(nullptr);
}


/**
 * @brief Key Event Handler
 * @param event The key event, which is to be handled
 */
void AbonnentenSuche::keyPressEvent(QKeyEvent *event)
{
    if(HandleKeyEvents(event))
        QWidget::keyPressEvent(event);
}

/**
 * @brief HandleKeyEvents To be called inside the different keyPressEvent handlers
 * @param event key event to handle
 * @returns True if the event still needs to be handled or false otherwise
 */
bool AbonnentenSuche::HandleKeyEvents(QKeyEvent *event)
{
    bool returnValue = false;
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        ResetFilters();
    //all other events are processed by the base class's event handler
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_I)
        IDFilter->setFocus();
    else
        returnValue = true;

    return returnValue;
}

/**
 * @brief AbonnentenSuche::ResetFilters Resets all the filters (line edits and combo boxes)
 */
void AbonnentenSuche::ResetFilters(void)
{
    bool prFilterChangeOld = prFilterChange;
    prFilterChange = true;
    IDFilter->clear();
    titelVorFilter->clear();
    titelNachFilter->clear();
    vornameFilter->clear();
    nachnameFilter->clear();
    organisationFilter->clear();
    strasseFilter->clear();
    PLZFilter->clear();
    ortFilter->clear();
    landFilter->clear();

    statusFilter->clearEditText();
    anredeFilter->clearEditText();
    amtstitelFilter->clearEditText();
    statusModel->select();
    anredeModel->select();
    amtstitelModel->select();

    ui->checkBoxSortByChangeDate->setChecked(false);

    prFilterChange = prFilterChangeOld;
    FiltersChanged(nullptr);
    vornameFilter->setFocus();
    ResetTableViewSizes();
}

/**
 * @brief AbonnentenSuche::UpdateTableViewSizes Resets the width of the search table view and (re)sets the table headers
 */
void AbonnentenSuche::ResetTableViewSizes()
{
    ui->searchTable->setColumnWidth(0, ID_WIDTH);
    ui->searchTable->setColumnWidth(1, STATUS_WIDTH);
    ui->searchTable->setColumnWidth(2, ANREDE_WIDTH);
    ui->searchTable->setColumnWidth(3, AMTSTITEL_WIDTH);
    ui->searchTable->setColumnWidth(4, TITEL_VOR_WIDTH);
    ui->searchTable->setColumnWidth(5, TITEL_NACH_WIDTH);
    ui->searchTable->setColumnWidth(6, VORNAME_WIDTH);
    ui->searchTable->setColumnWidth(7, NACHNAME_WIDTH);
    ui->searchTable->setColumnWidth(8, ORGANISATION_WIDTH);
    ui->searchTable->setColumnWidth(9, STRASSE_WIDTH);
    ui->searchTable->setColumnWidth(10, PLZ_WIDTH);
    ui->searchTable->setColumnWidth(11, ORT_WIDTH);
    ui->searchTable->setColumnWidth(12, LAND_WIDTH);
    ui->searchTable->setColumnWidth(13, ANTONIUSANZAHL_WIDTH);
    ui->searchTable->setColumnHidden(14, true);
    ui->searchTable->setColumnHidden(15, true);
    ui->searchTable->setColumnHidden(16, true);

    //(re)set table headers (the QSqlQueryModel resets the headers to the column names)
    searchTableModel->setHeaderData(0, Qt::Horizontal, "ID");
    searchTableModel->setHeaderData(1, Qt::Horizontal, "Status");
    searchTableModel->setHeaderData(2, Qt::Horizontal, "Anrede");
    searchTableModel->setHeaderData(3, Qt::Horizontal, "Amtstitel");
    searchTableModel->setHeaderData(4, Qt::Horizontal, "Titel vorgestellt");
    searchTableModel->setHeaderData(5, Qt::Horizontal, "Titel nachgestellt");
    searchTableModel->setHeaderData(6, Qt::Horizontal, "Vorname");
    searchTableModel->setHeaderData(7, Qt::Horizontal, "Nachname");
    searchTableModel->setHeaderData(8, Qt::Horizontal, "Organisation");
    searchTableModel->setHeaderData(9, Qt::Horizontal, "Straße");
    searchTableModel->setHeaderData(10, Qt::Horizontal, "Plz");
    searchTableModel->setHeaderData(11, Qt::Horizontal, "Ort");
    searchTableModel->setHeaderData(12, Qt::Horizontal, "Land");
    searchTableModel->setHeaderData(13, Qt::Horizontal, "Antoniusanzahl");
}

/**
 * @brief AbonnentenSuche::ExecuteQueryUpdateTable Executes the query and displays the results in the corresponding table widget
 * @param sqlString QString containing the SQL query
 */
void AbonnentenSuche::ExecuteQueryUpdateTable(QString sqlString)
{
    searchTableModel->setQuery(sqlString);
    UpdateLCDNum();
    ui->searchTable->show();
}


QString AbonnentenSuche::GetStatusName(QString statusID)
{
    return dbInterface->GetNameFromID(STATUS_TABLE, statusID);
}
QString AbonnentenSuche::GetAnredeName(QString  anredeID)
{
    return dbInterface->GetNameFromID(ANREDE_TABLE, anredeID);
}
QString AbonnentenSuche::GetAmtstitelName(QString amtstitelID)
{
    return dbInterface->GetNameFromID(AMTSTITEL_TABLE, amtstitelID);
}

void AbonnentenSuche::UpdateLCDNum()
{
    ui->lcdNumTableRows->display(searchTableModel->rowCount());
    if(ui->lcdNumTableRows->intValue() == 0)
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::red));
    else
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::green));
    return;
}

/**
 * @brief AbonnentenSuche::on_tableView_clicked Slot function for when the table view object is clicked
 * @param index
 */
void AbonnentenSuche::on_searchTable_clicked(const QModelIndex &index)
{
    if(index.column() == ABONNENTEN_SUCHE_CLICK_COLUMN)
    {
        //get the Abonnenten widget from our parent (the QTabWidget)
        Abonnenten *abonnentenWidget = static_cast<Abonnenten*>(static_cast<QTabWidget*>(parent)->widget(ABONNENTEN_TAB));
        if(abonnentenWidget == nullptr)
        {
            errorMan.BailOut("Error, parent->widget() returned NULL pointer - when trying to retrieve the Abonnenten widget from our parent QTabWidget", __FILE__, __LINE__, FAILURE);
        }
        unsigned int selectedID = searchTableModel->data(index).toUInt();
        abonnentenWidget->SetActiveID(selectedID);
        abonnentenWidget->LoadActiveRecord();
        static_cast<QTabWidget*>(parent)->setCurrentIndex(ABONNENTEN_TAB);
    }
}


/**
 * @brief AbonnentenSuche::on_exportButton_clicked Slot function for when the export button is clicked
 * 		  Starts the export routine
 */
void AbonnentenSuche::on_exportButton_clicked()
{
    ExportRoutine();
}

/**
 * @brief AbonnentenSuche::ExportRoutine Starts the export for the "Druckerei"
 * @details Creates 4 .csv files consisting of only active subscribers of the Antonius magazine split as follows:
 * 			.) Inland, Brief (Antonius Anzahl = 1)
 * 			.) Inland, Paket (Antonius Anzahl > 1)
 * 			.) Ausland, Brief (Antonius Anzahl = 1)
 * 			.) Ausland, Paket (Antonius Anzahl > 1)
 */
void AbonnentenSuche::ExportRoutine(void)
{
    QSqlQuery query(dbInterface->GetDatabase());
    QString sqlStringInlandLetter = EXPORT_SQL_PREFIX +
        ABONNENTEN_LAND + " = 'A' AND " +
        ABONNENTEN_ANTONIUSANZAHL + " = '1'";
    QString sqlStringAuslandLetter = EXPORT_SQL_PREFIX +
        ABONNENTEN_LAND + " <> 'A' AND " +
        ABONNENTEN_ANTONIUSANZAHL + " = '1'";
    QString sqlStringInlandParcel = EXPORT_SQL_PREFIX +
        ABONNENTEN_LAND + " = 'A' AND " +
        ABONNENTEN_ANTONIUSANZAHL + " > '1'";
    QString sqlStringAuslandParcel = EXPORT_SQL_PREFIX +
        ABONNENTEN_LAND + " <> 'A' AND " +
        ABONNENTEN_ANTONIUSANZAHL + " > '1'";

    QString exportDirectory = QFileDialog::getExistingDirectory(this, "Export Directory", "./", QFileDialog::Option::ShowDirsOnly);
    exportDirectory = exportDirectory + "/";
    WriteExportQueryOutputToCSVFile(exportDirectory + QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + INLAND_LETTER_FILENAME, sqlStringInlandLetter, INLAND_LETTER_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(exportDirectory + QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + AUSLAND_LETTER_FILENAME, sqlStringAuslandLetter, AUSLAND_LETTER_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(exportDirectory + QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + INLAND_PARCEL_FILENAME, sqlStringInlandParcel, INLAND_PARCEL_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(exportDirectory + QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + AUSLAND_PARCEL_FILENAME, sqlStringAuslandParcel, AUSLAND_PARCEL_NUMBER_OF_COLUMNS);
    QMessageBox::information(this, "Export", "Export has been successful!", QMessageBox::Ok, QMessageBox::Ok);
}

/**
 * @brief AbonnentenSuche::WriteExportQueryOutputToCSVFile Writes the result of an SQL query to a file formatted as .csv file
 * @details The columns are separated by ";"
 * 			Hence it replaces all ";" by "," and all "\n" and "\r" by " "
 * @param pathFileName The path including the name of the .csv file
 * @param queryString QString containing the SQL specification of the query
 * @param numberOfColumns The number of columns to extract from the query
 */
void AbonnentenSuche::WriteExportQueryOutputToCSVFile(QString pathFileName, QString queryString, unsigned int numberOfColumns)
{
    QFile file(pathFileName, this);
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadWrite))
    {
        qInfo() << "Could not open file " << pathFileName;
        errorMan.BailOut("Error could not open " + pathFileName.toLocal8Bit(), __FILE__, __LINE__, FAILURE);
    }

    QSqlQuery query(dbInterface->GetDatabase());
    if(query.exec(queryString) == false)
    {
        qInfo() << query.lastError().text();
        qInfo() << "queryString: " + queryString;
        errorMan.BailOut("Error with query.exec()\nqueryString: " + queryString.toLocal8Bit() + "\n" + query.lastError().text().toLocal8Bit(), __FILE__, __LINE__, FAILURE);
    }
    //write the horizontal header of the .csv file
    file.write(
    ABONNENTEN_ZAHLUNGSREFERENZ_EXPORT ";"
    ABONNENTEN_ANREDE_EXPORT ";"
    ABONNENTEN_AMTSTITEL_EXPORT ";"
    ABONNENTEN_TITELVOR_EXPORT ";"
    ABONNENTEN_VORNAME_EXPORT ";"
    ABONNENTEN_NACHNAME_EXPORT ";"
    ABONNENTEN_TITELNACH_EXPORT ";"
    ABONNENTEN_ORGANISATION_EXPORT ";"
    ABONNENTEN_STRASSE_EXPORT ";"
    ABONNENTEN_PLZALLGEMEIN_EXPORT ";"
    ABONNENTEN_ORTALLGEMEIN_EXPORT ";"
    ABONNENTEN_LAND_EXPORT ";"
    ABONNENTEN_ANTONIUSANZAHL_EXPORT ";"
    ABONNENTEN_ZUSATZINFO_EXPORT ";\r\n");
    QString exportString;
    while(query.next())
    {
        for(int z = 0; static_cast<unsigned int>(z) < numberOfColumns; z++)
        {
            //print a "Zahlungsreferenz" instead of the pure ID, which is ID+ZAHLUNGSREFERENCE_OFFSET
            if(z == 0)
                exportString = QString::number(query.value(z).toLongLong() + ZAHLUNGSREFERENCE_OFFSET);
            else
                //replace ";" by "," and "\n" and "\r" by " " (each)
                exportString = query.value(z).toString().replace(";", ",").replace("\n", " ").replace("\r", " ");
            file.write(exportString.toUtf8());
            file.write(";");
        }
        file.write("\r\n");
    }
    file.flush();
    file.close();
}

/**
 * @brief AbonnentenSuche::on_backupButton_clicked Slot function for when the backup button is clicked
 */
void AbonnentenSuche::on_backupButton_clicked()
{
    BackupRoutine();
}

/**
 * @brief BackupRoutine Creates a backup of all tables of the database in a directory selected by the user
 * @details The exported files from this backup are in .csv format
 */
void AbonnentenSuche::BackupRoutine(void)
{
    QString backupDirectoryFile = QFileDialog::getSaveFileName(this, "Backup Directory", "./antonius_backup.sql", "SQL files (*.sql)");
    QString password = QInputDialog::getText(nullptr, "Password", "Please enter the password", QLineEdit::Password, "Please enter the password");
    std::system("mysqldump -u Sal -p" + password.toLocal8Bit() + " antonius > \"" + backupDirectoryFile.toLocal8Bit());
}



/**
 * @brief AbonnentenSuche::RefreshComboboxModels Reloads the content of the combo box filters
 * @details Calling select() on the model of a combo box resets the combo box's content!
 */
void AbonnentenSuche::RefreshComboboxModels()
{
    RefreshComboBoxModel(statusFilter);
    RefreshComboBoxModel(anredeFilter);
    RefreshComboBoxModel(amtstitelFilter);
}

/**
 * @brief AbonnentenSuche::RefreshComboBoxModel A function to reload the contents of a combo box.
 * Tries to restore the old position of the combo box if it is still in the table of the combo box content
 * @details Works only for combo boxes, whose underlying model is of type QSqlTableModel!
 * @param comboBox The combo box, whose content table should be reloaded
 */
void AbonnentenSuche::RefreshComboBoxModel(QComboBox *comboBox)
{
    //Since calling select on a combo box's model resets the current text/selected element, we have to temporarily save and restore it
    //if the combo box's current edit line is not empty
    bool prFilterChangeOld = prFilterChange;
    prFilterChange = true;
    if(comboBox->currentIndex() != -1)
    {
        //Save the current ID
        int ID = static_cast<QSqlTableModel*>(comboBox->model())->record(comboBox->currentIndex()).value(ID_POS).toInt();
        static_cast<QSqlTableModel*>(comboBox->model())->select();
        //if the combo box was not empty
        if(ID != 0)
        {
            for(int index = 0; index < comboBox->count(); index++)
            {
                if(static_cast<QSqlTableModel*>(comboBox->model())->record(index).value(ID_POS).toInt() == ID)
                {
                    comboBox->setCurrentIndex(index);
                    break;
                }
            }
        }
    }
    else
    {
        static_cast<QSqlTableModel*>(comboBox->model())->select();
    }
    prFilterChange = prFilterChangeOld;
}
