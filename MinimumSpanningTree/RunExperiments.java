
/*
CSE6140 HW2
This is an example of how your experiments should look like.
Feel free to use and modify the code below, or write your own experimental code, as long as it produces the desired output.
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.PriorityQueue;

public class RunExperiments{
    public static void main(String[] args) throws IOException{


        if (args.length < 3) {
            System.err.println("Unexpected number of command line arguments");
            System.exit(1);
        }

        String graph_file = args[0];
        String change_file = args[1];
        String output_file = args[2];

        PrintWriter output;
        output = new PrintWriter(output_file, "UTF-8");

        //Write this function to parse edges from graph file to create your graph object
        Graph G = parseEdges(graph_file);
        //G.printGraph(G.edges);
        ArrayList<ArrayList<Integer>> MST = new ArrayList<ArrayList<Integer>>(3);;

        long startMST = System.nanoTime();
        int MSTweight = computeMST(G, MST);
        long finishMST = System.nanoTime();

        //Subtract the start time from the finish time to get the actual algorithm running time
        double MSTtotal = (finishMST - startMST)/1000000;

        //Write to output file the initial MST weight and time
        output.println(Integer.toString(MSTweight) + " " + Double.toString(MSTtotal));

        //Iterate through changes file
        BufferedReader br = new BufferedReader(new FileReader(change_file));
        String line = br.readLine();
        String[] split = line.split(" ");
        int num_changes = Integer.parseInt(split[0]);
        int u, v, weight;

        int newMST_weight;
        int vertexSize = G.num_vertex;
        double totalRecompute = 0;

        while ((line = br.readLine()) != null) {
            split = line.split(" ");
            u = Integer.parseInt(split[0]);
            v = Integer.parseInt(split[1]);
            weight = Integer.parseInt(split[2]);

            //Run your recomputeMST function to recalculate the new weight of the MST given the addition of this new edge
            //Note: you are responsible for maintaining the MST in order to update the cost without recalculating the entire MST
            long start_newMST = System.nanoTime();

            //maintaining the old MSTweight when the weight of added new edge is larger than original Graph
            	
                newMST_weight = recomputeMST(vertexSize, u,v,weight, MST);


            long finish_newMST = System.nanoTime();
            double newMST_total = (finish_newMST - start_newMST)/1000000;
            totalRecompute += newMST_total;

            //Write new MST weight and time to output file
            output.println(Integer.toString(newMST_weight) + " " + Double.toString(newMST_total).format("%.3f", newMST_total));

            //update oldMST_weight with newMST_weight
//             oldMST_weight = newMST_weight;
        }
        //print the total recompute time
        System.out.println("The total recompute time is: "+ totalRecompute);
        
        output.close();
        br.close();




    }



    // calculate MST using Kruskal's algorithm
    public static int computeMST(Graph G, ArrayList<ArrayList<Integer>> MST) {
        int cost = 0;

        ArrayList<Integer> list = new ArrayList<Integer>();
        int vertexSize = G.num_vertex;
        int[] parent = new int[vertexSize];
        for(int i = 0; i < vertexSize; i++) {
            parent[i] = -1;
        }
        //System.out.println(vertexSize);
        PriorityQueue<Node> pq = new PriorityQueue<>(new NodeComparator());

        for(int u = 0; u < G.edges.size(); u++) {
                Node newNode = new Node(G.edges.get(u).get(0), G.edges.get(u).get(1), G.edges.get(u).get(2));
                pq.add(newNode);  
        }
        while(list.size() < vertexSize-1) { //
            Node min = pq.poll();
            int p1 = findRoot(parent, min.from);
            int p2 = findRoot(parent, min.to);
            if(p1 != p2) { //p1, p2 have different parent roots, so adding path won't form cycle
                list.add(min.from);
                cost += min.value;
                parent[p1] = p2;
                ArrayList<Integer> a = new ArrayList<Integer>(3);
                a.add(min.from);
                a.add(min.to);
                a.add(min.value);
                MST.add(a);
            }
        }
//        for (int i = 0; i < MST.size(); i++) {
//             System.out.println(MST.get(i));
//        }
        return cost;
    }




    public static int recomputeMST(int vertexSize, int u,int v,int weight, ArrayList<ArrayList<Integer>> MST) {
//    	for (int i = 0; i < MST.size(); i++) {
//            if( (MST.get(i).get(0)==u && MST.get(i).get(1)==v) || (MST.get(i).get(0)==v && MST.get(i).get(1)==u)) {
//            	if(MST.get(i).get(2) > weight) {
//            		//update cost
//           		 	 cost = cost - MST.get(i).get(2) + weight;
//            		 ArrayList<Integer> a = new ArrayList<Integer>(3);
//                     a.add(u);
//                     a.add(v);
//                     a.add(weight);
//            		 MST.set(i, a); //update MST
//                 	}
//            }break;
//       }
    	int cost = 0;
    	ArrayList<Integer> e = new ArrayList<Integer>(3);
        e.add(u);
        e.add(v);
        e.add(weight);
		MST.add(e); //add new edge into MST
		 
    	ArrayList<Integer> list = new ArrayList<Integer>();
        
        int[] parent = new int[vertexSize];
        for(int i = 0; i < vertexSize; i++) {
            parent[i] = -1;
        }
        //System.out.println(vertexSize);
        PriorityQueue<Node> pq = new PriorityQueue<>(new NodeComparator());


        for(int i = 0; i < MST.size(); i++) {
        	 	Node newNode = new Node(MST.get(i).get(0), MST.get(i).get(1), MST.get(i).get(2));
                
                pq.add(newNode);
                
        }
        while(list.size() < vertexSize-1) { //
            Node min = pq.poll();
            int p1 = findRoot(parent, min.from);
            int p2 = findRoot(parent, min.to);
            if(p1 != p2) { //p1, p2 have different parent roots, so adding path won't form cycle
                list.add(min.from);
                parent[p1] = p2;
                
                cost += min.value;
            }
        }
    	return cost;
    }


    // find root vertex of each vertex
    public static int findRoot(int parent[], int v) {
        int r = v;
        while(parent[r] > -1) {
            r = parent[r];
        }
        return r;
    }


    public static Graph parseEdges(String graph_file) throws IOException {

        //Iterate through graph file
        BufferedReader br = new BufferedReader(new FileReader(graph_file));
        String line = br.readLine();
        String[] split = line.split(" ");
        int num_vertex = Integer.parseInt(split[0]);
        int num_edge = Integer.parseInt(split[1]);

        // Create a new class Graph
        Graph G = new Graph(3);
        G.num_vertex = num_vertex;
        G.numOfEdges = num_edge;

        int u, v, weight;
        while ((line = br.readLine()) != null) {
            split = line.split(" ");
            u = Integer.parseInt(split[0]);
            v = Integer.parseInt(split[1]);
            weight = Integer.parseInt(split[2]);
            // insert edges
            G.insertEdge(u, v, weight);
        }
        return G;
    }

}



