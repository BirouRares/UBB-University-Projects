import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class ColoringThread implements Runnable{

    Graph graph;
    int start; // starting index of the nodes
    int end; //ending index (exclusive) of the nodes this thread will process
    CyclicBarrier barrier;
    Set<Integer> conflicting; // stores the labels of nodes that have coloring conflicts
                              // and need to be recolored in subsequent iterations

    public ColoringThread(Graph graph, int start, int end, CyclicBarrier barrier, Set<Integer> conflicting)
    {
        this.graph = graph;
        this.start = start;
        this.end = end;
        this.barrier = barrier;
        this.conflicting = conflicting;
    }

    @Override
    public void run()
    {
        // phase 1: coloring
        for(int i = start; i < end; i++){
            Set<Integer> forbiddenColors = new HashSet<>(); //colors already used by the neighbors of the current node

            Node currentNode = graph.getNode(i);
            for(int neighbour: currentNode.getNeighbours())
            {
                forbiddenColors.add(graph.getNode(neighbour).getColor()); // add the color of the neighbor of curent node to the set of forbidden colors
            }

            int leastAvailableColor = 0; // the smallest color(number) that is not in the set of forbidden colors
            while(forbiddenColors.contains(leastAvailableColor))
            {
                leastAvailableColor++;
            }

            currentNode.setColor(leastAvailableColor); // set the color of the current node to the least available color
        }


        try {
            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        } // wait for all threads to finish coloring


        // phase 2: conflict detection, creating the set with the nodes needing to be recolored
        for(int i = start; i < end; i++)
        {
            Node currentNode = graph.getNode(i);
            for(int neighbour: currentNode.getNeighbours()) // check if the current node has the same color as any of its neighbors
            {
                if(currentNode.getColor() == graph.getNode(neighbour).getColor())
                {
                    //If a neighbor has the same color, the larger of the two node indices is added to the conflicting set
                    conflicting.add(Math.max(i, neighbour));
                }
            }
        }

        try
        {
            barrier.await();
        } catch (InterruptedException | BrokenBarrierException e) {
            e.printStackTrace();
        } // wait for all threads to finish conflict detection
    }
}
