/**
 * @brief  Holds misc. functions used in the conversion.
 * @retval None
 */
typedef struct Toolkit
{
    int (*getZeroCount)(Row row, bool leading);
    bool (*areZerosSorted)(Matrix matrix, bool leading);
    Tuple (*getPivotCoords)(Matrix matrix, int beyondRow);
    Matrix (*sortByLeadingZero)(Matrix matrix, Modifier modifier);

} Toolkit;

/**
 * @brief  counts number of zeros in a row.
 * @note   output depends on value of leading parameter.
 * @param  row: the row which contains the zeros to be counted.
 * @param  leading: if true, will stop counting when a non zero value is found.
 * @retval count: number of 0s (leading or non leading based on param leading).
 */
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

/**
 * @brief  checks if the amount of zeros (or leading zeros) increases as you go down the matrix.
 * @note   depends on parameter leading.
 * @param  matrix: the matrix to assert.
 * @param  leading: if true, checks that the leading zeros are sorted instead of all zeros.
 * @retval bool sorted: is the zeros in the correct orientation in the matrix.
 */
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

/**
 * @brief  get the coordinates of a leading pivot (to be).
 * @param  matrix: contains the pivot options.
 * @param  beyondRow: the row of the selected pivot CANNOT be less than this value.
 *                    this ensures that the leading pivot moves over one row each time.
 * @retval Tuple coords of the pivot located.
 */
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

/**
 * @brief  sorts the matrix based on the number of leading zeros in each row.
 * @note   requires use of the modifier.
 * @param  matrix: the matrix to be sorted.
 * @param  modifier: an initialised modifier struct.
 * @retval the sorted Matrix.
 */
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