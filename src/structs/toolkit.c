typedef struct Toolkit
{
    int (*getZeroCount)(Row row, bool leading);
    bool (*areZerosSorted)(Matrix matrix, bool leading);
    Tuple (*getPivotCoords)(Matrix matrix, int beyondRow);
    Matrix (*sortByLeadingZero)(Matrix matrix, Modifier modifier);

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

Matrix sortByLeadingZeroCore(Matrix matrix, Modifier modifier)
{
    while (!(areZerosSortedCore(matrix, true)))
    {
        for (int i = 1; i < ROW_COUNT; i++)
        {
            Row row;
            Row previousRow;

            memcpy(row, matrix.values[i], sizeof(row));
            memcpy(previousRow, matrix.values[i - 1], sizeof(previousRow));

            if (getZeroCountCore(row, true) < getZeroCountCore(previousRow, true))
            {
                // If there are more leading zeros in the upper row (row) than there
                // are in the lower row (previousRow), swap the rows.
                matrix = modifier.swapRows(matrix, i, i - 1);
            }
        }
    }

    return matrix;
}

Toolkit buildToolkit()
{
    Toolkit newToolkit = (Toolkit){
        .getZeroCount = getZeroCountCore,
        .areZerosSorted = areZerosSortedCore,
        .getPivotCoords = getPivotCoordsCore,
        .sortByLeadingZero = sortByLeadingZeroCore};

    return newToolkit;
}