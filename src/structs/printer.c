typedef struct Printer
{
    void (*printMatrix)(Matrix matrix);
    void (*printRow)(Row row);

} Printer;

void printMatrixCore(Matrix matrix)
{
    printf("{\n");
    for (int i = 0; i < ROW_COUNT; i++)
    {
        printf("\t{");
        for (int j = 0; j < COLUMN_COUNT; j++)
        {
            float value = matrix.values[i][j];
            printf("%6.2f", value);

            if (j != COLUMN_COUNT - 1)
            {
                printf(", ");
            }
        }
        printf("}");
        if (i != ROW_COUNT - 1)
        {
            printf(", \n");
        }
        else
        {
            printf("\n");
        }
    }
    printf("}\n\n");
}

void printRowCore(Row row)
{
    printf("{");

    for (int i = 0; i < COLUMN_COUNT; i++)
    {
        printf("%5.1f", row[i]);
        if (i != COLUMN_COUNT - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

Printer buildPrinter()
{
    Printer newPrinter = (Printer){
        .printMatrix = printMatrixCore,
        .printRow = printRowCore};

    return newPrinter;
}