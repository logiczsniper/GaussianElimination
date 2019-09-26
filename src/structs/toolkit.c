typedef struct Toolkit
{
    int (*getZeroCount)(Row row, bool leading);
    bool (*areZerosSorted)(Matrix matrix, bool leading);
    Tuple (*getPivotCoords)(Matrix matrix, int beyondRow);

} Toolkit;

int getZeroCountCore(Row row, bool leading)
{
    int count = 0;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        if (row[i] == 0.0F)
        {
            count++;
        }
        else if (leading)
        {
            break;
        }
    }
    return count;
}

bool areZerosSortedCore(Matrix matrix, bool leading)
{
    bool sorted = true;

    for (int i = 1; i < ROW_COUNT; i++)
    {
        int currentRowZeroCount = getZeroCountCore(matrix.values[i], leading);
        int previousRowZeroCount = getZeroCountCore(matrix.values[i - 1], leading);

        if (currentRowZeroCount < previousRowZeroCount)
        {
            // There are more zeros in the row above.
            sorted = false;
        }
    }

    return sorted;

    /*     int zeroCountOne = getZeroCountCore(matrix.values[0], leading);
    int zeroCountTwo = getZeroCountCore(matrix.values[1], leading);
    int zeroCountThree = getZeroCountCore(matrix.values[2], leading);
    int zeroCountFour = getZeroCountCore(matrix.values[3], leading);
    int zeroCountFive = getZeroCountCore(matrix.values[4], leading);

    return (zeroCountFive >= zeroCountFour && zeroCountFour >= zeroCountThree && zeroCountThree >= zeroCountTwo && zeroCountTwo >= zeroCountOne); */
}

Tuple getPivotCoordsCore(Matrix matrix, int beyondRow)
{
    Tuple pivotCoords;

    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (matrix.values[i][j] != 0.0F && i > beyondRow)
            {
                pivotCoords = (Tuple){i, j};
                return pivotCoords;
                printf("Pivot coords found:\nR%d - C%d\n", i, j);
            }
        }
    }
}

Toolkit buildToolkit()
{
    Toolkit newToolkit = (Toolkit){
        .getZeroCount = getZeroCountCore,
        .areZerosSorted = areZerosSortedCore,
        .getPivotCoords = getPivotCoordsCore};

    return newToolkit;
}