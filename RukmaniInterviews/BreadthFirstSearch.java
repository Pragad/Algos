import java.util.*;

public class BreadthFirstSearch {
    
    private enum Color { 
        WHITE, // A node that hasn't been discovered yet.
        GREY,  // A node that has been discovered and hence its shortest path to s is known
        BLACK,  // All adjacent nodes of this node have been discovered.
    };
    
    private static int[] breadthFirstSearch(int[][] graph, int start) {
        int n = graph.length;
        int[] d = new int[n];
        Color[] color = new Color[n];
        for (int i = 0; i < n; i++) {
            if (i == start) {
                d[i] = 0;
                color[i] = Color.GREY;
            } else {
                d[i] = -1;
                color[i] = Color.WHITE;
            }
        }
        
        Queue<Integer> toExplore = new ArrayDeque<Integer>();
        toExplore.offer(start);
        color[start] = Color.GREY;
        
        while (!toExplore.isEmpty()) {
            int curr = toExplore.poll();
            int[] edges = graph[curr];

            // Add all just discovered adjacent nodes to the queue.
            for (int i = 0; i < n; i++) {
                if (edges[i] == 6) {
                    // If the node has been discovered previously, then ignore it.
                    if (color[i] == Color.WHITE) {
                        // Mark node as discovered.
                        color[i] = Color.GREY;
                        d[i] = d[curr] + 6;
                        toExplore.offer(i);
                    }
                }
            }
            // All adjacent nodes have now been discovered.
            color[curr] = Color.BLACK;
        }
        return d;
    }

    /**
     * Input format:
     * n e // where n is number of nodes, e is number of edges
     * a b
     * c d
     * ... // each line represents one of the e edges.
     * s   // node to start at.
     * Graph is undirected. All edges have the same weight of 6.
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int e = scanner.nextInt();
        
        int[][] graph = new int[n][n];
        for (int j = 0; j < n; j++) {
            graph[j] = new int[n];
        }
        for (int j = 0; j < e; j++) {
            int start = scanner.nextInt();
            int end = scanner.nextInt();
            // Since the graph is undirected, there are two entries in the
            // adjacency matrix for every edge [a][b] and [b][a]
            graph[start-1][end-1] = 6;
            graph[end-1][start-1] = 6;
        }
        
        int start = scanner.nextInt()-1;
        int[] distances = breadthFirstSearch(graph, start);
        for (int k = 0; k < n; k++) {
            if (k != start) {
                System.out.print(distances[k] + " ");
            }
        }
    }
}