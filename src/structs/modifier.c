typedef struct Modifier
{
    Matrix (*addRows)(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple);
    Matrix (*subtractRows)(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple);
    Matrix (*multiplyConstant)(Matrix matrix, int rowNum, float multiple);
    Matrix (*divideConstant)(Matrix matrix, int rowNum, float dividend);
    Matrix (*swapRows)(Matrix initMatrix, int primaryRowNum, int secondaryRowNum);

} Modifier;

Matrix addRowsCore(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple)
{
    for (int j = 0; j < ROW_COUNT; j++)
    {
        if (j == primaryRowNum)
        {
            for (int i = 0; i < COLUMN_COUNT; i++)
            {
                matrix.values[j][i] = matrix.values[j][i] + matrix.values[secondaryRowNum][i] * multiple;

                printf("Matrix add C%d: R%d -> R%d - R%d * %f\n", i, j, j, secondaryRowNum, multiple);
            }
        }
    }
    return matrix;
}

Matrix subtractRowsCore(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple)
{
    {
        for (int j = 0; j < ROW_COUNT; j++)
        {
            if (j == primaryRowNum)
            {
                for (int i = 0; i < COLUMN_COUNT; i++)
                {
                    matrix.values[j][i] = matrix.values[j][i] - matrix.values[secondaryRowNum][i] * multiple;

                    printf("Matrix subtract C%d: R%d -> R%d - R%d * %f\n", i, j, j, secondaryRowNum, multiple);
                }
            }
        }
        return matrix;
    }
}

Matrix multiplyConstantCore(Matrix matrix, int rowNum, float multiple)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (i == rowNum)
        {
            for (int j = 0; j < COLUMN_COUNT; j++)
            {
                matrix.values[rowNum][j] = matrix.values[rowNum][j] * multiple;

                printf("Matrix multiply C%d: R%d -> R%d * %f\n", j, i, i, multiple);
            }
        }
    }
    return matrix;
}

Matrix divideConstantCore(Matrix matrix, int rowNum, float dividend)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (i == rowNum)
        {
            for (int j = 0; j < COLUMN_COUNT; j++)
            {
                matrix.values[rowNum][j] = matrix.values[rowNum][j] / dividend;
                printf("Matrix divide C%d: R%d -> R%d / %f\n", j, i, i, dividend);
            }
        }
    }
    return matrix;
}

Matrix swapRowsCore(Matrix matrix, int primaryRowNum, int secondaryRowNum)
{
    for (int j = 0; j < ROW_COUNT; j++)
    {
        if (j == secondaryRowNum)
        {
            for (int i = 0; i < COLUMN_COUNT; i++)
            {
                int tempValue = matrix.values[secondaryRowNum][i];
                matrix.values[secondaryRowNum][i] = matrix.values[primaryRowNum][i];
                matrix.values[primaryRowNum][i] = tempValue;

                printf("Matrix swap C%d: R%d <-> R%d\n", i, primaryRowNum, secondaryRowNum);
            }
        }
    }

    printMatrixCore(matrix);
    return matrix;
}

Modifier buildModifier()
{
    Modifier newModifier = (Modifier){
        .addRows = addRowsCore,
        .subtractRows = subtractRowsCore,
        .multiplyConstant = multiplyConstantCore,
        .divideConstant = divideConstantCore,
        .swapRows = swapRowsCore};

    return newModifier;
}