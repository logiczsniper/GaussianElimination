#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ROW_COUNT 5
#define COLUMN_COUNT 10

#include "src/matrix_elements/row.c"
#include "src/matrix_elements/matrix.c"
#include "src/matrix_elements/tuple.c"
#include "src/structs/modifier.c"
#include "src/structs/printer.c"
#include "src/structs/toolkit.c"
#include "src/structs/converter.c"

void main()
{
    /**
     * Takes a matrix with 
     * 5 rows &
     * 10 columns.
     * This is, by Gaussian elimination, 
     * converted to row echelon form.
     * Furthermore, it is converted
     * to reduced row echelon form.
     **/

    Matrix matrix = (Matrix){.values = {{4, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {8, 6, 2, 12, 0, 0, 4, 0, 0, 0},
                                        {4, 2, 8, 6, 0, 0, 0, 14, 0, 0},
                                        {0, 6, 4, 10, 8, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 8, 0, 0, 0}}};

    // Build converter struct.
    Converter converter = buildConverter();

    // Convert to Row Echelon Form (REF).
    matrix = converter.toREF(matrix);

    // Convert to Reduced Row Echelon Form (RREF).
    matrix = converter.toRREF(matrix);
}
