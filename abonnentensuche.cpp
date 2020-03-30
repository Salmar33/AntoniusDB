#include "abonnentensuche.h"
#include "ui_abonnentensuche.h"
#include "columnwidthposx.h"

//for testing only
#include <QThread>

AbonnentenInlandSuche::AbonnentenInlandSuche(DBInterface *dbInterface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbonnentenInlandSuche)
{
    ui->setupUi(this);
    this->dbInterface = dbInterface;
    this->parent = parent;

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

        TitelVorFilter = new ModQLineEdit(this, this);
        TitelVorFilter->move(QPoint(colWPosX.CalcPosX(QString("Titel vorgestellt")), FILTER_QLINEEDIT_Y));
        TitelVorFilter->setFont(font);
        TitelVorFilter->setFixedWidth(TITEL_VOR_WIDTH);

        TitelNachFilter = new ModQLineEdit(this, this);
        TitelNachFilter->move(QPoint(colWPosX.CalcPosX(QString("Titel nachgestellt")), FILTER_QLINEEDIT_Y));
        TitelNachFilter->setFont(font);
        TitelNachFilter->setFixedWidth(TITEL_NACH_WIDTH);

        VornameFilter = new ModQLineEdit(this, this);
        VornameFilter->move(QPoint(colWPosX.CalcPosX(QString("Vorname")), FILTER_QLINEEDIT_Y));
        VornameFilter->setFont(font);
        VornameFilter->setFixedWidth(VORNAME_WIDTH);

        NachnameFilter = new ModQLineEdit(this, this);
        NachnameFilter->move(QPoint(colWPosX.CalcPosX(QString("Nachname")), FILTER_QLINEEDIT_Y));
        NachnameFilter->setFont(font);
        NachnameFilter->setFixedWidth(NACHNAME_WIDTH);

        OrganisationFilter = new ModQLineEdit(this, this);
        OrganisationFilter->move(QPoint(colWPosX.CalcPosX(QString("Organisation")), FILTER_QLINEEDIT_Y));
        OrganisationFilter->setFont(font);
        OrganisationFilter->setFixedWidth(ORGANISATION_WIDTH);

        StrasseFilter = new ModQLineEdit(this, this);
        StrasseFilter->move(QPoint(colWPosX.CalcPosX(QString("Straße")), FILTER_QLINEEDIT_Y));
        StrasseFilter->setFont(font);
        StrasseFilter->setFixedWidth(STRASSE_WIDTH);

        PLZFilter = new ModQLineEdit(this, this);
        PLZFilter->move(QPoint(colWPosX.CalcPosX(QString("Plz")), FILTER_QLINEEDIT_Y));
        PLZFilter->setFont(font);
        PLZFilter->setFixedWidth(PLZ_WIDTH);

        OrtFilter = new ModQLineEdit(this, this);
        OrtFilter->move(QPoint(colWPosX.CalcPosX(QString("Ort")), FILTER_QLINEEDIT_Y));
        OrtFilter->setFont(font);
        OrtFilter->setFixedWidth(ORT_WIDTH);

        StatusFilter = new ModQComboBox(this, this);
        StatusFilter->move(QPoint(colWPosX.CalcPosX(QString("Status")), FILTER_QLINEEDIT_Y));
        StatusFilter->setFont(font);
        StatusFilter->setFixedWidth(STATUS_WIDTH);

        AnredeFilter = new ModQComboBox(this, this);
        AnredeFilter->move(QPoint(colWPosX.CalcPosX(QString("Anrede")), FILTER_QLINEEDIT_Y));
        AnredeFilter->setFont(font);
        AnredeFilter->setFixedWidth(ANREDE_WIDTH);

        AmtstitelFilter = new ModQComboBox(this, this);
        AmtstitelFilter->move(QPoint(colWPosX.CalcPosX(QString("Amtstitel")), FILTER_QLINEEDIT_Y));
        AmtstitelFilter->setFont(font);
        AmtstitelFilter->setFixedWidth(AMTSTITEL_WIDTH);

    }
    catch(std::bad_alloc exc)
    {
        errorMan.BailOut("Thrown std::bad_alloc exception", __FILE__, __LINE__, FAILURE);
    }

    ui->tableWidget->update();

    //connect signal with slots
    QObject::connect(this->IDFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->TitelVorFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->TitelNachFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->VornameFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->NachnameFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->OrganisationFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->StrasseFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->PLZFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->OrtFilter, &ModQLineEdit::textEdited, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->StatusFilter, &ModQComboBox::editTextChanged, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->AnredeFilter, &ModQComboBox::editTextChanged, this, &AbonnentenInlandSuche::FiltersChanged);
    QObject::connect(this->AmtstitelFilter, &ModQComboBox::editTextChanged, this, &AbonnentenInlandSuche::FiltersChanged);

    ResetFilters();
}

AbonnentenInlandSuche::~AbonnentenInlandSuche()
{
    delete IDFilter;
    delete TitelVorFilter;
    delete TitelNachFilter;
    delete VornameFilter;
    delete NachnameFilter;
    delete OrganisationFilter;
    delete StrasseFilter;
    delete PLZFilter;
    delete OrtFilter;
    delete StatusFilter;
    delete AnredeFilter;
    delete AmtstitelFilter;
    delete ui;
    tableHeaderList.clear();
}

/**
 * @brief AbonnentenInlandSuche::TableRowData::TableRowData Standard constructor without arguments
 */
AbonnentenInlandSuche::TableRowData::TableRowData()
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
 * @brief AbonnentenInlandSuche::TableRowData Simple Constructor for a TableRowData struct
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
AbonnentenInlandSuche::TableRowData::TableRowData(QString ID, QString status, QString anrede, QString amtstitel, QString titelVor, QString titelNach, QString vorname, QString nachname, QString organisation, QString strasse, QString plz, QString ort, QString antoniusanzahl, QString zusatzinfo)
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
 * @brief AbonnentenInlandSuche::ModQLineEdit::ModQLineEdit Constructor for the from QLineEdit inherited class ModQLineEdit
 * @param parent QWidget that "owns" this object (passed on to base class)
 * @param outerClassInstance Instance of enclosing class object
 */
AbonnentenInlandSuche::ModQLineEdit::ModQLineEdit(QWidget *parent, AbonnentenInlandSuche *outerClassInstance) : QLineEdit(parent)
{
    this->outerClassInstance = outerClassInstance;
}
AbonnentenInlandSuche::ModQLineEdit::~ModQLineEdit() {}

void AbonnentenInlandSuche::ModQLineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        outerClassInstance->ResetFilters();
    //all other events are processed by the base class's event handler
    else
        QLineEdit::keyPressEvent(event);
}

/**
 * @brief AbonnentenInlandSuche::ModQComboBox::ModQComboBox Constructor for the from QComboBox inherited class ModQComboBox
 * @param parent QWidget that "owns" this object (passed on to base class)
 * @param outerClassInstance Instance of enclosing class object
 */
AbonnentenInlandSuche::ModQComboBox::ModQComboBox(QWidget *parent, AbonnentenInlandSuche *outerClassInstance) : QComboBox(parent)
{
    this->outerClassInstance = outerClassInstance;
}
AbonnentenInlandSuche::ModQComboBox::~ModQComboBox() {}

void AbonnentenInlandSuche::ModQComboBox::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        outerClassInstance->ResetFilters();
    //all other events are processed by the base class's event handler
    else
        QComboBox::keyPressEvent(event);
}


/**
 * @brief AbonnentenInlandSuche::ClearTable Clears the contents of the table widget
 */
void AbonnentenInlandSuche::ClearTable(void)
{
    //ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->update();
    UpdateLCDNum();
    return;
}


/**
 * @brief AbonnentenInlandSuche::AddRow Adds a row to the table widget of this form
 * @param tableRowData Data to fill each column entry of the row with
 * @param update Whether or not the corresponding table widget should be updated to make the changes instantly visible or not (for multiple successive updates setting this to false might improve performance)
 */
void AbonnentenInlandSuche::AddRow(TableRowData tableRowData, bool update)
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
 * @brief AbonnentenInlandSuche::AddRow Adds a test row
 */
void AbonnentenInlandSuche::AddRowTest(void)
{
    TableRowData tableRowData(
                QString("0"),
                QString("G"),
                QString("Herrn"),
                QString("Prof."),
                QString("Dr."),
                QString("PhD"),
                QString("Max"),
                QString("Mustermann"),
                QString("Hoola Hoop Corp."),
                QString("Gangsta Street 69"),
                QString("1234"),
                QString("Wien"),
                QString("1"),
                QString("Wants cookies")
                );
    AddRow(tableRowData, true);
}

/**
 * @brief Just for testing
 */
void AbonnentenInlandSuche::on_pushButton_clicked()
{
    for(int z = 0; z < 10000; z++)
    {
        AddRowTest();
    }
}

/**
 * @brief Just for testing
 */
void AbonnentenInlandSuche::on_pushButton_2_clicked()
{
    ClearTable();
}

/**
 * @brief AbonnentenInlandSuche::FiltersChanged Slot function that is called, whenever a filter (line edit or combobox) is changed
 * @param text The new text that changed
 */
void AbonnentenInlandSuche::FiltersChanged(const QString &text)
{
    QString sqlString = BuildQueryString();
    ExecuteQueryUpdateTable(sqlString);
    return;
}

/**
 * @brief AbonnentenInlandSuche::BuildQueryStringPart Builds part of an sql string for a query
 * @param sqlString The string to which to append an SQL statement
 * @param firstWhereClause States whether there already exsists a clause in the supplied string \sqlString
 * @param columnName Name of the column for which this clause implements a criteria
 * @param filterContent Content of the filter for the column \c columnName (line edit or combobox)
 */
void AbonnentenInlandSuche::BuildQueryStringPart(QString& sqlString, bool& firstWhereClause, QString columnName, QString filterContent)
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
    sqlString.append(QString("` LIKE \'%"));
    sqlString.append(filterContent);
    sqlString.append(QString("%\')"));
    return;
}


/**
 * @brief AbonnentenInlandSuche::BuildQueryString Builds a query depending on the content of the filters (line edit and combobox elements on the search form)
 * @return Returns a QString containing an SQL query
 */
QString AbonnentenInlandSuche::BuildQueryString(void)
{
    bool firstWhereClause = true;
    QString sqlString("SELECT * FROM `" + ABONNENTEN_TABLE + "` ");
    QString text;


    text = IDFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("ID"), text);

    text = TitelVorFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("TitelVorgestellt"), text);

    text = TitelNachFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("TitelNachgestellt"), text);

    text = VornameFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("Vorname"), text);

    text = NachnameFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("Nachname"), text);

    text = OrganisationFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("Organisation"), text);

    text = StrasseFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("Straße"), text);

    text = PLZFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("PLZallgemein"), text);

    text = OrtFilter->text();
    if(!text.isNull() && !text.isEmpty())
        BuildQueryStringPart(sqlString, firstWhereClause, QString("Ortallgemein"), text);

    text = StatusFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
        ComboboxBuildQueryString(sqlString, QString("statust"), QString("Status"), text, QString("Status"), firstWhereClause);

    text = AnredeFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
        ComboboxBuildQueryString(sqlString, QString("anredet"), QString("Anrede"), text, QString("Anrede"), firstWhereClause);

    text = AmtstitelFilter->currentText();
    if(!text.isNull() && !text.isEmpty())
        ComboboxBuildQueryString(sqlString, QString("amtstitelt"), QString("Amtstitel"), text, QString("Amtstitel"), firstWhereClause);

    //set the sort order
    if(ui->checkBoxSortByChangeDate->isChecked() == true)
        sqlString.append(QString(" ORDER BY `letzteÄnderung` DESC, `Nachname` ASC, `Vorname` ASC"));
    else
        sqlString.append(" ORDER BY `Nachname` ASC, `Vorname` ASC");

    return sqlString;
}


/**
 * @brief AbonnentenInlandSuche::ComboboxBuildQueryString Builds a query part for \c sqlString.
 * 		  This method assumes that the primary key element column of the comboboxes underlying table is called "ID"
 * @param sqlString SQL string for which to build a query part
 * @param tableName Name of the table
 * @param comboboxColumnName Name of the table's column corresponding to the combobox element
 * @param comboboxText Text that is currently present in the combobox's line edit element
 * @param columnName Name of the "main" table's column
 * @param firstWhereClause States whether this is the first "WHERE-clause" in \c sqlString
 */
void AbonnentenInlandSuche::ComboboxBuildQueryString(QString& sqlString, QString tableName, QString comboboxColumnName, QString comboboxText, QString columnName, bool& firstWhereClause)
{
    QSqlQuery comboboxQuery(dbInterface->GetDatabase());
    QString comboboxSqlString("SELECT ID FROM `");
    comboboxSqlString.append(tableName);
    comboboxSqlString.append("` WHERE `");
    comboboxSqlString.append(comboboxColumnName);
    comboboxSqlString.append("` LIKE (\'");
    comboboxSqlString.append(comboboxText);
    comboboxSqlString.append("\')");

    if(comboboxQuery.exec(comboboxSqlString) == false)
    {
        qInfo() << comboboxQuery.lastError().text();
        qInfo() << "comboboxSqlString: " << comboboxSqlString;
        errorMan.BailOut("Error with comboboxQuery.exec\n", __FILE__, __LINE__, FAILURE);
    }
    while(comboboxQuery.next())
    {
        QString ID = comboboxQuery.value(0).toString();
        BuildQueryStringPart(sqlString, firstWhereClause, columnName, ID);
    }
    return;
}


/**
 * @brief AbonnentenInlandSuche::on_checkBoxSortByChangeDate_stateChanged This slot is activated when the state of the "SortByChangeDate" checkbox is changed
 * @note This slot was automatically created by the UI wizard
 * @param arg1
 */
void AbonnentenInlandSuche::on_checkBoxSortByChangeDate_stateChanged(int arg1)
{
    QString sqlString = BuildQueryString();
    ExecuteQueryUpdateTable(sqlString);
}


/**
 * @brief Key Event Handler
 * @param event The key event, which is to be handled
 */
void AbonnentenInlandSuche::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Backspace)
        ResetFilters();
    //all other events are processed by the base class's event handler
    else
        QWidget::keyPressEvent(event);
}

/**
 * @brief AbonnentenInlandSuche::ResetFilters Resets all the filters (line edits and combo boxes)
 */
void AbonnentenInlandSuche::ResetFilters(void)
{
    ClearTable();
    IDFilter->clear();
    TitelVorFilter->clear();
    TitelNachFilter->clear();
    VornameFilter->clear();
    NachnameFilter->clear();
    OrganisationFilter->clear();
    StrasseFilter->clear();
    PLZFilter->clear();
    OrtFilter->clear();

    StatusFilter->clearEditText();
    AnredeFilter->clearEditText();
    AmtstitelFilter->clearEditText();

    ui->checkBoxSortByChangeDate->setChecked(false);

    QString sqlString = BuildQueryString();
    ExecuteQueryUpdateTable(sqlString);
    VornameFilter->setFocus();
}

/**
 * @brief AbonnentenInlandSuche::ExecuteQueryUpdateTable Executes the query and displays the results in the corresponding table widget
 * @param sqlString QString containing the SQL query
 */
void AbonnentenInlandSuche::ExecuteQueryUpdateTable(QString sqlString)
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

QString AbonnentenInlandSuche::GetStatusName(QString statusID)
{
    return dbInterface->GetNameFromID(STATUS_TABLE, statusID);
}
QString AbonnentenInlandSuche::GetAnredeName(QString  anredeID)
{
    return dbInterface->GetNameFromID(ANREDE_TABLE, anredeID);
}
QString AbonnentenInlandSuche::GetAmtstitelName(QString amtstitelID)
{
    return dbInterface->GetNameFromID(AMTSTITEL_TABLE, amtstitelID);
}

void AbonnentenInlandSuche::UpdateLCDNum()
{
    ui->lcdNumTableRows->display(ui->tableWidget->rowCount());
    if(ui->lcdNumTableRows->intValue() == 0)
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::red));
    else
        ui->lcdNumTableRows->setPalette(QPalette(Qt::GlobalColor::green));
    return;
}

/**
 * @brief AbonnentenInlandSuche::on_tableWidget_cellClicked Slot function for when a cell on the table widget is clicked
 * @param row Row that was clicked
 * @param column Column that was clicked
 */
void AbonnentenInlandSuche::on_tableWidget_cellClicked(int row, int column)
{
    if(column == ABONNENTEN_SUCHE_CLICK_COLUMN)
    {
        QTableWidgetItem *tableWidgetItem = ui->tableWidget->item(row, column);
        if(tableWidgetItem == nullptr)
        {
            errorMan.BailOut("Error, item() returned NULL pointer", __FILE__, __LINE__, FAILURE);
        }
        AbonnentenInland *abonnentenInlandWidget = static_cast<AbonnentenInland*>(static_cast<QTabWidget*>(parent)->widget(ABONNENTEN_TAB));
        if(abonnentenInlandWidget == nullptr)
        {
            errorMan.BailOut("Error, widget() returned NULL pointer", __FILE__, __LINE__, FAILURE);
        }
        unsigned int selectedID = tableWidgetItem->text().toUInt();
        abonnentenInlandWidget->SetActiveID(selectedID);
        abonnentenInlandWidget->LoadActiveRecord();
        static_cast<QTabWidget*>(parent)->setCurrentIndex(ABONNENTEN_TAB);
    }
}
