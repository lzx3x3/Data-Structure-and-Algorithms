import java.util.ArrayList;

public class Graph {
    public ArrayList<Integer> vertexList;
    public ArrayList<ArrayList<Integer>> edges;
    public int numOfEdges;
    public int num_vertex;

    public Graph(int n) {
        edges = new ArrayList<ArrayList<Integer>>(n);
        numOfEdges = 0;
        num_vertex = 0;
    }

    //insert vertex
    public void insertVertex(int vertex) {
        vertexList.add(vertex);
    }

    //insert edges
    public void insertEdge(int v1, int v2, int w) {
        ArrayList<Integer> a1 = new ArrayList<Integer>(3);
        a1.add(v1);
        a1.add(v2);
        a1.add(w);
        edges.add(a1);
    }

    //print edges of Graph
    public static void printGraph(ArrayList<ArrayList<Integer>> edges) {
        for (int i = 0; i < edges.size(); i++) {           
            System.out.println(edges.get(i));

        }
    }

}
