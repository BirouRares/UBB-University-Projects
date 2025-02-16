import java.util.ArrayList;
import java.util.List;

public class Main
{
    public static void main(String[] args)
    {
        Graph graphWithHamiltonianCycle = new Graph(
                new ArrayList<>(List.of(0,1,2,3,4)),
                new ArrayList<>(List.of(
                        new ArrayList<>(List.of(1)),
                        new ArrayList<>(List.of(2, 3)),
                        new ArrayList<>(List.of(4)),
                        new ArrayList<>(List.of(0)),
                        new ArrayList<>(List.of(1, 3, 4))
                )));//Hamiltonian cycle: 0->1->2->4->3->0

        Graph graphWithoutHamiltonianCycle = new Graph(
                new ArrayList<>(List.of(0,1,2,3,4)),
                new ArrayList<>(List.of(
                        new ArrayList<>(List.of(1)),
                        new ArrayList<>(List.of(2, 3)),
                        new ArrayList<>(List.of(4)),
                        new ArrayList<>(List.of(0)),
                        new ArrayList<>(List.of(1, 4))
                ))); //no Hamiltonian cycle

        Graph randomGraph = new Graph(10);
//        System.out.println(randomGraph);

        long startTime = System.nanoTime();

//        HamiltonianCycleFinder finder = new HamiltonianCycleFinder(graphWithHamiltonianCycle);
//        HamiltonianCycleFinder finder = new HamiltonianCycleFinder(graphWithoutHamiltonianCycle);
        HamiltonianCycleFinder finder = new HamiltonianCycleFinder(randomGraph);


        finder.startSearch();

        long stopTime = System.nanoTime();

        double totalTime = ((double) stopTime - (double) startTime) / 1_000_000_000.0;
        System.out.println("Time: " + totalTime + "s");
    }
}