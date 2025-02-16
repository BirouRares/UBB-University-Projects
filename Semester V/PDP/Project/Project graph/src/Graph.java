import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Graph
{
    List<Node> nodes = new ArrayList<>();

    int BOUND; // maximum number of edges per node in random graph generation
    public Graph(int nrNodes, int bound)
    {
        BOUND = bound;
        for(int i = 0; i < nrNodes; i++)
        {
            Node node = new Node(i);
            nodes.add(node);
        }
        generateEdges(BOUND);
    }

    public void generateEdges(int maxEdgesPerNode) // generate random graph
    {
        Random random = new Random();
        for(int i = 0; i < nodes.size(); i++)
        {
            int nrEdgesToBeAdded = random.nextInt(maxEdgesPerNode);
            for(int j = 0; j < nrEdgesToBeAdded; j++)
            {
                int m = random.nextInt(nodes.size());
                if(m != i)
                {
                    addEdge(i, m);
                    addEdge(m, i);
                }
            }
        }
    }

    public void addEdge(int n, int m){
        nodes.get(n).addNeighbour(m);
    } // add edge between two nodes

    public Graph(String fileName) // read the graph from file
    {
        try {
            File file = new File(fileName);
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);

            String line = br.readLine();
            int nrNodes = Integer.parseInt(line); // number of nodes read from the first line of the file

            for(int i = 0; i < nrNodes; i++)
            {
                Node node = new Node(i); // create a new node
                nodes.add(node);
            }

            while((line = br.readLine()) != null) // read the edges from the file
            {
                String[] edge = line.split(" ");
                if(edge.length > 0){
                    int n = Integer.parseInt(edge[0]);
                    int m = Integer.parseInt(edge[1]);
                    if (n!=m){
                        addEdge(n, m);
                        addEdge(m, n);
                    }
                }
            }
            fr.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    public Node getNode(int n){
        return nodes.get(n);
    }

    public int getNrNodes(){
        return nodes.size();
    }

    @Override
    public String toString()
    {
        StringBuilder s = new StringBuilder();
        for(Node n: nodes)
        {
            s.append("Node ").append(n.getLabel()).append(" - Color ").append(n.getColor()).append("\n");
        }
        return s.toString();
    }

    public Map<Integer, Set<Integer>> getGroupedColors()
    {
        Map<Integer, Set<Integer>> colorsMap = new HashMap<>();
        for(Node node: nodes)
        {
            if(! colorsMap.containsKey(node.getColor()))
            {
                colorsMap.put(node.getColor(), new HashSet<>());
            }
            colorsMap.get(node.getColor()).add(node.getLabel());
        }

        return colorsMap;
    }

    public boolean checkColoring() // Validates that no two adjacent nodes share the same color.
    {
        for(Node node: nodes) // iterate through all nodes
        {
            for(Integer neighbour: node.getNeighbours())  // iterate through all neighbours of the current node
            {
                if(node.getColor() == nodes.get(neighbour).getColor())
                {
                    return false;
                }
            }
        }
        return true;
    }
}

