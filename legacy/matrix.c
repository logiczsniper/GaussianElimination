#include <stdio.h>
#include "row.c"
#include "column.c"

#define ROW_COUNT 5
#define COLUMN_COUNT 10

typedef struct Matrix
{
    Row (*getRow)(struct Matrix, int rowNum);
    Column (*getColumn)(struct Matrix, int columnNum);
    Slot (*getSlot)(struct Matrix, int rowNum, int columnNum);

    Row rowOne[COLUMN_COUNT];
    Row rowTwo[COLUMN_COUNT];
    Row rowThree[COLUMN_COUNT];
    Row rowFour[COLUMN_COUNT];
    Row rowFive[COLUMN_COUNT];
} Matrix;

Slot getSlotCore(struct Matrix matrix, int rowNum, int columnNum)
{
    Slot selectedSlot;
    Row selectedRow = matrix.getRow(matrix, rowNum);
    selectedSlot = selectedRow.getColumnValue(selectedRow, columnNum);
    return selectedSlot;
}

Row getRowCore(struct Matrix matrix, int rowNum)
{
    Row selectedRow;

    switch (rowNum)
    {
    case 1:
        selectedRow = *matrix.rowOne;
        break;
    case 2:
        selectedRow = *matrix.rowTwo;
        break;
    case 3:
        selectedRow = *matrix.rowThree;
        break;
    case 4:
        selectedRow = *matrix.rowFour;
        break;
    case 5:
        selectedRow = *matrix.rowFive;
        break;

    default:
        break;
    }

    return selectedRow;
}

Column getColumnCore(struct Matrix matrix, int columnNum)
{
    Column selectedColumn;

    switch (columnNum)
    {
    case 1:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnOne,
            .rowTwo = matrix.getRow(matrix, 2).columnOne,
            .rowThree = matrix.getRow(matrix, 3).columnOne,
            .rowFour = matrix.getRow(matrix, 4).columnOne,
            .rowFive = matrix.getRow(matrix, 5).columnOne,
            .getRowValue = &getRowValueCore};
        break;
    case 2:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnTwo,
            .rowTwo = matrix.getRow(matrix, 2).columnTwo,
            .rowThree = matrix.getRow(matrix, 3).columnTwo,
            .rowFour = matrix.getRow(matrix, 4).columnTwo,
            .rowFive = matrix.getRow(matrix, 5).columnTwo,
            .getRowValue = &getRowValueCore};
        break;
    case 3:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnThree,
            .rowTwo = matrix.getRow(matrix, 2).columnThree,
            .rowThree = matrix.getRow(matrix, 3).columnThree,
            .rowFour = matrix.getRow(matrix, 4).columnThree,
            .rowFive = matrix.getRow(matrix, 5).columnThree,
            .getRowValue = &getRowValueCore};
        break;
    case 4:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnFour,
            .rowTwo = matrix.getRow(matrix, 2).columnFour,
            .rowThree = matrix.getRow(matrix, 3).columnFour,
            .rowFour = matrix.getRow(matrix, 4).columnFour,
            .rowFive = matrix.getRow(matrix, 5).columnFour,
            .getRowValue = &getRowValueCore};
        break;
    case 5:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnFive,
            .rowTwo = matrix.getRow(matrix, 2).columnFive,
            .rowThree = matrix.getRow(matrix, 3).columnFive,
            .rowFour = matrix.getRow(matrix, 4).columnFive,
            .rowFive = matrix.getRow(matrix, 5).columnFive,
            .getRowValue = &getRowValueCore};
        break;
    case 6:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnSix,
            .rowTwo = matrix.getRow(matrix, 2).columnSix,
            .rowThree = matrix.getRow(matrix, 3).columnSix,
            .rowFour = matrix.getRow(matrix, 4).columnSix,
            .rowFive = matrix.getRow(matrix, 5).columnSix,
            .getRowValue = &getRowValueCore};
        break;
    case 7:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnSeven,
            .rowTwo = matrix.getRow(matrix, 2).columnSeven,
            .rowThree = matrix.getRow(matrix, 3).columnSeven,
            .rowFour = matrix.getRow(matrix, 4).columnSeven,
            .rowFive = matrix.getRow(matrix, 5).columnSeven,
            .getRowValue = &getRowValueCore};
        break;
    case 8:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnEight,
            .rowTwo = matrix.getRow(matrix, 2).columnEight,
            .rowThree = matrix.getRow(matrix, 3).columnEight,
            .rowFour = matrix.getRow(matrix, 4).columnEight,
            .rowFive = matrix.getRow(matrix, 5).columnEight,
            .getRowValue = &getRowValueCore};
        break;
    case 9:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnNine,
            .rowTwo = matrix.getRow(matrix, 2).columnNine,
            .rowThree = matrix.getRow(matrix, 3).columnNine,
            .rowFour = matrix.getRow(matrix, 4).columnNine,
            .rowFive = matrix.getRow(matrix, 5).columnNine,
            .getRowValue = &getRowValueCore};
        break;
    case 10:
        selectedColumn = (Column){
            .rowOne = matrix.getRow(matrix, 1).columnTen,
            .rowTwo = matrix.getRow(matrix, 2).columnTen,
            .rowThree = matrix.getRow(matrix, 3).columnTen,
            .rowFour = matrix.getRow(matrix, 4).columnTen,
            .rowFive = matrix.getRow(matrix, 5).columnTen,
            .getRowValue = &getRowValueCore};
        break;
    default:
        break;
    }

    return selectedColumn;
}

struct Matrix buildMatrix()
{
    int values[COLUMN_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct Matrix newMatrix = (struct Matrix){
        .rowOne = buildRow(values),
        .rowTwo = buildRow(values),
        .rowThree = buildRow(values),
        .rowFour = buildRow(values),
        .rowFive = buildRow(values),
        .getRow = &getRowCore,
        .getColumn = &getColumnCore,
        .getSlot = &getSlotCore};

    return newMatrix;
}

int main()
{
    struct Matrix myMatrix = buildMatrix();
    Slot value = myMatrix.getSlot(myMatrix, 3, 7);
    printf("%d", value);

    return 0;
}