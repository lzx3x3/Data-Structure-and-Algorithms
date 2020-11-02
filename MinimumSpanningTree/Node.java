import java.util.Comparator;

public class Node {
	public int from;
	public int to;
	public int value;
	
	public Node(int k1, int k2, int v) {
		this.from = k1;
		this.to = k2;
		this.value = v;
	}
}


class NodeComparator implements Comparator<Node>{ 
    
    public int compare(Node v1, Node v2) { 
    	return (v1.value - v2.value);
     } 
} 
