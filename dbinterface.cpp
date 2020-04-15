#include "dbinterface.h"

DBInterface::DBInterface()
{
    //nothing to do really
}

DBInterface::~DBInterface()
{
    if(database.isOpen())
        database.close();
}

/**
 * @brief DBInterface::GetDatabase Returns a reference to the object's database variable
 * @return Reference to the object's database variable
 */
QSqlDatabase& DBInterface::GetDatabase()
{
    return this->database;
}

/**
 * @brief Connects to MariaDB database
 */
void DBInterface::ConnectToDatabase(QString password)
{
    //Connect to the MariaDB database
    database = QSqlDatabase::addDatabase(DATABASE_TYPE);
    database.setHostName(HOST_NAME);
    database.setPort(HOST_PORT);
    database.setUserName(USER_NAME);
    database.setDatabaseName(DATABASE_NAME);
    database.setPassword(password);
    if(database.open() == false)
    {
        QMessageBox::critical(nullptr, "Error", "Error when opening the database", QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Ok);
        QByteArray ba = database.hostName().toLatin1();
        char buffer[BUFFER_SIZE];
        sprintf(buffer, "Error when opening the database\nHostname: %s\nPort: %u", ba.data(), database.port());
        errorMan.BailOut(buffer, __FILE__, __LINE__, FAILURE);
    }
}

/**
 * @brief DBInterface::GetNameFromID Returns the name of an element from a table given its ID
 * @param table Name of the table in the database
 * @param ID Value of the ID column of the given table
 * @return If there exists no element in the given table with the given ID, an empty string is returned, otherwise the name of the first entry with that ID is returned
 */
QString DBInterface::GetNameFromID(QString table, QString ID)
{
    QSqlQuery query(database);
    QString sqlString;
    QString returnString("");

    if(table.compare(ANREDE_TABLE) == 0)
        sqlString = QString("SELECT `" + ANREDE_ANREDE + "` FROM `" + table + "` WHERE `ID`='" + ID + "'");
    else if(table.compare(STATUS_TABLE) == 0)
        sqlString = QString("SELECT `" + STATUS_STATUS + "` FROM `" + table + "` WHERE `ID`='" + ID + "'");
    else if(table.compare(AMTSTITEL_TABLE) == 0)
        sqlString = QString("SELECT `" + AMTSTITEL_AMTSTITEL + "` FROM `" + table + "` WHERE `ID`='" + ID + "'");
    else
        return returnString;

    if(query.exec(sqlString) == false)
    {
        qInfo() << query.lastError().text();
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with query.exec: " + query.lastError().text().toLocal8Bit(), __FILE__, __LINE__, FAILURE);
    }
    if(query.next() == false)
        returnString = QString("");
    else
        returnString = query.value(0).toString();
    return returnString;
}

/**
 * @brief DBInterface::GetIDFromName Returns the ID (primary key field) from an entry in \c table with a matching \c value
 * @param table The table where to look for the ID
 * @param valueColumn The name of the column, where the \c value is stored
 * @param value Value for which a matching record is searched for in \c table
 * @return Returns the ID of a record with the value \c value in its column \c valueColumn
 */
unsigned int DBInterface::GetIDFromValue(QString table, QString valueColumn, QString value)
{
    QSqlQuery query;
    QString sqlString("SELECT `ID` FROM `" + table + "` WHERE " + "`" + valueColumn + "` LIKE '" + value + "'");
    if(query.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with query.exec(): \nsqlString: " + sqlString.toLocal8Bit(), __FILE__, __LINE__, FAILURE);
    }
    if(query.next() == false)
    {
        errorMan.BailOut("Error with query.next()", __FILE__, __LINE__, FAILURE);
    }
    return query.value(0).toUInt();
}

/**
 * @brief DBInterface::SetComboBoxTabModel Sets the actively displayed value of a combobox that has a QSqlTableModel in the database \c database
 * @param comboBox The combobox whose active value should be set
 * @param currentElemID ID from the table in the database corresponding to the entry that should be currently displayed in the combobox
 */
void DBInterface::SetElemComboBoxTabModel(QComboBox *comboBox, unsigned int currentElemID)
{
    static_cast<QSqlTableModel*>(comboBox->model())->select();
    //set the current value of the combobox
    bool elementFound = false;
    unsigned int tempID = 0;
    for(int index = 0; index < comboBox->model()->rowCount(); index++)
    {
        tempID = static_cast<QSqlTableModel*>(comboBox->model())->record(index).value(ID_POS).toUInt();
        if(tempID == currentElemID)
        {
            comboBox->setCurrentIndex(index);
            elementFound = true;
            break;
        }
    }
    //if no element with matching ID was found, clear the combo box's edit line
    if(!elementFound)
        comboBox->clearEditText();
}

/**
 * @brief DBInterface::SetComboBoxCustomID Sets the actively displayed value of a combobox that has a QSqlRelationalTableModel in the database \c database
 * @param comboBox The combobox whose active value should be set
 * @param currentElemID ID from the table in the database corresponding to the entry that should be currently displayed in the combobox
 * @param IDPos The indexed position (beginning at 0) of the ID field in the combo boxes model
 */
void DBInterface::SetElemComboBoxRelTabModel(QComboBox *comboBox, unsigned int currentElemID, unsigned int IDPos)
{
    static_cast<QSqlRelationalTableModel*>(comboBox->model())->select();
    //set the current value of the combobox
    bool elementFound = false;
    unsigned int tempID = 0;
    for(int index = 0; index < comboBox->model()->rowCount(); index++)
    {
        tempID = static_cast<QSqlRelationalTableModel*>(comboBox->model())->record(index).value(IDPos).toUInt();
        if(tempID == currentElemID)
        {
            comboBox->setCurrentIndex(index);
            elementFound = true;
            break;
        }
    }
    //if no element with matching ID was found, clear the combo box's edit line
    if(!elementFound)
        comboBox->clearEditText();
}

/**
 * @brief DBInterface::AddToComboBoxPromptUpdateRecord Prompts the user via a message box whether the added item in the combox's line edit field
 *		  should be permanently inserted.
 *		  If "yes" is selected by the user, the item is permanently added and the combobox's content is updated to display the new value.
 * 		  Otherwise the old value is restored.
 * @details Should only be used for combo boxes, whose model is QSqlTableModel
 * 			It does not work with QSqlRelationalTableModel
 * @param comboBox The combo box where the item may be inserted
 * @param table Table where the item may be inserted
 * @param column Where the item's name is stored
 * @param currentID ID (primary key of \c table) of the combobox element from the current record (used to revert back to the existing/previous combo box value before the edit was made)
 * @param parentWidget parent Parent widget for the QMessageBox that this method creates for the prompt
 * @return true if the combo box has been updated or false if not
 */
bool DBInterface::AddToComboBoxPromptUpdateRecord(QComboBox *comboBox, QString table, QString column, unsigned int currentID, QWidget *parentWidget)
{
    QMessageBox::StandardButton messageBoxButton;
    messageBoxButton = QMessageBox::question(parentWidget, QString("New Item"), QString("Do you want to permanently add '" + comboBox->currentText() + "'?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(messageBoxButton == QMessageBox::Yes)
    {
        QSqlQuery sqlQuery(database);
        QString sqlString("INSERT INTO `" + table + "` (`" + column + "`) VALUES ('" + comboBox->currentText() + "')");
        if(sqlQuery.exec(sqlString) == false)
        {
            qInfo() << "sqlString: " << sqlString;
            errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
        }

        //get ID from the added combobox element
        sqlString = QString("SELECT `ID` FROM `" + table + "` ORDER BY `ID` DESC LIMIT 1");
        if(sqlQuery.exec(sqlString) == false)
        {
            qInfo() << "sqlString: " << sqlString;
            errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
        }
        if(sqlQuery.next() == false)
        {
            qInfo() << "sqlString: " << sqlString;
            errorMan.BailOut("sqlQuery.next() == false - meaning the query returns no result", __FILE__, __LINE__, FAILURE);
        }
        SetElemComboBoxTabModel(comboBox, sqlQuery.value(0).toUInt());
        return true;
    }
    else
    {
        //setup the combobox and set its current value according to \c currentID
        SetElemComboBoxTabModel(comboBox, currentID);
        return false;
    }
}

/**
 * @brief DBInterface::AddBuchung Adds an entry to BUCHUNGEN_TABLE
 * @param remitterID The "Überweiser ID"
 * @param date The date of the remittance (transfer)
 * @param value The value of the remittance (transfer) in €
 */
void DBInterface::AddBuchung(unsigned int remitterID, QDate date, double value)
{
    QSqlQuery sqlQuery(database);
    QString sqlString("INSERT INTO `" + BUCHUNGEN_TABLE + "` (`" + BUCHUNGEN_UEBERWEISER_ID + "`, `" + BUCHUNGEN_DATUM + "`, `" + BUCHUNGEN_BETRAG + "`) VALUES ('" + QString::number(remitterID) + "', '" + date.toString(DATABASE_DATE_FORMAT) + "', '" + QString::number(value) + "')");

    if(sqlQuery.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
}

/**
 * @brief DBInterface::UpdateRecordValue Updates a single value of a record in the database
 * @details It is assumed that the primary key of the foreign table is called "ID"
 * @param table Name of the table for which a record is updated
 * @param column The column to be updated
 * @param updateValue The new value for the entry (specified by columnName and ID)
 * @param ID The record's ID, which is to be updated
 */
void DBInterface::UpdateRecordValue(QString table, QString column, QString updateValue, unsigned ID)
{
    QSqlQuery updateQuery(database);
    QString queryString("UPDATE `" + table + "` SET `" + column + "` = '" + updateValue + "' WHERE `ID` = '" + QString::number(ID) + "'");

    if(updateQuery.exec(queryString) == false)
    {
        qInfo() << updateQuery.lastError().text();
        qInfo() << "queryString: " << queryString;
        errorMan.BailOut("Error with updateQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
}

///**
// * @brief DBInterface::UpdateRecordForeignKey Updates a single value of some record in the database
// * It looks up the key value from \param foreignValue in the table \param foreignTable and column \param foreignColumn, where we assume that the key value is the first column of the table.
// * This key value of this foreign table is then used to update the record in \param tableName at the column \param columnName and \param ID
// * If no corresponding entry is found in the foreign table, this method will do nothing.
// * @details It is assumed that the primary key of the foreign table is on position ID_POS
// * @param table Name of the table for which a record is updated
// * @param column The column to be updated
// * @param foreignValue The value of the entry (specified by columnName and ID)
// * @param ID The record's ID, which is to be updated
// * @param foreignTable The table to get the new key value from
// * @param foreignColumn The column of the foreign value
// */
//void DBInterface::UpdateRecordForeignKey(QString table, QString column, QString foreignValue, unsigned ID, QString foreignTable, QString foreignColumn)
//{
//    QSqlQuery sqlQuery(database);
//    QString sqlString("SELECT * FROM `" + foreignTable + "` WHERE `" + foreignColumn + "` = '" + foreignValue + "'");
//
//    if(foreignValue.isNull() || foreignValue.isEmpty())
//    {
//        //set the key value to 0 if the entry should be cleared
//        UpdateRecordValue(table, column, QString::number(0), ID);
//    }
//    else
//    {
//        if(sqlQuery.exec(sqlString) == false)
//        {
//            qInfo() << "sqlString:" << sqlString;
//            errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
//        }
//        if(sqlQuery.next())
//        {
//            UpdateRecordValue(table, column, sqlQuery.value(ID_POS).toString(), ID);
//        }
//        //if the foreign value does not exist in the table
//        else
//        {
//            //do nothing
//        }
//    }
//}

/**
 * @brief DBInterface::Contains Checks whether in the database the table \c table contains an element, whose entry in \c column equals \c content
 * @param table The table search for \c content
 * @param column The column to look for \c content
 * @param content The value to look for
 * @return True if the item exists in the table
 */
bool DBInterface::Contains(QString table, QString column, QString content)
{
    QSqlQuery sqlQuery(database);
    QString sqlString("SELECT * FROM `" + table + "` WHERE `" + column + "` = '" + content + "'");
    if(sqlQuery.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
    return sqlQuery.next();
}

/**
 * @brief DBInterface::AddJuncRecord Adds a record to a junction table
 * @details The junction table is assumed to have a primary key consisting of two columns (namely \c thisJuncColumnID and \c otherJuncColumnID)
 * @param juncTable Name of the junction table to which the record should be added
 * @param thisJuncColumnID Name of junction table's first party of primary key - corresponds to \c newID
 * @param otherJuncColumnID Name of junction table's other part of primary key - corresponds to \c otherCurrentID
 * @param thisID Primary key value of new record for column \c thisJuncColumnID
 * @param otherCurrentID Primary key value of new record for column \c otherJuncColumnID
 */
void DBInterface::AddJuncRecord(QString juncTable, QString thisJuncColumnID, QString otherJuncColumnID, unsigned int thisID, unsigned int otherCurrentID)
{
    QSqlQuery sqlQuery(database);
    QString sqlString("INSERT INTO `" + juncTable + "` (`" + thisJuncColumnID + "`, `" + otherJuncColumnID + "`) VALUES ('" + QString::number(thisID) + "', '" + QString::number(otherCurrentID) + "')");
    if(sqlQuery.exec(sqlString) == false)
    {
        qInfo() << "sqlString: " << sqlString;
        errorMan.BailOut("Error with sqlQuery.exec()", __FILE__, __LINE__, FAILURE);
    }
}
