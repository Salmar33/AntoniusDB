AntoniusDB is a database client application.
It provides a GUI to interface with a mariaDB database specifically designed for address management of subscribers of the magazine "Antonius".

This software uses the Qt framework and is published under the GNU General Public License - see "License.txt"

In ".\_dll file for 32bit mingw" you'll find the necessary .dll file and a README.txt describing how you enable Qt to work with mariaDB (mysql).

In case you want to further develop and then redistribute this application, on windows plattforms the easiest way to deploy it is to call "windeployqt <path to application binary>"

In the current Qt version there is a bug in the automatic code generation affecting ui_abonnentensuche.h.
Thus when compiling the application you may run in the following compiler errors (or similar):
Fehler: 'PlaceholderText' is not a member of 'QPalette'
         palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
The only fix so far is to just comment out or delete the lines in question.

You can manually use mysqldump for backups as follows (from the terminal):
C:\blabla>mysqldump -u Sal -p antonius > backup_file.sql
or alternatively use the built in "BACKUP" button on the Abonnentensuche (F4) tab.

Restore a backup as follows:
C:\blabla>mysqldump -u Sal -p antonius < backup_file.sql
