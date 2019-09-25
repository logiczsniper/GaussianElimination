#include <stdio.h>
#define ROW_COUNT 5
#define COLUMN_COUNT 10

typedef int Slot;

typedef struct Column
{
    Slot (*getRowValue)(struct Column, int rowNum);

    Slot rowOne;
    Slot rowTwo;
    Slot rowThree;
    Slot rowFour;
    Slot rowFive;

} Column, columnOne, columnTwo, columnThree, columnFour, columnFive, columnSix, columnSeven, columnEight, columnNine, columnTen;

Slot getRowValueCore(Column column, int rowNum)
{

    Slot selectedValue;

    switch (rowNum)
    {
    case 1:
        selectedValue = column.rowOne;
        break;
    case 2:
        selectedValue = column.rowTwo;
        break;
    case 3:
        selectedValue = column.rowThree;
        break;
    case 4:
        selectedValue = column.rowFour;
        break;
    case 5:
        selectedValue = column.rowFive;
        break;
    default:
        break;
    }
}