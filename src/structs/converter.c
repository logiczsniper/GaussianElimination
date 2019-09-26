typedef struct Converter
{
    Matrix (*toREF)(Matrix matrix);
} Converter;

Matrix sortByLeadingZero(Matrix matrix, Toolkit toolkit, Modifier modifier);

Matrix toREFCore(Matrix initMatrix)
{

    // Create supporting structs.
    Modifier modifier = buildModifier();
    Printer printer = buildPrinter();
    Toolkit toolkit = buildToolkit();

    // Start by copying values of initMatrix to a matrix
    // I can modify.
    Matrix matrix = initMatrix;

    // Check if all rows are zero
    bool foundNonZeroRow = false;

    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (toolkit.getZeroCount(matrix.values[i], false) != COLUMN_COUNT)
        {
            // This row contains non zero values.
            foundNonZeroRow = true;
        }
    }

    if (!foundNonZeroRow)
    {
        // The matrix contains nothing but zeros.
        return matrix;
    }

    // The matrix contains non zero values. Continue;
    // Sort matrix so that the rows with the most zeros
    // are at the bottom and the rows with the least
    // zeros are at the top.
    // Start i = 1 as we need to take rows two at a time;
    // if i = 0 we cannot get the previous row to compare it.

    while (!(toolkit.areZerosSorted(matrix, false)))
    {
        for (int i = 1; i < ROW_COUNT; i++)
        {
            Row row;
            Row previousRow;

            memcpy(row, matrix.values[i], sizeof(row));
            memcpy(previousRow, matrix.values[i - 1], sizeof(previousRow));

            if (toolkit.getZeroCount(row, false) < toolkit.getZeroCount(previousRow, false))
            {
                // If there are more zeros in the upper row (row) than there
                // are in the lower row (previousRow), swap the rows.
                matrix = modifier.swapRows(matrix, i, i - 1);
            }
        }
    }

    // Now we must arrange the rows so that the number of leading 0s
    // increases as you go down the matrix (vertically).
    matrix = sortByLeadingZero(matrix, toolkit, modifier);

    // Ensuring that the pivot coords move down one row each time.
    // As each time a pivot is found, the values below are turned to zeros,
    // there is no need to ensure the column is tracked. A zero value will never
    // be picked as a pivot.
    int beyondRow = -1;

    for (int column = 0; column < COLUMN_COUNT; column++)
    {
        // Find the first number which will be made into the first pivot.
        Tuple pivotCoords = toolkit.getPivotCoords(matrix, beyondRow);

        beyondRow++;

        // Divide the first row by the value of the pivot to make it 1, if
        // it is not already one.
        if (matrix.values[pivotCoords.row][pivotCoords.column] != 1.0F && matrix.values[pivotCoords.row][pivotCoords.column] != 0.0F)
        {
            matrix = modifier.divideConstant(matrix, pivotCoords.row, matrix.values[pivotCoords.row][pivotCoords.column]);
        }

        // Make everything below the created leading pivot a 0.

        int columnNum = pivotCoords.column;
        int rowNum = pivotCoords.row;
        for (int i = 0; i < ROW_COUNT; i++)
        {
            for (int j = 0; j < COLUMN_COUNT; j++)
            {
                if (j == columnNum && i != rowNum)
                {
                    // We are only modifying this column.
                    float value = matrix.values[i][j];

                    // If the value is not zero, perform row operation to
                    // make it 0.
                    if (value > 0.0F)
                    {
                        matrix = modifier.subtractRows(matrix, i, pivotCoords.row, fabsf(value));
                    }
                    else if (value < 0.0F)
                    {
                        matrix = modifier.addRows(matrix, i, pivotCoords.row, fabsf(value));
                    }
                }
            }
        }
        printer.printMatrix(matrix);
    }

    // Run the leading zeros algorithm again
    // Now we must arrange the rows so that the number of leading 0s
    // increases as you go down the matrix (vertically).
    matrix = sortByLeadingZero(matrix, toolkit, modifier);

    printer.printMatrix(matrix);
}

Matrix sortByLeadingZero(Matrix matrix, Toolkit toolkit, Modifier modifier)
{
    while (!(toolkit.areZerosSorted(matrix, true)))
    {
        for (int i = 1; i < ROW_COUNT; i++)
        {
            Row row;
            Row previousRow;

            memcpy(row, matrix.values[i], sizeof(row));
            memcpy(previousRow, matrix.values[i - 1], sizeof(previousRow));

            if (toolkit.getZeroCount(row, true) < toolkit.getZeroCount(previousRow, true))
            {
                // If there are more leading zeros in the upper row (row) than there
                // are in the lower row (previousRow), swap the rows.
                matrix = modifier.swapRows(matrix, i, i - 1);
            }
        }
    }

    return matrix;
}

Converter buildConverter()
{
    Converter newConverter = (Converter){
        .toREF = toREFCore};

    return newConverter;
}