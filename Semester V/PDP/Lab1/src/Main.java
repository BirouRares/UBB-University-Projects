import model.Bill;
import model.Inventory;
import model.Product;
import model.Transaction;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class Main
{
    private static final int NUMBER__OF_THREADS = 100;
    private static Inventory deposit = new Inventory();
    private static List<Product> products = new ArrayList<>();
    private static List<Bill> recordOfSales = new ArrayList<>();
    private static List<Transaction> transactions = new ArrayList<>();

    public static void main(String[] args)
    {
        WriteInFile();
        ReadFromFile();

        float start =  (float) System.nanoTime() / 1000000;

        for (int i = 0; i < NUMBER__OF_THREADS; i++)
        {
            Transaction t = new Transaction(deposit, "t" + i);
            int productCount = new Random().nextInt(10); // Generates between 0 and 9 products

            for (int j = 0; j < productCount; j++)
            {
                int quantity = new Random().nextInt(10); // Generates a random quantity between 0 and 9
                if (products.size() > 0) // Ensure there are products to select from
                {
                    int productId = new Random().nextInt(products.size());
                    t.add(products.get(productId), quantity);
                }
            }
            transactions.add(t);
        }

        List<Thread> threads = new ArrayList<>();

        transactions.forEach(t -> threads.add(new Thread(t)));

        for (Thread thread : threads)
        {
            thread.start();
        }

        for (Thread thread : threads){

            try
            {
                thread.join(); // wait for all threads to finish
            } catch (InterruptedException e)
            {
                System.out.println(e.getMessage());
            }
        }

        verify();

        float end = (float) System.nanoTime() / 1000000;
        System.out.println("\n End work: " + (end - start) / 1000 + " seconds");
    }

    static void verify()
    {
        System.err.println("Verifying the stock...");

        int expectedSum = 0;
        double sum = recordOfSales.stream().mapToDouble(i -> i.getProducts().stream().mapToDouble(j -> j.getPrice()).sum()).sum();
        if(transactions.stream().mapToDouble(i ->{
            if (i == null)
                return 0.0f;
            else
                return i.getTotalPrice();
        }).sum() == sum) {
            System.err.println("Stock verification failed!");
        }
        else
        {
            System.err.println("Verification Successful!");
        }
    }

    private static void WriteInFile()
    {
        int i = 0;
        try
        {
            BufferedWriter writer = new BufferedWriter(new FileWriter("D:\\Quick access files\\PDP\\Lab1\\src\\data\\products.txt"));
            while ( i < 1000 )
            {
                Random r = new Random();
                Integer quantity = r.nextInt();
                if (quantity < 0)
                    quantity =  (quantity * -1) % 100;
                else
                    quantity %= 100;
                String s = new RandomString().generateRandomString() +  ' ' + r.nextDouble() + ' ' +  quantity + '\n';
                writer.write(s);
                i += 1;
            }
            writer.close();
        }
        catch (IOException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private static void ReadFromFile()
    {
        File file = new File("D:\\Quick access files\\PDP\\Lab1\\src\\data\\products.txt");
        try
        {
            Scanner sc = new Scanner(file);
            while(sc.hasNext())
            {
                Product p = new Product(sc.next(), sc.nextFloat());
                products.add(p);
                deposit.add(p, sc.nextInt());
            }
        } catch (FileNotFoundException e)
        {
            System.out.println(e.getMessage());
        }
    }
}