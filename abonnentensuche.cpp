#include "abonnentensuche.h"
#include "ui_abonnentensuche.h"
#include "columnwidthposx.h"

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
        " WHERE " +
        ABONNENTEN_STATUS + " = '0' AND ");

AbonnentenSuche::AbonnentenSuche(DBInterface *dbInterface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbonnentenSuche)
{
    ui->setupUi(this);
    this->dbInterface = dbInterface;
    this->parent = parent;

    prFilterChange = false;
    /********** set the horizontal headers for the table **********/
    ui->tableWidget->setColumnCount(INLAND_SUCHE_COLUMN_COUNT);

    ui->tableWidget->setRowCount(0);		//initially the table is empty (there are no rows)

    ui->tableWidget->verticalHeader()->hide();

    //this object is used to correctly position the "line edit" objects (filters) over the corresponding columns
    ColumnWidthPosX colWPosX;

    //initialization of table headers
    colWPosX.Append(ID_WIDTH, QString("ID"));
    tableHeaderList.append(QString("ID"));
    colWPosX.Append(STATUS_WIDTH, QString("Status"));
    tableHeaderList.append(QString("Status"));
    colWPosX.Append(ANREDE_WIDTH, QString("Anrede"));
    tableHeaderList.append(QString("Anrede"));
    colWPosX.Append(AMTSTITEL_WIDTH, QString("Amtstitel"));
    tableHeaderList.append(QString("Amtstitel"));
    colWPosX.Append(TITEL_VOR_WIDTH, QString("Titel vorgestellt"));
    tableHeaderList.append(QString("Titel vorgestellt"));
    colWPosX.Append(TITEL_NACH_WIDTH, QString("Titel nachgestellt"));
    tableHeaderList.append(QString("Titel nachgestellt"));
    colWPosX.Append(VORNAME_WIDTH, QString("Vorname"));
    tableHeaderList.append(QString("Vorname"));
    colWPosX.Append(NACHNAME_WIDTH, QString("Nachname"));
    tableHeaderList.append(QString("Nachname"));
    colWPosX.Append(ORGANISATION_WIDTH, QString("Organisation"));
    tableHeaderList.append(QString("Organisation"));
    colWPosX.Append(STRASSE_WIDTH, QString("Straße"));
    tableHeaderList.append(QString("Straße"));
    colWPosX.Append(PLZ_WIDTH, QString("Plz"));
    tableHeaderList.append(QString("Plz"));
    colWPosX.Append(ORT_WIDTH, QString("Ort"));
    tableHeaderList.append(QString("Ort"));
    colWPosX.Append(ANTONIUSANZAHL_WIDTH, QString("Antoniusanzahl"));
    tableHeaderList.append(QString("Antoniusanzahl"));
    colWPosX.Append(ZUSATZINFO_WIDTH, QString("Zusatzinfo"));
    tableHeaderList.append(QString("Zusatzinfo"));

    ui->tableWidget->setHorizontalHeaderLabels(tableHeaderList);


    ui->tableWidget->setColumnWidth(0, ID_WIDTH);
    ui->tableWidget->setColumnWidth(1, STATUS_WIDTH);
    ui->tableWidget->setColumnWidth(2, ANREDE_WIDTH);
    ui->tableWidget->setColumnWidth(3, AMTSTITEL_WIDTH);
    ui->tableWidget->setColumnWidth(4, TITEL_VOR_WIDTH);
    ui->tableWidget->setColumnWidth(5, TITEL_NACH_WIDTH);
    ui->tableWidget->setColumnWidth(6, VORNAME_WIDTH);
    ui->tableWidget->setColumnWidth(7, NACHNAME_WIDTH);
    ui->tableWidget->setColumnWidth(8, ORGANISATION_WIDTH);
    ui->tableWidget->setColumnWidth(9, STRASSE_WIDTH);
    ui->tableWidget->setColumnWidth(10, PLZ_WIDTH);
    ui->tableWidget->setColumnWidth(11, ORT_WIDTH);
    ui->tableWidget->setColumnWidth(12, ANTONIUSANZAHL_WIDTH);
    ui->tableWidget->setColumnWidth(13, ZUSATZINFO_WIDTH);
    QFont font(QString("Calibri"), DEFAULT_FONT_SIZE);

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

    ui->tableWidget->update();

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
    delete statusFilter;
    delete anredeFilter;
    delete amtstitelFilter;
    delete ui;
    tableHeaderList.clear();
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
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        outerClassInstance->ResetFilters();
    //all other events are processed by the base class's event handler
    else
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
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        outerClassInstance->ResetFilters();
    //all other events are processed by the base class's event handler
    else
        QComboBox::keyPressEvent(event);
}


/**
 * @brief AbonnentenSuche::ClearTable Clears the contents of the table widget
 */
void AbonnentenSuche::ClearTable(void)
{
    //ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->update();
    UpdateLCDNum();
    return;
}


/**
 * @brief AbonnentenSuche::AddRow Adds a row to the table widget of this form
 * @param tableRowData Data to fill each column entry of the row with
 * @param update Whether or not the corresponding table widget should be updated to make the changes instantly visible or not (for multiple successive updates setting this to false might improve performance)
 */
void AbonnentenSuche::AddRow(TableRowData tableRowData, bool update)
{
    int rowCount = ui->tableWidget->rowCount();

    try
    {
        ui->tableWidget->insertRow(rowCount);

        ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(tableRowData.ID));
        ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(tableRowData.status));
        ui->tableWidget->setItem(rowCount, 2, new QTableWidgetItem(tableRowData.anrede));
        ui->tableWidget->setItem(rowCount, 3, new QTableWidgetItem(tableRowData.amtstitel));
        ui->tableWidget->setItem(rowCount, 4, new QTableWidgetItem(tableRowData.titelVor));
        ui->tableWidget->setItem(rowCount, 5, new QTableWidgetItem(tableRowData.titelNach));
        ui->tableWidget->setItem(rowCount, 6, new QTableWidgetItem(tableRowData.vorname));
        ui->tableWidget->setItem(rowCount, 7, new QTableWidgetItem(tableRowData.nachname));
        ui->tableWidget->setItem(rowCount, 8, new QTableWidgetItem(tableRowData.organisation));
        ui->tableWidget->setItem(rowCount, 9, new QTableWidgetItem(tableRowData.strasse));
        ui->tableWidget->setItem(rowCount, 10, new QTableWidgetItem(tableRowData.plz));
        ui->tableWidget->setItem(rowCount, 11, new QTableWidgetItem(tableRowData.ort));
        ui->tableWidget->setItem(rowCount, 12, new QTableWidgetItem(tableRowData.antoniusanzahl));
        ui->tableWidget->setItem(rowCount, 13, new QTableWidgetItem(tableRowData.zusatzinfo));
    }
    catch(std::bad_alloc exc)
    {
        errorMan.BailOut("Thrown std::bad_alloc exception", __FILE__, __LINE__, FAILURE);
    }

    if(update)
    {
        ui->tableWidget->update();
        UpdateLCDNum();
    }

    return;
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
    if(firstWhereClause == true)
    {
        sqlString.append(" WHERE");
        firstWhereClause = false;
    }
    else
        sqlString.append(" AND");

    sqlString.append(QString(" (`"));
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
    return;
}


/**
 * @brief AbonnentenSuche::BuildQueryString Builds a query depending on the content of the filters (line edit and combobox elements on the search form)
 * @return Returns a QString containing an SQL query
 */
QString AbonnentenSuche::BuildQueryString(void)
{
    bool firstWhereClause = true;
    QString sqlString("SELECT * FROM `" + ABONNENTEN_TABLE + "` ");
    QString text;


    text = IDFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ID, text, true);

    text = titelVorFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_TITELVOR, text, false);

    text = titelNachFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_TITELNACH, text, false);

    text = vornameFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_VORNAME, text, false);

    text = nachnameFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_NACHNAME, text, false);

    text = organisationFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ORGANISATION, text, false);

    text = strasseFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_STRASSE, text, false);

    text = PLZFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_PLZALLGEMEIN, text, false);

    text = ortFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, ABONNENTEN_ORTALLGEMEIN, text, false);

    text = statusFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
        ComboboxBuildQueryString(sqlString, statusFilter, ABONNENTEN_STATUS, firstWhereClause);

    text = anredeFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
        ComboboxBuildQueryString(sqlString, anredeFilter, ABONNENTEN_ANREDE, firstWhereClause);

    text = amtstitelFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
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

    QString ID = static_cast<QSqlTableModel*>(comboBox->model())->record(comboBox->currentIndex()).value(ID_POS).toString();
    BuildQueryStringPart(sqlString, firstWhereClause, columnName, ID, true);
    return;
}


/**
 * @brief AbonnentenSuche::on_checkBoxSortByChangeDate_stateChanged This slot is activated when the state of the "SortByChangeDate" checkbox is changed
 * @note This slot was automatically created by the UI wizard
 * @param arg1
 */
void AbonnentenSuche::on_checkBoxSortByChangeDate_stateChanged(int arg1)
{
    QString sqlString = BuildQueryString();
    ExecuteQueryUpdateTable(sqlString);
}


/**
 * @brief Key Event Handler
 * @param event The key event, which is to be handled
 */
void AbonnentenSuche::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        ResetFilters();
    //all other events are processed by the base class's event handler
    else
        QWidget::keyPressEvent(event);
}

/**
 * @brief AbonnentenSuche::ResetFilters Resets all the filters (line edits and combo boxes)
 */
void AbonnentenSuche::ResetFilters(void)
{
    bool prFilterChangeOld = prFilterChange;
    prFilterChange = true;
    ClearTable();
    IDFilter->clear();
    titelVorFilter->clear();
    titelNachFilter->clear();
    vornameFilter->clear();
    nachnameFilter->clear();
    organisationFilter->clear();
    strasseFilter->clear();
    PLZFilter->clear();
    ortFilter->clear();

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
}

/**
 * @brief AbonnentenSuche::ExecuteQueryUpdateTable Executes the query and displays the results in the corresponding table widget
 * @param sqlString QString containing the SQL query
 */
void AbonnentenSuche::ExecuteQueryUpdateTable(QString sqlString)
{
    QSqlQuery query(dbInterface->GetDatabase());

    ClearTable();

    if(query.exec(sqlString) == false)
    {
        qInfo() << query.lastError().text();
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with query.exec\n", __FILE__, __LINE__, FAILURE);
    }
    while(query.next())
    {
        TableRowData tableRowData(
            (query.value(0) == false) ? QString("") : query.value(0).toString(),
            (query.value(18) == false) ? QString("") : GetStatusName(query.value(18).toString()),
            (query.value(1) == false) ? QString("") : GetAnredeName(query.value(1).toString()),
            (query.value(4) == false) ? QString("") : GetAmtstitelName(query.value(4).toString()),
            (query.value(2) == false) ? QString("") : query.value(2).toString(),
            (query.value(3) == false) ? QString("") : query.value(3).toString(),
            (query.value(6) == false) ? QString("") : query.value(6).toString(),
            (query.value(5) == false) ? QString("") : query.value(5).toString(),
            (query.value(7) == false) ? QString("") : query.value(7).toString(),
            (query.value(8) == false) ? QString("") : query.value(8).toString(),
            (query.value(12) == false) ? QString("") : query.value(12).toString(),
            (query.value(13) == false) ? QString("") : query.value(13).toString(),
            (query.value(14) == false) ? QString("") : query.value(14).toString(),
            (query.value(22) == false) ? QString("") : query.value(22).toString()
        );
        AddRow(tableRowData, false);
    }
    ui->tableWidget->update();
    UpdateLCDNum();
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
    ui->lcdNumTableRows->display(ui->tableWidget->rowCount());
    if(ui->lcdNumTableRows->intValue() == 0)
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::red));
    else
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::green));
    return;
}

/**
 * @brief AbonnentenSuche::on_tableWidget_cellClicked Slot function for when a cell on the table widget is clicked
 * @param row Row that was clicked
 * @param column Column that was clicked
 */
void AbonnentenSuche::on_tableWidget_cellClicked(int row, int column)
{
    if(column == ABONNENTEN_SUCHE_CLICK_COLUMN)
    {
        QTableWidgetItem *tableWidgetItem = ui->tableWidget->item(row, column);
        if(tableWidgetItem == nullptr)
        {
            errorMan.BailOut("Error, item() returned NULL pointer", __FILE__, __LINE__, FAILURE);
        }
        Abonnenten *abonnentenWidget = static_cast<Abonnenten*>(static_cast<QTabWidget*>(parent)->widget(ABONNENTEN_TAB));
        if(abonnentenWidget == nullptr)
        {
            errorMan.BailOut("Error, widget() returned NULL pointer", __FILE__, __LINE__, FAILURE);
        }
        unsigned int selectedID = tableWidgetItem->text().toUInt();
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

    WriteExportQueryOutputToCSVFile(QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + INLAND_LETTER_FILENAME, sqlStringInlandLetter, INLAND_LETTER_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + AUSLAND_LETTER_FILENAME, sqlStringAuslandLetter, AUSLAND_LETTER_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + INLAND_PARCEL_FILENAME, sqlStringInlandParcel, INLAND_PARCEL_NUMBER_OF_COLUMNS);
    WriteExportQueryOutputToCSVFile(QDate::currentDate().toString(DATABASE_DATE_FORMAT) + " - " + AUSLAND_PARCEL_FILENAME, sqlStringAuslandParcel, AUSLAND_PARCEL_NUMBER_OF_COLUMNS);
    QMessageBox::information(this, "Export", "Export has been successful!", QMessageBox::Ok, QMessageBox::Ok);
}

/**
 * @brief AbonnentenSuche::WriteExportQueryOutputToCSVFile Writes the result of an SQL query to a file formatted as .csv file
 * @param fileName The name of the .csv file
 * @param queryString QString containing the SQL specification of the query
 * @param numberOfColumns The number of columns to extract from the query
 */
void AbonnentenSuche::WriteExportQueryOutputToCSVFile(QString fileName, QString queryString, unsigned int numberOfColumns)
{
    QFile file(fileName, this);
    if(!file.open(QIODevice::WriteOnly | QIODevice::ReadWrite))
    {
        qInfo() << "Could not open file" << fileName;
        errorMan.BailOut("Error could not open" + fileName.toLocal8Bit(), __FILE__, __LINE__, FAILURE);
        return;
    }

    QSqlQuery query(dbInterface->GetDatabase());
    query.exec(queryString);
    while(query.next())
    {
        for(int z = 0; static_cast<unsigned int>(z) < numberOfColumns; z++)
        {
            file.write(query.value(z).toByteArray());
            file.write(",");
        }
        file.write("\r\n");
    }
    file.flush();
    file.close();
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
