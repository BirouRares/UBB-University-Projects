import java.util.*;
import java.util.concurrent.CyclicBarrier;

public class Main {

    static int NR_THREADS = 4;

    public static void main(String[] args) throws InterruptedException {

//        Graph graph = new Graph("g1.txt");
        Graph graph = new Graph("g2.txt");
//        Graph graph = new Graph(500, 100);

        long startTime = System.nanoTime();
        color(graph);
        long endTime = System.nanoTime();

        long duration = (endTime - startTime) / 1000000;
        System.out.printf("Execution took: %d ms", duration);
    }

    public static List<Thread> createThreads(Graph graph, Set<Integer> conflicting) {
        int n = graph.getNrNodes();

        int nodesPerThread = n / NR_THREADS; // number of nodes each thread will process
        int remaining = n % NR_THREADS;

        CyclicBarrier barrier = new CyclicBarrier(NR_THREADS);

        List<Thread> threads = new ArrayList<>();

        int endOfLastT = 0;
        int start;
        for (int i = 0; i < NR_THREADS; i++) //Iterates over the number of threads
        { //calculates the range of nodes (start to end) for each thread
            start = endOfLastT;
            int end;
            if (remaining > 0) // if leftovers
            {
                end = start + nodesPerThread + 1;
                remaining--; // assigns one additional node to the current thread
            } else
            {
                end = start + nodesPerThread;
            }
            endOfLastT = end;
            Runnable thread = new ColoringThread(graph, start, end, barrier, conflicting);
            threads.add(new Thread(thread));
        }

        return threads;
    }

    public static void color(Graph graph)
    {
        Set<Integer> conflicting = new HashSet<>();
        conflicting.add(1); // dummy values to start the loop

        while (!conflicting.isEmpty())  // loop until there are no conflicts
        {
            Set<Integer> newConflicting = new HashSet<>(); // stores the labels of nodes that have coloring conflicts
            List<Thread> threads = createThreads(graph, newConflicting);
            for (var t : threads) // start all threads
            {
                t.start();
            }
            for (var t : threads)
            {
                try {
                    t.join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            conflicting = newConflicting; // update the conflicting set
        }

        System.out.println(graph);
        System.out.println(graph.checkColoring());
    }
}
