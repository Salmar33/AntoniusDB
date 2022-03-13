#include "columnwidthposx.h"

ColumnWidthPosX::ColumnStr::ColumnStr(unsigned int width, QString columnName)
{
    this->width = width;
    this->columnName = columnName;
}

bool ColumnWidthPosX::ColumnStr::operator==(struct ColumnWidthPosX::ColumnStr columnStr) const
{
    return (this->width == columnStr.width) && (QString::compare(this->columnName, columnStr.columnName) == 0);
}

ColumnWidthPosX::ColumnWidthPosX()
{
    ;
}

ColumnWidthPosX::~ColumnWidthPosX()
{
    ;
}


/**
 * @brief ColumnWidthPoxX::Append appends an element of type ColumnStr to the internal list
 * @param width Width of the respective column
 * @param columnName Name of the respective column
 */
void ColumnWidthPosX::Append(unsigned int width, QString columnName)
{
    widthList.append(ColumnStr(width, columnName));
}


/**
 * @brief ColumnWidthPoxX::Append appends an element of type ColumnStr to the internal list
 * @param columnStr Element to be stored in the list
 */
void ColumnWidthPosX::Append(ColumnStr columnStr)
{
    widthList.append(columnStr);
}


/**
 * @brief ColumnWidthPosX::CalcPosX Calculates the x coordinate of the column \c columnName
 * @param columnName Name of the column to calculate the x position for
 * @return The x position of the corresponding column or -1 if it was not found in the list
 */
int ColumnWidthPosX::CalcPosX(QString columnName)
{
    int returnWidth = -1;

    for(int index = 0; index < widthList.size(); index++)
    {
        if(QString::compare(widthList.at(index).columnName, columnName) == 0)
        {
            returnWidth = 0;
            for(int z = 0; z < index; z++)
            {
                returnWidth += widthList.at(z).width;
            }
        }
    }

    return returnWidth;
}

/**
 * @brief ColumnWidthPosX::CalcPosX Calculates the x coordinate of the column \c columnName
 * @param columnStr ColumnStr element of the column to calculate the x position for
 * @return The x position of the corresponding column or -1 if it was not found in the list
 */
int ColumnWidthPosX::CalcPosX(struct ColumnStr columnStr)
{
    int index = widthList.indexOf(columnStr);
    int returnWidth = 0;

    // if the element was not found in the list
    if(index == -1)
        return -1;

    for(int z = 0; z < index; z++)
    {
        returnWidth += widthList.at(z).width;
    }

    return returnWidth;
}

/**
 * @brief ColumnWidthPosX::CalcPosX Calculates the x coordinate of the column at position \c columnIndex
 * @param columnIndex index of the column to calculate the x position for
 * @return The x position of the corresponding column or -1 if columnIndex is greater than the size of the list
 */
int ColumnWidthPosX::CalcPosX(unsigned int columnIndex)
{
    int returnWidth = 0;

    if(columnIndex > static_cast<unsigned int>(widthList.size()))
    {
        return -1;
    }

    for(int z = 0; static_cast<unsigned int>(z) < columnIndex; z++)
    {
        returnWidth += widthList.at(z).width;
    }

    return returnWidth;
}
