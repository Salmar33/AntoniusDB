#ifndef COLUMNWIDTHPOSX_H
#define COLUMNWIDTHPOSX_H

#include <QString>
#include <QList>

/**
 * @brief The ColumnWidthPosX class provides a function, which outputs the x coordinate of a column considering the width of all the columns next to it (to its left)
 * The elements are stored in a list of ColumnStr elements
 * An object of this class therefore provides the x position of elements by summing the width of elements to their left.
 */
class ColumnWidthPosX
{
public:
    struct ColumnStr
    {
        ColumnStr(unsigned int, QString);
        bool operator==(ColumnWidthPosX::ColumnStr);

        unsigned int width; QString columnName;
    };
    ColumnWidthPosX();
    ~ColumnWidthPosX();
    void Append(unsigned int width, QString columnName);
    void Append(ColumnStr columnStr);
    int CalcPosX(QString columnName);
    int CalcPosX(struct ColumnStr columnStr);
    int CalcPosX(unsigned int columnIndex);

private:
    QList<struct ColumnStr> widthList;
};

#endif // COLUMNWIDTHPOSX_H
