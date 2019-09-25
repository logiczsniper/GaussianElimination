#define ROW_COUNT 5
#define COLUMN_COUNT 10

#include "args_enum.c"
#include "../src/matrix_elements/row.c"
#include "../src/matrix_elements/matrix.c"

enum ArgStatus checkMatrix(long matrixSize)
{
    /**
     * Ensure that the input matrix 
     * contains 5 rows and 
     * 10 columns.
     * If either of these are not true, 
     * return 0.
     **/

    int row_size[10];
    int row_count = matrixSize / sizeof(row_size);

    if (row_count != ROW_COUNT)
    {
        return FAIL;
    }

    for (int i = 0; i < ROW_COUNT; i++)
    {
        int column_count = sizeof(row_size) / sizeof(int);

        if (column_count != COLUMN_COUNT)
        {
            return FAIL;
        }
    }

    return PASS;
}

int main(void)
{
    Matrix matrix = (Matrix){.values = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 2, 0, 6, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 3, 3, 8, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};

    enum ArgStatus argStatus = checkMatrix(sizeof(matrix));

    // Check to ensure an appropiate matrix is provided.
    if (argStatus == FAIL)
    {
        printf("FAIL");
    }
    else if (argStatus == PASS)
    {
        printf("PASS");

        // If valid, begin the conversion to row echelon form.
        convertToREF(matrix);
    }
}