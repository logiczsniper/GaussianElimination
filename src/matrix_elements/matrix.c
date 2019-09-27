/**
 * @brief  a list of Row structs to represent a 2D array object.
 * @see    row.c
 * @retval None
 */
typedef struct Matrix
{
    Row values[ROW_COUNT];
} Matrix;
