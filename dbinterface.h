#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include "ErrorManagement/ErrorManagement.h"
#include "defaultmeasures.h"

#define DATABASE_TYPE				QString("QMYSQL")
#define DATABASE_NAME				QString("antonius")
#define HOST_ADDRESS				0x7f000001	//corresponds to 127.0.0.1
#define HOST_NAME					QString("localhost")
#define HOST_PORT					3306
#define CONNECTION_WAIT_DURATION	8000		//duration to wait for connection establishment in milliseconds
#define USER_NAME					QString("Sal")
#define PASSWORD					QString("")

extern ErrorManagement errorMan;

class DBInterface
{
private:
    QSqlDatabase database;

public:
    DBInterface();
    ~DBInterface();

    QSqlDatabase& GetDatabase(void);
    void ConnectToDatabase(QString password);
    QString GetNameFromID(QString table, QString ID);
    void SetElemComboBox(QComboBox *comboBox, unsigned int currentElemID);
    bool AddToComboBoxPromptUpdateRecord(QComboBox *comboBox, QString table, QString column, unsigned int currentID, QWidget *parentWidget);
    void AddBuchung(unsigned int remitterID, QDate date, double value);
    //void UpdateRecordForeignKey(QString table, QString column, QString foreignValue, unsigned ID, QString foreignTable, QString foreignColumn);
    void UpdateRecordValue(QString tableName, QString columnName, QString updateValue, unsigned ID);
    bool Contains(QString table, QString column, QString content);
    void AddJuncRecord(QString juncTable, QString thisJuncColumnID, QString otherJuncColumnID, unsigned int newID, unsigned int otherCurrentID);
};
#endif // DBINTERFACE_H
