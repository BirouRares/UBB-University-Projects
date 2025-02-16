import java.util.ArrayList;
import java.util.concurrent.ExecutionException;

public class Main {
    public static void main(String[] args) throws InterruptedException, ExecutionException
    {

        Polynomial p = new Polynomial(10000);
        Polynomial q = new Polynomial(10000);
//        System.out.println("p:" + p);
//        System.out.println("q:" + q);

        classicSequential(p, q);
        classicParallel(p, q);

        KaratsubaSequential(p, q);
        KaratsubaParallel(p, q);

    }

    private static Polynomial classicSequential(Polynomial p, Polynomial q)
    {
        long startTime = System.nanoTime();
        Polynomial result = PolynomialHelper.multiplicationSequentialForm(p, q);
        long endTime = System.nanoTime();
        System.out.println("Simple sequential: ");
        System.out.print("Time: ");
        System.out.println((endTime - startTime) / 1000000);
        return result;
    }

    private static Polynomial classicParallel(Polynomial p, Polynomial q) throws InterruptedException
    {
        long startTime = System.nanoTime();
        Polynomial result = PolynomialHelper.multiplicationParallelizedForm(p, q, 2);
        long endTime = System.nanoTime();
        System.out.println("Simple parallel: ");
        System.out.print("Time: ");
        System.out.println((endTime - startTime) / 1000000);
        return result;
    }

    private static Polynomial KaratsubaSequential(Polynomial p, Polynomial q)
    {
        long startTime = System.nanoTime();
        Polynomial result = PolynomialHelper.multiplicationKaratsubaSequentialForm(p, q);
        long endTime = System.nanoTime();
        System.out.println("Karatsuba sequential: ");
        System.out.print("Time: ");
        System.out.println((endTime - startTime) / 1000000);
        return result;
    }

    private static Polynomial KaratsubaParallel(Polynomial p, Polynomial q) throws ExecutionException, InterruptedException
    {
        long startTime = System.nanoTime();
        Polynomial result = PolynomialHelper.multiplicationKaratsubaParallelizedForm(p, q, 1);
        long endTime = System.nanoTime();
        System.out.println("Karatsuba parallel: ");
        System.out.print("Time: ");
        System.out.println((endTime - startTime) / 1000000);
        return result;
    }
}
