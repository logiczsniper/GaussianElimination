typedef struct Toolkit
{
    int (*getZeroCount)(Row row);
    int (*getLeadingZeroCount)(Row row);
    bool (*zerosAtBottom)(Matrix matrix);
    bool (*leadingZerosAtTop)(Matrix matrix);
    Tuple (*getPivotCoords)(Matrix matrix, int beyondRow);

} Toolkit;

int getZeroCountCore(Row row)
{
    int count = 0;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        if (row[i] == 0)
        {
            count++;
        }
    }

    return count;
}

int getLeadingZeroCountCore(Row row)
{
    int count = 0;

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        if (row[i] == 0)
        {
            count++;
        }
        else
        {
            break;
        }
    }

    return count;
}

bool leadingZerosAtTopCore(Matrix matrix)
{
    int zeroCountOne = getLeadingZeroCountCore(matrix.values[0]);
    int zeroCountTwo = getLeadingZeroCountCore(matrix.values[1]);
    int zeroCountThree = getLeadingZeroCountCore(matrix.values[2]);
    int zeroCountFour = getLeadingZeroCountCore(matrix.values[3]);
    int zeroCountFive = getLeadingZeroCountCore(matrix.values[4]);

    return (zeroCountFive >= zeroCountFour && zeroCountFour >= zeroCountThree && zeroCountThree >= zeroCountTwo && zeroCountTwo >= zeroCountOne);
}

bool zerosAtBottomCore(Matrix matrix)
{
    int zeroCountOne = getZeroCountCore(matrix.values[0]);
    int zeroCountTwo = getZeroCountCore(matrix.values[1]);
    int zeroCountThree = getZeroCountCore(matrix.values[2]);
    int zeroCountFour = getZeroCountCore(matrix.values[3]);
    int zeroCountFive = getZeroCountCore(matrix.values[4]);

    return (zeroCountFive >= zeroCountFour && zeroCountFour >= zeroCountThree && zeroCountThree >= zeroCountTwo && zeroCountTwo >= zeroCountOne);
}

Tuple getPivotCoordsCore(Matrix matrix, int beyondRow)
{
    Tuple pivotCoords;

    for (int i = 0; i < ROW_COUNT; i++)
    {
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            if (matrix.values[i][j] != 0 && i > beyondRow)
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
        .getLeadingZeroCount = getLeadingZeroCountCore,
        .zerosAtBottom = zerosAtBottomCore,
        .leadingZerosAtTop = leadingZerosAtTopCore,
        .getPivotCoords = getPivotCoordsCore};

    return newToolkit;
}