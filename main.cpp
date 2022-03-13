#include "ErrorManagement/ErrorManagement.h"
#include "antoniusdbguitab.h"
#include <QApplication>
#include <QWidget>
#include <QInputDialog>
#include "defaultmeasures.h"
#include "dbinterface.h"

//global ErrorManagement variable used for generating error message output in the error log file
ErrorManagement errorMan;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);		//does resource management ...

    DBInterface *dbInterface = new DBInterface();
    //database password prompt
    QString password = QInputDialog::getText(nullptr, "Password", "Please enter the password", QLineEdit::Password, "Please enter the password");
    if(password.isNull() || password.isEmpty())
        errorMan.BailOut("No Password has been entered", __FILE__, __LINE__, PASSWORD_ERROR);
    //Connects to MariaDB database
    dbInterface->ConnectToDatabase(password);

    AntoniusDBGUITab w(dbInterface);				//creates the main widget (window)
    w.show();
    return a.exec();
}
