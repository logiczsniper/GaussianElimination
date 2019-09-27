/**
 * @brief  responsible for modifying the matrix.
 * @note   completes the elementary row operations.
 * @retval None
 */
typedef struct Modifier
{
    Matrix (*addRows)(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple);
    Matrix (*subtractRows)(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple);
    Matrix (*multiplyConstant)(Matrix matrix, int rowNum, float multiple);
    Matrix (*divideConstant)(Matrix matrix, int rowNum, float dividend);
    Matrix (*swapRows)(Matrix initMatrix, int primaryRowNum, int secondaryRowNum);

} Modifier;

/**
 * @brief  adds a multiple of a secondary row to a primary row.
 * @note   multiple should not be 0.
 * @param  matrix: the matrix where the rows are to be found.
 * @param  primaryRowNum: the row which the operation will by applied to.
 * @param  secondaryRowNum: the row which will be multiplied by the multiple and then added to the primary row.
 * @param  multiple: the value to multiply with the secondary row. Should be equal to the value you want to make a 0.
 * @retval Matrix with the operation completed.
 */
Matrix addRowsCore(Matrix matrix, int primaryRowNum, int secondaryRowNum, float multiple)
{
    for (int j = 0; j < ROW_COUNT; j++)
    {
        if (j == primaryRowNum)
        {
            for (int i = 0; i < COLUMN_COUNT; i++)
            {
                matrix.values[j][i] = matrix.values[j][i] + matrix.values[secondaryRowNum][i] * multiple;
            }
        }
    }

    printf("Matrix add: R%d -> R%d + R%d * %f\n", primaryRowNum, primaryRowNum, secondaryRowNum, multiple);
    return matrix;
}

/**
 * @brief  subtracts a multiple of a secondary row to a primary row.
 * @note   multiple should not be 0.
 * @param  matrix: the matrix where the rows are to be found.
 * @param  primaryRowNum: the row which the operation will by applied to.
 * @param  secondaryRowNum: the row which will be multiplied by the multiple and then subtracrted from the primary row.
 * @param  multiple: the value to multiply with the secondary row. Should be equal to the value you want to make a 0.
 * @retval Matrix with the operation completed.
 */
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
                }
            }
        }
        printf("Matrix subtract: R%d -> R%d - R%d * %f\n", primaryRowNum, primaryRowNum, secondaryRowNum, multiple);
        return matrix;
    }
}

/**
 * @brief  multiplies a row by a non zero constant.
 * @note   constant cannot equal 0.
 * @param  matrix: the matrix where the row is found.
 * @param  rowNum: the index of the row which the operation will be completed on.
 * @param  multiple: the number to multiply in.
 * @retval Matrix with operation completed.
 */
Matrix multiplyConstantCore(Matrix matrix, int rowNum, float multiple)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (i == rowNum)
        {
            for (int j = 0; j < COLUMN_COUNT; j++)
            {
                matrix.values[rowNum][j] = matrix.values[rowNum][j] * multiple;
            }
        }
    }
    printf("Matrix multiply: R%d -> R%d * %f\n", rowNum, rowNum, multiple);
    return matrix;
}

/**
 * @brief  divides a row by a non zero constant.
 * @note   constant cannot equal 0.
 * @param  matrix: the matrix where the row is found.
 * @param  rowNum: the index of the row which the operation will be completed on.
 * @param  multiple: the number to divide in.
 * @retval Matrix with operation completed.
 */
Matrix divideConstantCore(Matrix matrix, int rowNum, float dividend)
{
    for (int i = 0; i < ROW_COUNT; i++)
    {
        if (i == rowNum)
        {
            for (int j = 0; j < COLUMN_COUNT; j++)
            {
                matrix.values[rowNum][j] = matrix.values[rowNum][j] / dividend;
            }
        }
    }

    printf("Matrix divide: R%d -> R%d / %f\n", rowNum, rowNum, dividend);
    return matrix;
}

/**
 * @brief  swaps the position of two rows in the matrix.
 * @param  matrix: the matrix where the rows are found.
 * @param  primaryRowNum: the first row index.
 * @param  secondaryRowNum: the second row index.
 * @retval Matrix with the rows found at the aforementioned indices swapped.
 */
Matrix swapRowsCore(Matrix matrix, int primaryRowNum, int secondaryRowNum)
{
    for (int j = 0; j < ROW_COUNT; j++)
    {
        if (j == secondaryRowNum)
        {
            for (int i = 0; i < COLUMN_COUNT; i++)
            {
                float tempValue = matrix.values[secondaryRowNum][i];
                matrix.values[secondaryRowNum][i] = matrix.values[primaryRowNum][i];
                matrix.values[primaryRowNum][i] = tempValue;
            }
        }
    }

    printf("Matrix swap: R%d <-> R%d\n", primaryRowNum, secondaryRowNum);
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