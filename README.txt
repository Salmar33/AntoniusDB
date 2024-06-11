AntoniusDB is a database client application.
It provides a GUI to interface with a mariaDB database specifically designed for address management of subscribers of the magazine "Antonius".

This software uses the Qt framework and is published under the GNU General Public License - see "License.txt"

In ".\_dll file for 32bit mingw" you'll find the necessary .dll file and a separate README.txt describing how you enable Qt to work with mariaDB (mysql).

In case you want to further develop and then redistribute this application, on windows plattforms the easiest way to deploy it is to call "windeployqt <path to application binary>"
As it turns out "windeployqt" does not work reliably.
A good workaround is to temporarily change the Qt installation folder's name "QT" to for example "QT-bak" and copy all .dll files from:
	-) <drive letter>:\Qt\<QT version>\<compiler_name>\bin\
and all content from
	-) <drive letter>:\Qt\<QT version>\<compiler_name>\plugins\
Then execute the application and attempt to delete all .dll files while the program is running.
Only the ones, which are not being used, will effectively be deleted.
Afterwards rename the Qt installation folder again to "QT".

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
