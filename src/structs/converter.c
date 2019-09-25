typedef struct Converter
{
    Matrix (*toREF)(Matrix matrix);
    Matrix (*toRREF)(Matrix matrix);
} Converter;

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
        if (toolkit.getZeroCount(matrix.values[i]) != COLUMN_COUNT)
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

    while (!(toolkit.zerosAtBottom(matrix)))
    {
        for (int i = 1; i < ROW_COUNT; i++)
        {
            Row row;
            Row previousRow;

            memcpy(row, matrix.values[i], sizeof(row));
            memcpy(previousRow, matrix.values[i - 1], sizeof(previousRow));

            if (toolkit.getZeroCount(row) < toolkit.getZeroCount(previousRow))
            {
                // If there are more zeros in the upper row (row) than there
                // are in the lower row (previousRow), swap the rows.
                matrix = modifier.swapRows(matrix, i, i - 1);
            }
        }
    }

    // Now we must arrange the rows so that the number of leading 0s
    // increases as you go down the matrix (vertically).
    while (!(toolkit.leadingZerosAtTop(matrix)))
    {
        for (int i = 1; i < ROW_COUNT; i++)
        {
            Row row;
            Row previousRow;

            memcpy(row, matrix.values[i], sizeof(row));
            memcpy(previousRow, matrix.values[i - 1], sizeof(previousRow));

            if (toolkit.getLeadingZeroCount(row) < toolkit.getLeadingZeroCount(previousRow))
            {
                // If there are more leading zeros in the upper row (row) than there
                // are in the lower row (previousRow), swap the rows.
                matrix = modifier.swapRows(matrix, i, i - 1);
            }
        }
    }
    for (int column = 0; column < COLUMN_COUNT; column++)
    {

        int beyondRow, beyondColumn;
        beyondRow = -1;
        beyondColumn = -1;

        // Find the first number which will be made into the first pivot.
        Tuple pivotCoords = toolkit.getPivotCoords(matrix, beyondRow, beyondColumn);

        beyondRow++;
        beyondColumn++;

        // Divide the first row by the value of the pivot to make it 1.
        matrix = modifier.divideConstant(matrix, pivotCoords.row, matrix.values[pivotCoords.row][pivotCoords.column]);

        printer.printMatrix(matrix);

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
                    int value = matrix.values[i][j];

                    // If the value is not zero, perform row operation to
                    // make it 0.
                    if (value > 0)
                    {
                        matrix = modifier.subtractRows(matrix, i, pivotCoords.row, abs(value));
                    }
                    else if (value < 0)
                    {
                        matrix = modifier.addRows(matrix, i, pivotCoords.row, abs(value));
                    }
                }
            }
        }

        printer.printMatrix(matrix);
    }

    // Repeat step 2 but for c1 of rN, so c1 = [1, 0, 0, ... 0]

    // Repeat previous steps for cN, but incrementing the first column each
    // iteration so the pivot values
}

Matrix toRREFCore(Matrix matrix)
{
}

Converter buildConverter()
{
    Converter newConverter = (Converter){
        .toREF = toREFCore,
        .toRREF = toRREFCore};

    return newConverter;
}