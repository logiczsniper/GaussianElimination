#include <stdio.h>
#define ROW_COUNT 5
#define COLUMN_COUNT 10

typedef int Slot;

typedef struct Row
{
    Slot (*getColumnValue)(struct Row, int columnNum);

    Slot columnOne;
    Slot columnTwo;
    Slot columnThree;
    Slot columnFour;
    Slot columnFive;
    Slot columnSix;
    Slot columnSeven;
    Slot columnEight;
    Slot columnNine;
    Slot columnTen;
} Row, rowOne, rowTwo, rowThree, rowFour, rowFive;

Slot getColumnValueCore(Row row, int columnNum)
{
    Slot selectedValue;

    switch (columnNum)
    {
    case 1:
        selectedValue = row.columnOne;
        break;
    case 2:
        selectedValue = row.columnTwo;
        break;
    case 3:
        selectedValue = row.columnThree;
        break;
    case 4:
        selectedValue = row.columnFour;
        break;
    case 5:
        selectedValue = row.columnFive;
        break;
    case 6:
        selectedValue = row.columnSix;
        break;
    case 7:
        selectedValue = row.columnSeven;
        break;
    case 8:
        selectedValue = row.columnEight;
        break;
    case 9:
        selectedValue = row.columnNine;
        break;
    case 10:
        selectedValue = row.columnTen;
        break;
    default:
        break;
    }
}

Row buildRow(int values[COLUMN_COUNT])
{
    Row newRow = (Row){
        .columnOne = values[0],
        .columnTwo = values[1],
        .columnThree = values[2],
        .columnFour = values[3],
        .columnFive = values[4],
        .columnSix = values[5],
        .columnSeven = values[6],
        .columnEight = values[7],
        .columnNine = values[8],
        .columnTen = values[9],
        .getColumnValue = &getColumnValueCore};
    return newRow;
}
