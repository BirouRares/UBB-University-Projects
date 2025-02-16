import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main
{

    private static final int rowMatrix1 = 90;
    private static final int rowMatrix2 = 90;
    private static final int colMatrix1 = 90;
    private static final int colMatrix2 = 90;

    private static final int THREAD_COUNT = 3;

    // Replace this to switch between Thread pool and classic threads approach
    private static final String THREAD_APPROACH = "THREAD_POOL"; // Options: "CLASSIC", "THREAD_POOL"

    public static void main(String[] args) {
        Matrix matrix1 = new Matrix(rowMatrix1, colMatrix1);
        Matrix matrix2 = new Matrix(rowMatrix2, colMatrix2);

        if(colMatrix1 == rowMatrix2){
            System.out.println("Start -> compute the Matrix!");

            Matrix result = new Matrix(matrix1.getRows(), matrix2.getColumns());

            matrix1.generateRandomMatrix();
            matrix2.generateRandomMatrix();

            double startTime = System.nanoTime();

            if ("CLASSIC".equals(THREAD_APPROACH))
            {
                classicThreadsCase(matrix1, matrix2, result);
            }
            else if ("THREAD_POOL".equals(THREAD_APPROACH))
            {
                threadPoolCase(matrix1, matrix2, result);
            }

            double stopTime = System.nanoTime();
            System.out.println("End -> compute the Matrix!");
            System.out.println("Elapsed time: " + (stopTime - startTime) / 1_000_000_000.0);

        }
        else
        {
            System.out.println("Cannot multiply the matrices! Ensure the first matrix's columns equal the second matrix's rows.\n");
        }
    }

    private static void threadPoolCase(Matrix matrix1, Matrix matrix2, Matrix result)
    {
        ExecutorService executorService = new ThreadPoolExecutor(
                THREAD_COUNT, THREAD_COUNT, 0L, TimeUnit.MILLISECONDS,
                new ArrayBlockingQueue<>(THREAD_COUNT, true));

        for (int i = 0; i < THREAD_COUNT; i++)
        {
            executorService.submit(InitializeTask.initRowTask(i, matrix1, matrix2, result, THREAD_COUNT));
        }

        executorService.shutdown();
        try
        {
            if (!executorService.awaitTermination(600, TimeUnit.SECONDS))
            {
                executorService.shutdownNow();
            }
            System.out.println(matrix1);
            System.out.println(matrix2);
            System.out.println("Resulted matrix: ");
            System.out.println(result);
        } catch (InterruptedException e) {
            executorService.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }

    private static void classicThreadsCase(Matrix matrix1, Matrix matrix2, Matrix result)
    {
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < THREAD_COUNT; i++)
        {
            threads.add(InitializeTask.initRowTask(i, matrix1, matrix2, result, THREAD_COUNT));
        }

        for (Thread t : threads)
        {
            t.start();
        }

        for (Thread t : threads)
        {
            try
            {
                t.join();
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
        System.out.println(matrix1);
        System.out.println(matrix2);
        System.out.println("Resulted matrix: ");
        System.out.println(result);
    }
}
