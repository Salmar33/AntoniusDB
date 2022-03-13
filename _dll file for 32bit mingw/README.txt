To enable working with mysql (and the mingw 32 bit compiler in Qt) put the file libmysql.dll it into the directory of your Qt installation that looks something like this
G:\QT\5.11.1\mingw53_32\bin

Note that libmysql.dll is actually libmariadb.dll just renamed.

IMPORTANT:
If that does not work then try the following:

in "G:\Qt\6.1.2\Src" call:
configure.bat -sql-mysql -- -DMySQL_INCLUDE_DIR="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\include" -DMySQL_LIBRARY="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\lib\libmariadb.lib"



with mingw81_64:
qt-cmake -G Ninja "G:\QT\6.1.2\Src\qtbase\src\plugins\sqldrivers" -DCMAKE_INSTALL_PREFIX="G:\QT\6.1.2\mingw81_64" -DMySQL_INCLUDE_DIR="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\include" -DMySQL_LIBRARY="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\lib\libmariadb.lib"


with msvc2019_64:
qt-cmake -G Ninja "G:\QT\6.1.2\Src\qtbase\src\plugins\sqldrivers" -DCMAKE_INSTALL_PREFIX="G:\QT\6.1.2\msvc2019_64" -DMySQL_INCLUDE_DIR="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\include" -DMySQL_LIBRARY="C:\Program Files\MariaDB\MariaDB Connector C 64-bit\lib\libmariadb.lib"


