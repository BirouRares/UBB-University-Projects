public class InitializeTask
{

    public static ThreadMatrix initRowTask(int index, Matrix matrix1, Matrix matrix2, Matrix result, int threadsNumber)
    { //Initializes a RowTask object, which represents a unit of work for matrix multiplication.

        int positions = result.getRows() * result.getColumns(); // number of positions in the result matrix

        int defaultNumberOfPositionsPerThread = positions / threadsNumber; // number of positions that each thread should fill

        int numberOfThreadsWithExtraPos = positions % threadsNumber; // number of threads that should fill one more position

        int positionsToBeFilled = defaultNumberOfPositionsPerThread;  // number of positions that the current thread should fill

        if(index < numberOfThreadsWithExtraPos){
            positionsToBeFilled++;
        }

        int startRow = positionsToBeFilled * index / result.getColumns();
        int startCol = positionsToBeFilled * index % result.getColumns();


        if (index == threadsNumber - 1)
        {
            positionsToBeFilled += numberOfThreadsWithExtraPos;
        }

        return new RowTask(startRow, startCol, positionsToBeFilled, matrix1, matrix2, result);

    }

    public static int computeMatrixElement(Matrix matrix1, Matrix matrix2, int row, int column)
    {
        int result = 0;
        if (row < matrix1.getRows() && column < matrix2.getColumns())
        {
            int i = 0;
            while (i < matrix1.getColumns())
            {
                result = result + matrix1.getElemFromPos(row, i) * matrix2.getElemFromPos(i, column);
                i++;
            }
        }
        else
        {
            throw new IllegalArgumentException();
        }

        return result;
    }
}