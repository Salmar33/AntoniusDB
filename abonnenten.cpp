#include "abonnenten.h"
#include "ui_abonnenten.h"
#include <QKeyEvent>

AbonnentenInland::AbonnentenInland(DBInterface *dbInterface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbonnentenInland)
{
    ui->setupUi(this);

    this->dbInterface = dbInterface;

    //set up the combo boxes with their respective SQL table models
    try
    {
        amtstitelModel = new QSqlTableModel(this, this->dbInterface->GetDatabase());
        amtstitelModel->setTable(AMTSTITEL_TABLE);
        ui->comboAmtstitel->setModel(amtstitelModel);
        ui->comboAmtstitel->setModelColumn(AMTSTITEL_AMTSTITEL_POS);
        static_cast<QSqlTableModel*>(ui->comboAmtstitel->model())->setSort(AMTSTITEL_AMTSTITEL_POS, Qt::AscendingOrder);
        static_cast<QSqlTableModel*>(ui->comboAmtstitel->model())->select();

        anredeModel = new QSqlTableModel(this, this->dbInterface->GetDatabase());
        anredeModel->setTable(ANREDE_TABLE);
        ui->comboAnrede->setModel(anredeModel);
        ui->comboAnrede->setModelColumn(ANREDE_ANREDE_POS);
        static_cast<QSqlTableModel*>(ui->comboAnrede->model())->select();

        ortModel = new QSqlRelationalTableModel(this, this->dbInterface->GetDatabase());
        ortModel->setTable(PLZ_ORT_JUNC_TABLE);
        ortModel->setRelation(PLZ_ORT_JUNC_ORT_ID_POS, QSqlRelation(ORT_TABLE, ORT_ID, ORT_ORT + ", " + ORT_ID + " as " + ORT_ID));
        ui->comboOrt->setModel(ortModel);
        ui->comboOrt->setModelColumn(PLZ_ORT_JUNC_ORT_ID_POS);
        static_cast<QSqlRelationalTableModel*>(ui->comboOrt->model())->select();

        plzModel = new QSqlTableModel(this, this->dbInterface->GetDatabase());
        plzModel->setTable(PLZ_TABLE);
        ui->comboPLZ->setModel(plzModel);
        ui->comboPLZ->setModelColumn(PLZ_PLZ_POS);
        static_cast<QSqlTableModel*>(ui->comboPLZ->model())->select();

        statusModel = new QSqlTableModel(this, this->dbInterface->GetDatabase());
        statusModel->setTable(STATUS_TABLE);
        ui->comboStatus->setModel(statusModel);
        ui->comboStatus->setModelColumn(STATUS_STATUS_POS);
        static_cast<QSqlTableModel*>(ui->comboStatus->model())->select();

        buchungenModel = new QSqlTableModel(this, this->dbInterface->GetDatabase());
        buchungenModel->setTable(BUCHUNGEN_TABLE);
        buchungenModel->setSort(BUCHUNGEN_DATUM_POS, Qt::DescendingOrder);
        ui->tableBuchungen->setModel(buchungenModel);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_UEBERWEISER_ID_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_BUCHUNGSNUMMER_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_IBAN_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_BIC_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_STATUS_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_GEGKTO_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_VERWENDUNGSZWECK_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_EINGEHEND_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_DANKBRIEF_POS, true);
        ui->tableBuchungen->setColumnHidden(BUCHUNGEN_LETZTE_AENDERUNG_POS, true);
    }
    catch(std::bad_alloc exception)
    {
        errorMan.BailOut("std::bad_alloc exception thrown", __FILE__, __LINE__, FAILURE);
    }

    //set the special value texts for the date time fields (the text to display if the current value is equal to the minimum displayable value)
    ui->dateErstelltAm->setSpecialValueText(DATETIME_SPECIAL_VALUE);
    ui->dateStatusGesetzt->setSpecialValueText(DATETIME_SPECIAL_VALUE);
    ui->dateLetzteAenderung->setSpecialValueText(DATETIME_SPECIAL_VALUE);

    //look up and display the first record in the database
    QSqlQuery sqlQuery(dbInterface->GetDatabase());
    if(sqlQuery.exec("SELECT * FROM `" + ABONNENTEN_TABLE + "` ORDER BY `ID` ASC LIMIT 1") == false)
    {
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
    if(sqlQuery.next() == false)
    {
        errorMan.BailOut("sqlQuery.next() == false - no entry found", __FILE__, __LINE__, FAILURE);
    }
    activeID = sqlQuery.value(ABONNENTEN_ID_POS).toUInt();

    //since I cannot subclass the GUI elements from the wizard (in abonnenten.ui) and reimplement their event handler, I have to use this alternative method to filter events, effectively circumventing their standard event handler
    ui->comboAmtstitel->installEventFilter(this);
    ui->comboAnrede->installEventFilter(this);
    ui->comboOrt->installEventFilter(this);
    ui->comboPLZ->installEventFilter(this);
    ui->comboStatus->installEventFilter(this);
    ui->dateStatusGesetzt->installEventFilter(this);


    LoadActiveRecord();
}

AbonnentenInland::~AbonnentenInland()
{
    delete ui;
    delete amtstitelModel;
    delete anredeModel;
    delete ortModel;
    delete plzModel;
    delete statusModel;
}

/**
 * @brief AbonnentenInland::eventFilter Event filter to detect, when one of the combo boxes loses focus or return is pressed in order to update them
 * @param object The object, whose event has been caught
 * @param event The caught event
 * @return False if the event can be handled further by \c object itself (according to the docu) otherwise true
 */
bool AbonnentenInland::eventFilter(QObject *object, QEvent *event)
{
    static std::atomic_flag atomicFlag = ATOMIC_FLAG_INIT;
    bool oldPrChange = prChange;
    if(object == ui->comboAmtstitel || object == ui->comboAnrede || object == ui->comboOrt || object == ui->comboPLZ || object == ui->comboStatus)
    {
        if(event->type() == QEvent::FocusOut || (event->type() == QEvent::KeyRelease && (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Return || static_cast<QKeyEvent*>(event)->key() == Qt::Key_Enter)))
        {
            QSqlQuery sqlQuery(dbInterface->GetDatabase());
            QString sqlString("SELECT * FROM `" + ABONNENTEN_TABLE + "` WHERE `" + ABONNENTEN_ID + "` = '" + QString::number(activeID) + "'");

            //select the active record in the database
            if(sqlQuery.exec(sqlString) == false)
            {
                qInfo() << "sqlString: " << sqlString;
                errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
            }
            if(sqlQuery.next() == false)
            {
                qInfo() << "sqlString: " << sqlString;
                errorMan.BailOut("sqlQuery.next() == false \nactive record was not found in database", __FILE__, __LINE__, FAILURE);
            }
            prChange = true;
            if(object == ui->comboAmtstitel)
                HandleComboBoxManipulationTableModel(ui->comboAmtstitel, AMTSTITEL_TABLE, AMTSTITEL_AMTSTITEL, AMTSTITEL_ID, ABONNENTEN_TABLE, ABONNENTEN_AMTSTITEL, sqlQuery.value(ABONNENTEN_AMTSTITEL_POS).toUInt(), true, atomicFlag);
            else if(object == ui->comboAnrede)
                HandleComboBoxManipulationTableModel(ui->comboAnrede, ANREDE_TABLE, ANREDE_ANREDE, ANREDE_ID, ABONNENTEN_TABLE, ABONNENTEN_ANREDE, sqlQuery.value(ABONNENTEN_ANREDE_POS).toUInt(), false, atomicFlag);
            else if(object == ui->comboOrt)
                HandleComboBoxManipulationRelationalTableModel(ui->comboOrt, ORT_TABLE, ORT_ORT, ABONNENTEN_TABLE, ABONNENTEN_ORTAUSTRIA, sqlQuery.value(ABONNENTEN_ORTAUSTRIA_POS).toUInt(), true, atomicFlag, PLZ_ORT_JUNC_TABLE, PLZ_ORT_JUNC_ORT_ID, PLZ_ORT_JUNC_PLZ_ID, sqlQuery.value(ABONNENTEN_PLZAUSTRIA_POS).toUInt());
            else if(object == ui->comboPLZ)
                HandleComboBoxManipulationTableModel(ui->comboPLZ, PLZ_TABLE, PLZ_PLZ, PLZ_ID, ABONNENTEN_TABLE, ABONNENTEN_PLZAUSTRIA, sqlQuery.value(ABONNENTEN_PLZAUSTRIA_POS).toUInt(), false, atomicFlag);
            else if(object == ui->comboStatus)
            {
                if(HandleComboBoxManipulationTableModel(ui->comboStatus, STATUS_TABLE, STATUS_STATUS, STATUS_ID, ABONNENTEN_TABLE, ABONNENTEN_STATUS, sqlQuery.value(ABONNENTEN_STATUS_POS).toUInt(), false, atomicFlag))
                    SetUpdateDateTimeForStatusChangeToCurrentDateTime();
            }
        }
        else if(event->type() == QEvent::KeyPress && static_cast<QKeyEvent*>(event)->key() == Qt::Key_F4)
        {
            this->keyPressEvent(static_cast<QKeyEvent*>(event));
            return true;	//telling object to not handle this keypress event further
        }
    }
    else if(object == ui->dateStatusGesetzt)
    {
        if(event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Delete)
            {
                ui->dateStatusGesetzt->setDateTime(ui->dateStatusGesetzt->minimumDateTime());
                dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_STATUSGESETZTAM, ui->dateStatusGesetzt->date().toString(DATABASE_DATE_FORMAT), activeID);
                LoadActiveRecord();
            }
        }
    }
    prChange = oldPrChange;
    return false;
}

/**
 * @brief Slot function for when the "Heute" button is released to set the date
 */
void AbonnentenInland::on_buttonHeute_released()
{
    //if the "heute" button is pressed, write the current date in the dateErstelltAm text field and update the record in the database
    ui->dateErstelltAm->setDate(QDate::currentDate());
    dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ERSTELLTAM, ui->dateErstelltAm->date().toString(DATABASE_DATE_FORMAT), activeID);
    LoadActiveRecord();
}

/**
 * @brief Overridden Key Event Handler
 * @param event The key event, which is to be handled
 */
void AbonnentenInland::keyPressEvent(QKeyEvent *event)
{
    // if CTRL + D is pressed, then move the cursor to the txtEditAnmerkungen field and enter the current date if not yet present
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_D)
        this->MoveToAnmerkungen();
    else if(event->key() == Qt::Key_F5)
        LoadActiveRecord();
    else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_B)
    {
        BuchungHinzu buchungDialog(activeID, dbInterface, this);
        buchungDialog.exec();
        LoadActiveRecord();
    }
    //all other events are processed by the base class's event handler
    else
        QWidget::keyPressEvent(event);
}

/**
 * @brief AbonnentenInland::keyReleaseEvent Overridden key event handler
 * @param event The key even, which is to be handled upon release of a key
 */
void AbonnentenInland::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Left)
    {
        SetPreviousRecordActive();
        LoadActiveRecord();
    }
    else if(event->modifiers() == Qt::AltModifier && event->key() == Qt::Key_Right)
    {
        SetNextRecordActive();
        LoadActiveRecord();
    }
    else
        QWidget::keyReleaseEvent(event);
}

/**
 * @brief Moves the cursor to the Anmerkungen Edit field and writes down the current date in a new line if not yet present
 */
void AbonnentenInland::MoveToAnmerkungen(void)
{
    ui->txtEditAnmerkungen->setFocus();
    QString text = ui->txtEditAnmerkungen->document()->toPlainText();
    if(text.isNull() or text.isEmpty())
    {
        ui->txtEditAnmerkungen->setText(QDate::currentDate().toString(QString(ANMERKUNGEN_DATE_FORMAT)) + QString(" "));
    }
    else
    {
        if(!text.contains(QDate::currentDate().toString(QString(ANMERKUNGEN_DATE_FORMAT))))
        {
            ui->txtEditAnmerkungen->append(QDate::currentDate().toString(QString(ANMERKUNGEN_DATE_FORMAT)) + QString(" "));
        }
    }
    //position the cursor at the end of the text edit field
    ui->txtEditAnmerkungen->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}

/**
 * @brief AbonnentenInland::SetPreviousRecordActive Sets the \c activeID variable to the previous record (ordered by IDs) in the ABONNENTEN_TABLE table.
 * 													If the active record is already the first record \c activeID is left unchanged.
 * @details Changes \c activeID
 */
void AbonnentenInland::SetPreviousRecordActive()
{
    QSqlQuery sqlQuery(dbInterface->GetDatabase());
    QString sqlString("SELECT `" + ABONNENTEN_ID + "` FROM `" + ABONNENTEN_TABLE + "` ORDER BY `" + ABONNENTEN_ID + "` ASC");

    if(sqlQuery.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }

    //iterate through all record IDs; when the active ID has been found set the active ID to the previous one in the iteration
    for(unsigned int prevID = 0; sqlQuery.next(); prevID = sqlQuery.value(0).toUInt())
    {
        if(sqlQuery.value(0).toUInt() == activeID)
        {
            if(prevID != 0)
            {
                activeID = prevID;
            }
            return;
        }
    }
}

/**
 * @brief AbonnentenInland::SetNextRecordActive Sets the \c activeID variable to the next record (ordered by IDs) in the ABONNENTEN_TABLE table.
 * 													If the active record is already the last record \c activeID is left unchanged.
 * @details Changes \c activeID
 */
void AbonnentenInland::SetNextRecordActive()
{
    QSqlQuery sqlQuery(dbInterface->GetDatabase());
    QString sqlString("SELECT `" + ABONNENTEN_ID + "` FROM `" + ABONNENTEN_TABLE + "` ORDER BY `" + ABONNENTEN_ID + "` ASC");

    if(sqlQuery.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }

    //iterate through all record IDs; when the active ID has been found set the active ID to the next one in the iteration if it exists
    for(; sqlQuery.next();)
    {
        if(sqlQuery.value(0).toUInt() == activeID)
        {
            if(sqlQuery.next())
            {
                activeID = sqlQuery.value(0).toUInt();
            }
            return;
        }
    }
}

/**
 * @brief AbonnentenInland::on_pushButtonNewRecord_clicked When this button was clicked a new record is added to the database
 */
void AbonnentenInland::on_pushButtonNewRecord_clicked()
{
    QMessageBox::StandardButton messageBoxButton;
    QSqlQuery sqlQuery;
    QString queryString("INSERT INTO `" + ABONNENTEN_TABLE + "` (`erstelltAm`, `Land`, `letzteÄnderung`, `Dankschreiben`, `Antoniusanzahl`, `StatusGesetztAm`, `Anmerkungen`) " +
        "VALUES ( '" +
            QDateTime::currentDateTime().toString(DATABASE_DATETIME_FORMAT) + "' ," +
            QString("'A'") + ", '" +
            QDateTime::currentDateTime().toString(DATABASE_DATETIME_FORMAT) + "' ," +
            QString::number(0) + "," +
            QString::number(1) + "," +
            "'0001-01-01'" + ", '" +
            QDate::currentDate().toString(QString(ANMERKUNGEN_DATE_FORMAT)) + QString(" hinzugefügt laut '")
        + ")");

    messageBoxButton = QMessageBox::question(this, QString("New Record"), QString("Do you want to add a new record?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(messageBoxButton == QMessageBox::Yes)
    {
        //add new record to database
        if(sqlQuery.exec(queryString) == false)
        {
            qInfo() << "queryString: " << queryString;
            errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
        }

        //look up the new record in the database and retrieve its ID and make this new ID the active ID
        if(sqlQuery.exec("SELECT * FROM `" + ABONNENTEN_TABLE + "` ORDER BY `ID` DESC LIMIT 1") == false)
        {
            errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
        }
        if(sqlQuery.next() == false)
        {
            errorMan.BailOut("sqlQuery.next() == false - no entry found", __FILE__, __LINE__, FAILURE);
        }
        activeID = sqlQuery.value(ABONNENTEN_ID_POS).toUInt();

        LoadActiveRecord();
    }
}


/**
 * @brief AbonnentenInland::LoadActiveRecord Loads the active record (the record with ID \c activeID) from the database
 */
void AbonnentenInland::LoadActiveRecord()
{
    QSqlQuery sqlQuery(dbInterface->GetDatabase());

    //select the active record in the database
    if(sqlQuery.exec("SELECT * FROM `" + ABONNENTEN_TABLE + "` WHERE `ID` = '" + QString::number(activeID) + "'") == false)
    {
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
    if(sqlQuery.next() == false)
    {
        qInfo() << "activeID = " << activeID;
        errorMan.BailOut("sqlQuery.next() == false \nactive record was not found in database", __FILE__, __LINE__, FAILURE);
    }

    prChange = true;
    //reload the content of the comboboxes and set their current value
    anredeModel->select();
    dbInterface->SetElemComboBoxTabModel(ui->comboAnrede, sqlQuery.value(ABONNENTEN_ANREDE_POS).toUInt());
    amtstitelModel->select();
    dbInterface->SetElemComboBoxTabModel(ui->comboAmtstitel, sqlQuery.value(ABONNENTEN_AMTSTITEL_POS).toUInt());
    plzModel->select();
    dbInterface->SetElemComboBoxTabModel(ui->comboPLZ, sqlQuery.value(ABONNENTEN_PLZAUSTRIA_POS).toUInt());
    statusModel->select();
    dbInterface->SetElemComboBoxTabModel(ui->comboStatus, sqlQuery.value(ABONNENTEN_STATUS_POS).toUInt());
    ortModel->setFilter(QString("`" + PLZ_ORT_JUNC_PLZ_ID + "` = '" + sqlQuery.value(ABONNENTEN_PLZAUSTRIA_POS).toString() + "'"));
    ortModel->select();
    //ortModel corresponds to a QSqlRelationalTableModel (internally a join of the tables is happening), where the ID of the corresponding "Ort" is
    //at the 3rd position --> index 2
    dbInterface->SetElemComboBoxRelTabModel(ui->comboOrt, sqlQuery.value(ABONNENTEN_ORTAUSTRIA_POS).toUInt(), 2);
    if(!sqlQuery.value(ABONNENTEN_ERSTELLTAM_POS).toDate().isValid() || sqlQuery.value(ABONNENTEN_ERSTELLTAM_POS).toString().compare(ZERO_DATETIME_STRING) == 0)
        ui->dateErstelltAm->setDateTime(ui->dateErstelltAm->minimumDateTime());
    else
        ui->dateErstelltAm->setDate(sqlQuery.value(ABONNENTEN_ERSTELLTAM_POS).toDate());
    ui->lineEditID->setText(sqlQuery.value(ABONNENTEN_ID_POS).toString());
    ui->lineEditTitelVor->setText(sqlQuery.value(ABONNENTEN_TITELVOR_POS).toString());
    ui->lineEditTitelNach->setText(sqlQuery.value(ABONNENTEN_TITELNACH_POS).toString());
    ui->lineEditVorname->setText(sqlQuery.value(ABONNENTEN_VORNAME_POS).toString());
    ui->lineEditNachname->setText(sqlQuery.value(ABONNENTEN_NACHNAME_POS).toString());
    ui->lineEditOrganisation->setText(sqlQuery.value(ABONNENTEN_ORGANISATION_POS).toString());
    ui->lineEditStrasse->setText(sqlQuery.value(ABONNENTEN_STRASSE_POS).toString());
    ui->lineEditLand->setText(sqlQuery.value(ABONNENTEN_LAND_POS).toString());
    ui->lineEditPLZ->setText(sqlQuery.value(ABONNENTEN_PLZALLGEMEIN_POS).toString());
    ui->lineEditOrt->setText(sqlQuery.value(ABONNENTEN_ORTALLGEMEIN_POS).toString());
    ui->lineEditMietcode->setText(sqlQuery.value(ABONNENTEN_MIETCODE_POS).toString());
    if(!sqlQuery.value(ABONNENTEN_LETZTEAENDERUNG_POS).toDateTime().isValid() || sqlQuery.value(ABONNENTEN_LETZTEAENDERUNG_POS).toString().compare(ZERO_DATETIME_STRING) == 0)
        ui->dateLetzteAenderung->setDateTime(ui->dateLetzteAenderung->minimumDateTime());
    else
        ui->dateLetzteAenderung->setDateTime(sqlQuery.value(ABONNENTEN_LETZTEAENDERUNG_POS).toDateTime());
    sqlQuery.value(ABONNENTEN_DANKSCHREIBEN_POS).toBool() ? ui->checkDankschreiben->setCheckState(Qt::Checked) : ui->checkDankschreiben->setCheckState(Qt::Unchecked);
    ui->spinAntoniusAnzahl->setValue(sqlQuery.value(ABONNENTEN_ANTONIUSANZAHL_POS).toInt());
    ui->lineEditZusatzinfo->setText(sqlQuery.value(ABONNENTEN_ZUSATZINFO_POS).toString());
    ui->lineEditTelNr->setText(sqlQuery.value(ABONNENTEN_TELNR_POS).toString());
    ui->lineEditMobil->setText(sqlQuery.value(ABONNENTEN_MOBIL_POS).toString());
    ui->lineEditEmail->setText(sqlQuery.value(ABONNENTEN_EMAIL_POS).toString());
    ui->lineEditBeruf->setText(sqlQuery.value(ABONNENTEN_BERUFTAETIGKEIT_POS).toString());
    if(!sqlQuery.value(ABONNENTEN_STATUSGESETZTAM_POS).toDateTime().isValid() || sqlQuery.value(ABONNENTEN_STATUSGESETZTAM_POS).toString().compare(ZERO_DATETIME_STRING) == 0)
        ui->dateStatusGesetzt->setDateTime(ui->dateStatusGesetzt->minimumDateTime());
    else
        ui->dateStatusGesetzt->setDateTime(sqlQuery.value(ABONNENTEN_STATUSGESETZTAM_POS).toDateTime());
    ui->txtEditAnmerkungen->setText(sqlQuery.value(ABONNENTEN_ANMERKUNGEN_POS).toString());
    //set up the model for "Buchungen"
    buchungenModel->setFilter(QString("`" + BUCHUNGEN_UEBERWEISER_ID + "` = '" + QString::number(activeID) + "'"));
    buchungenModel->select();
    prChange = false;
}

/**
 * @brief AbonnentenInland::SetandUpdateDateTimeLastChange Updates the "letzte Änderung" date time field in the form and in the database with the current date
 * @details Temporarily modies \c this->prChange
 */
void AbonnentenInland::SetUpdateDateTimeLastChangeToCurrentDateTime(void)
{
        QDateTime time = QDateTime::currentDateTime();
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_LETZTEAENDERUNG, time.toString(DATABASE_DATETIME_FORMAT), activeID);
}

/**
 * @brief AbonnentenInland::SetUpdateDateTimeForStatusChangeToCurrentDateTime Updates the "Status gesetzt" field in the form and database with the current date
 * @details Temporarily modies \c this->prChange
 */
void AbonnentenInland::SetUpdateDateTimeForStatusChangeToCurrentDateTime(void)
{
        QDateTime time = QDateTime::currentDateTime();
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_STATUSGESETZTAM, time.toString(DATABASE_DATETIME_FORMAT), activeID);
}

/**
 * @brief AbonnentenInland::on_lineEditTitelVor_textEdited Slot function to update the record in the database when the "Titel vorgestellt" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditTitelVor_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_TITELVOR, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditTitelNach_textEdited Slot function to update the record in the database when the "Titel nachgestellt" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditTitelNach_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_TITELNACH, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditVorname_textEdited Slot function to update the record in the database when the "Vorname" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditVorname_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_VORNAME, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditNachname_textEdited Slot function to update the record in the database when the "Nachname" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditNachname_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_NACHNAME, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditOrganisation_textEdited Slot function to update the record in the database when the "Organisation" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditOrganisation_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ORGANISATION, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditStrasse_textEdited Slot function to update the record in the database when the "Straße" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditStrasse_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_STRASSE, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditLand_textEdited Slot function to update the record in the database when the "Land" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditLand_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_LAND, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditPLZ_textEdited Slot function to update the record in the database when the "PLZ" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditPLZ_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_PLZALLGEMEIN, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditOrt_textEdited Slot function to update the record in the database when the "Ort" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditOrt_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ORTALLGEMEIN, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditMietcode_textEdited Slot function to update the record in the database when the "Mietcode" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditMietcode_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_MIETCODE, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditZusatzinfo_textEdited Slot function to update the record in the database when the "Zusatzinfo" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditZusatzinfo_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ZUSATZINFO, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditTelNr_textEdited Slot function to update the record in the database when the "TelNr" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditTelNr_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_TELNR, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditMobil_textEdited Slot function to update the record in the database when the "Mobil" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditMobil_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_MOBIL, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditEmail_textEdited Slot function to update the record in the database when the "Email" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditEmail_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_EMAIL, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_lineEditBeruf_textEdited Slot function to update the record in the database when the "Beruf/Tätigkeit" field is edited
 * @param arg1 New content of the data field
 */
void AbonnentenInland::on_lineEditBeruf_textEdited(const QString &arg1)
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_BERUFTAETIGKEIT, arg1, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_txtEditAnmerkungen_textChanged Slot function to update the record in the database when the "Anmerkungen" field is edited
 */
void AbonnentenInland::on_txtEditAnmerkungen_textChanged()
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ANMERKUNGEN, ui->txtEditAnmerkungen->toPlainText(), activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_checkDankschreiben_clicked Slot function to update the "Dankeschreiben" column, when the "Dankschreiben" checkbox is clicked
 * @param checked True if the if the button is checked and false otherwise
 */
void AbonnentenInland::on_checkDankschreiben_clicked(bool checked)
{
    if(!prChange)
    {
        if(checked)
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_DANKSCHREIBEN, QString::number(1), activeID);
        else
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_DANKSCHREIBEN, QString::number(0), activeID);

        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_spinAntoniusAnzahl_editingFinished Slot function to update the "Antoniusanzahl" column, when the corresponding spinbox is changed and the spinbox loses focus
 */
void AbonnentenInland::on_spinAntoniusAnzahl_editingFinished()
{
    if(!prChange)
    {
        dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ANTONIUSANZAHL, QString::number(ui->spinAntoniusAnzahl->value()), activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_dateErstelltAm_dateTimeChanged Slot function to update the "erstellt am" entry, when the correspnding field in the form is changed
 * @param dateTime The new date and time
 */
void AbonnentenInland::on_dateErstelltAm_dateTimeChanged(const QDateTime &dateTime)
{
    if(!prChange)
    {
        QString newStrValue = dateTime.toString(DATABASE_DATETIME_FORMAT);
        if(newStrValue.isEmpty() || newStrValue.isNull() || !dateTime.isValid())
        {
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ERSTELLTAM, ZERO_DATETIME_STRING, activeID);
            ui->dateErstelltAm->clear();
        }
        else
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_ERSTELLTAM, newStrValue, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::on_dateStatusGesetzt_dateTimeChanged Flots function to update the "Status gesetzt am" entry, when the content of the corresponding field in the form is changed
 * @param dateTime The new date and time
 */
void AbonnentenInland::on_dateStatusGesetzt_dateTimeChanged(const QDateTime &dateTime)
{
    if(!prChange)
    {
        QString newStrValue = dateTime.toString(DATABASE_DATETIME_FORMAT);
        if(newStrValue.isEmpty() || newStrValue.isNull() || !dateTime.isValid())
        {
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_STATUSGESETZTAM, ZERO_DATETIME_STRING, activeID);
            ui->dateStatusGesetzt->clear();
        }
        else
            dbInterface->UpdateRecordValue(ABONNENTEN_TABLE, ABONNENTEN_STATUSGESETZTAM, newStrValue, activeID);
        SetUpdateDateTimeLastChangeToCurrentDateTime();
        LoadActiveRecord();
    }
}

/**
 * @brief AbonnentenInland::HandleComboBoxManipulationTableModel Handles the manipulation of combo boxes - should be called after the line edit of a combo box has been changed (and lost focus or similar) or a new item has been selected
 * 		  It handles the update of the main table and the update of the combo box table in case a new item was chosen to be added to the combo box
 * @details Only works for combo boxes that get their data directly via a QSqlTableModel
 *			This method does not work for combo boxes that use a QSqlRelationalTableModel and get their entries from a junction table
 * 			For combo boxes that use a QSqlRelationalTableModel use HandleComboBoxManipulationRelationalTableModel() instead
 * @param comboBox The combo box that is updated
 * @param comboBoxTable The table that contains all available options of the combo box
 * @param comboBoxColumnName The column, whose values are displayed
 * @param comboBoxColumnID The ID column (primary key) of the combo box table
 * @param tableMain The main table, where the combo boxes current value is stored
 * @param columnMain The column of the main table, where the combo boxes current value is stored
 * @param currentID The current ID (content of \c columnMain from the main table) corresponding to the combo box \c comboBox
 * @param allowNew If true and the combo box's line edit contains an element not in its content table, the user will be prompted to add the new element.
 * 				   Otherwise if it is false the combo box's line edit will be set to display the "old" value.
 * @param atomicFlag Reference to an atomic flag that will prevent this function to be called simultaneously by multiple threads
 * @return true if \c columnMain in \c tableMain was actually updated with a new value (which could also be empty, meaning the field was effectively cleared) otherwise false
 */
bool AbonnentenInland::HandleComboBoxManipulationTableModel(QComboBox *comboBox, QString comboBoxTable, QString comboBoxColumnName, QString comboBoxColumnID, QString tableMain, QString columnMain, unsigned int currentID, bool allowNew, std::atomic_flag& atomicFlag)
{
    bool returnVal = false;
    //if the atomic flag was not set previously set it (check and set done atomically)
    if(!atomicFlag.test_and_set())
    {
        int currentTextIndex = comboBox->findText(comboBox->currentText(), Qt::MatchFixedString);
        //if the combo box's line edit is not empty, but its content does not match any of the elements in the combo box's table (comparison is case insensitive - as are comparisons in the database)
        if(currentTextIndex == -1 && !comboBox->currentText().isEmpty() && !comboBox->currentText().isNull())
        {
            if(allowNew)
            {
                if(dbInterface->AddToComboBoxPromptUpdateRecord(comboBox, comboBoxTable, comboBoxColumnName, currentID, this))
                {
                    dbInterface->UpdateRecordValue(tableMain, columnMain, static_cast<QSqlTableModel*>(comboBox->model())->record(comboBox->currentIndex()).value(ID_POS).toString(), activeID);
                    SetUpdateDateTimeLastChangeToCurrentDateTime();
                    LoadActiveRecord();
                    returnVal = true;
                }
            }
            else
            {
                //reload the "old" value in the combo box
                dbInterface->SetElemComboBoxTabModel(comboBox, currentID);
                returnVal = false;
            }
        }
        else
        {
            //if the combobox's line edit is empty
            if(comboBox->currentText().isEmpty() || comboBox->currentText().isNull())
            {
                //if the corresponding column in the record is "empty"
                if(currentID == 0)
                {
                    //do nothing since, the entry was already empty
                    returnVal = false;
                }
                else
                {
                    dbInterface->UpdateRecordValue(tableMain, columnMain, "0", activeID);
                    SetUpdateDateTimeLastChangeToCurrentDateTime();
                    LoadActiveRecord();
                    returnVal = true;
                }
            }
            //if the combobox's line edit is not empty and its current text is part of its content list
            else
            {
                QSqlQuery sqlQuery(dbInterface->GetDatabase());
                QString sqlString("SELECT * FROM `" + comboBoxTable+ "` WHERE `" + comboBoxColumnID + "` = '" + QString::number(currentID) + "' AND `" + comboBoxColumnName + "` = '" + comboBox->currentText() + "'");
                if(sqlQuery.exec(sqlString) == false)
                {
                    qInfo() << "sqlString : " << sqlString;
                    errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
                }
                if(sqlQuery.next())
                {
                    //do nothing as the entry is already set
                    returnVal = false;
                }
                else
                {
                    dbInterface->UpdateRecordValue(tableMain, columnMain, static_cast<QSqlTableModel*>(comboBox->model())->record(currentTextIndex).value(ID_POS).toString(), activeID);
                    SetUpdateDateTimeLastChangeToCurrentDateTime();
                    LoadActiveRecord();
                    returnVal = true;
                }
            }
        }
        //atomically clear the flag
        atomicFlag.clear();
    }
    return returnVal;
}

/**
 * @brief AbonnentenInland::HandleComboBoxManipulationRelationalTableModel Handles the manipulation of combo boxes - should be called after the line edit of a combo box has been changed (and lost focus or similar) or a new item has been selected
 * 		  It handles the update of the main table and the update of the combo box table in case a new item was chosen to be added to the combo box
 * @details Only works for combo boxes that get their data via a QSqlRelationalTableModel
 * 			For combo boxes that get their content from a QSqlTableModel use HandleComboBoxManipulationTableModel() instead
 * 			Also note that this method is pretty much tailored to the needs of the Ort-PLZ relation, use for other purposes with care
 * @param comboBox The combo box that is updated
 * @param comboBoxTable The table that contains all available options of the combo box
 * @param comboBoxColumnName The column, whose values are displayed
 * @param tableMain The main table, where the combo box's current value is stored
 * @param columnMain The column of the main table, where the combo box's current value is stored
 * @param currentID The current ID (content of \c columnMain from the main table) corresponding to the combo box \c comboBox
 * @param allowNewJunc If true and the combo box's line edit contains an element not in its junction table, the user will be prompted to add the new element.
 * 					   Otherwise if it is false the combo box's line edit will be set to display the "old" value.
 * @param atomicFlag Reference to an atomic flag that will prevent this function to be called simultaneously by multiple threads
 * @param juncTable The name of the junction table
 * @param thisJuncColumnID The name of the ID column of the junction table for the element in the combobox (it is assumed that the primary key for this junction table is a pair, where \c thisJuncColumnID correspondons to the one in the combo box)
 * @param otherJuncColumnID The name of the ID column of the junction table for the "other" key element (it is assumed that the primary key for this junction table is a pair)
 * @param otherCurrentID Current ID value of the junction table for the currently active record
 */
void AbonnentenInland::HandleComboBoxManipulationRelationalTableModel(QComboBox *comboBox, QString comboBoxTable, QString comboBoxColumnName, QString tableMain, QString columnMain, unsigned int currentID, bool allowNewJunc, std::atomic_flag& atomicFlag, QString juncTable, QString thisJuncColumnID, QString otherJuncColumnID, unsigned int otherCurrentID)
{
    //if the atomic flag was not set previously set it (check and set done atomically)
    if(!atomicFlag.test_and_set())
    {
        int currentTextIndex = comboBox->findText(comboBox->currentText(), Qt::MatchFixedString);
        //if the combo box's line edit is not empty, but its content does not match any of the elements in the join (on \c otherCurrentID) between combo box's table and the junction table (comparison is case insensitive - as are comparisons in the database)
        if(currentTextIndex == -1 && !comboBox->currentText().isEmpty() && !comboBox->currentText().isNull())
        {
            if(allowNewJunc)
            {
                //check whether the current text of the combo box is present in the combo box table
                if(dbInterface->Contains(comboBoxTable, comboBoxColumnName, comboBox->currentText()))
                {
                    QMessageBox::StandardButton messageBoxButton = QMessageBox::question(this, QString("New association"), QString("Do you want to permanently associate '" + comboBox->currentText() + "' with the current PLZ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if(messageBoxButton == QMessageBox::Yes)
                    {
                        unsigned int newID = dbInterface->GetIDFromValue(comboBoxTable, comboBoxColumnName, comboBox->currentText());
                        dbInterface->AddJuncRecord(juncTable, thisJuncColumnID, otherJuncColumnID, newID, otherCurrentID);
                        dbInterface->UpdateRecordValue(tableMain,columnMain, QString::number(newID), activeID);
                        SetUpdateDateTimeLastChangeToCurrentDateTime();
                        LoadActiveRecord();
                    }
                    else
                    {
                        //reload the "old" value in the combo box
                        dbInterface->SetElemComboBoxTabModel(comboBox, currentID);
                    }
                }
                else
                {
                    //reload the "old" value in the combo box
                    dbInterface->SetElemComboBoxTabModel(comboBox, currentID);
                }

            }
            else
            {
                //reload the "old" value in the combo box
                dbInterface->SetElemComboBoxTabModel(comboBox, currentID);
            }
        }
        else
        {
            //if the combobox's line edit is empty
            if(comboBox->currentText().isEmpty() || comboBox->currentText().isNull())
            {
                //if the corresponding column in the record is "empty"
                if(currentID == 0)
                {
                    //do nothing since, the entry was already empty
                }
                else
                {
                    dbInterface->UpdateRecordValue(tableMain, columnMain, "0", activeID);
                    SetUpdateDateTimeLastChangeToCurrentDateTime();
                    LoadActiveRecord();
                }
            }
            //if the combobox's line edit is not empty and its current text is part of its content list
            else
            {
                int index = comboBox->findText(comboBox->currentText(), Qt::MatchFixedString);
                unsigned int newID = static_cast<QSqlRelationalTableModel*>(comboBox->model())->record(index).value(2).toUInt();
                dbInterface->UpdateRecordValue(tableMain, columnMain, QString::number(newID), activeID);
                SetUpdateDateTimeLastChangeToCurrentDateTime();
                LoadActiveRecord();
            }
        }
        //atomically clear the flag
        atomicFlag.clear();
    }
}

/**
 * @brief AbonnentenInland::SetActiveID Sets the active ID of this form
 * @param newActiveID The new active ID
 */
void AbonnentenInland::SetActiveID(unsigned int newActiveID)
{
    this->activeID = newActiveID;
}

/**
 * @brief AbonnentenInland::on_buttonBuchungHinzu_clicked Slot function for when the "Buchung hinzufügen" button is clicked
 */
void AbonnentenInland::on_buttonBuchungHinzu_clicked()
{
    BuchungHinzu buchungDialog(activeID, dbInterface, this);
    buchungDialog.exec();
    LoadActiveRecord();
}
