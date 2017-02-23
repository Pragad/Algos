import java.util.*;
import java.math.*;

/**
 * Given a grid with free points '.', walls 'W' and retrooms 'R', find the shortest
 * path to a restroom from a point without walking through walls.
 */
public class FindNearestRestroom {

	private static class Point {
		public int x;
		public int y;

		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		public String toString() {
			return "x: " + x + " y: " + y;
		}
	}

	/**
	 * One way if you are told that the grid is fixed but the starting point
	 * may vary and many such calls will be made is to do the following:
	 * Find the shortest path from each restroom to all points. The when a given
	 * point is queried, find which restroom has the shortest distance to it.
	 */
	private static void findNearestRestroom(char[][] grid, int x, int y) {
		// First pass to find where all the restrooms are.
		int m = grid.length;
		int n = grid[0].length;

		List<Point> restrooms = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == 'R') {
					restrooms.add(new Point(i, j));
				}
			}
		}

		int r = restrooms.size();
		int[][][] distanceMap = new int[r][m][n];
		// For each restroom, construct a map with the shortest distance from
		// the restroom to each point (a reverse map)
		for (int i = 0; i < r; i++) {
			Point restroom = restrooms.get(i);

			boolean[][] discovered = new boolean[m][n];
			Queue<Point> toExplore = new ArrayDeque<>();
			toExplore.offer(restroom);

			for (int j = 0; j < m; j++) {
				for (int k = 0; k < n; k++) {
					distanceMap[i][j][k] = Integer.MAX_VALUE;
				}
			}

			distanceMap[i][restroom.x][restroom.y] = 0;

			while (!toExplore.isEmpty()) {
				Point current = toExplore.poll();

				discovered[current.x][current.y] = true;
				int d = distanceMap[i][current.x][current.y];
				

				if (current.y + 1 < n && !discovered[current.x][current.y + 1]
					&& grid[current.x][current.y + 1] != 'W') {
					discovered[current.x][current.y + 1] = true;
					toExplore.add(new Point(current.x, current.y + 1));
					distanceMap[i][current.x][current.y + 1] = d + 1;
				}
				
				if (current.x - 1 >= 0 && !discovered[current.x - 1][current.y]
				&& grid[current.x - 1][current.y] != 'W') {
					discovered[current.x - 1][current.y] = true;
					toExplore.add(new Point(current.x - 1, current.y));
					distanceMap[i][current.x - 1][current.y] = d + 1;
				}
				
				if (current.y - 1 >= 0 && !discovered[current.x][current.y - 1]
					&& grid[current.x][current.y - 1] != 'W') {
					discovered[current.x][current.y - 1] = true;
					toExplore.add(new Point(current.x, current.y - 1));
					distanceMap[i][current.x][current.y - 1] = d + 1;
				}
				
				if (current.x + 1 < n && !discovered[current.x + 1][current.y]
					&& grid[current.x + 1][current.y] != 'W') {
					discovered[current.x + 1][current.y] = true;
					toExplore.add(new Point(current.x + 1, current.y));
					distanceMap[i][current.x + 1][current.y] = d + 1;
				}
			}
		}

		// Now for the given point, find the closest restroom and the path
		// to get to it.
		int minDistance = Integer.MAX_VALUE;
		int nearestRestroom = -1;
		for (int i = 0; i < r; i++) {
			if (distanceMap[i][x][y] < minDistance && distanceMap[i][x][y] >= 0) {
				minDistance = distanceMap[i][x][y];
				nearestRestroom = i;
			}
		}
		
		if (minDistance == Integer.MAX_VALUE) {
			System.out.println("Impossible to reach any restroom from here");
			return;
		}

		if (minDistance == 0) {
			System.out.println("Already at a restroom");
			return;
		}

		int[][] distToRestroom = distanceMap[nearestRestroom];
		while (!(x == restrooms.get(nearestRestroom).x &&
			y == restrooms.get(nearestRestroom).y)) {
			int minDist = distToRestroom[x][y];
			int nextX = 0;
			int nextY = 0;

			if (y + 1 < n && distToRestroom[x][y+1] < minDist) {
				minDist = distToRestroom[x][y+1];
				nextX = x;
				nextY = y + 1;
			}
			if (x - 1 >= 0 && distToRestroom[x-1][y] < minDist) {
				minDist = distToRestroom[x-1][y];
				nextX = x-1;
				nextY = y;
			}
			if (y - 1 < n && distToRestroom[x][y-1] < minDist) {
				minDist = distToRestroom[x][y-1];
				nextX = x;
				nextY = y - 1;
			}
			if (x + 1 < n && distToRestroom[x+1][y] < minDist) {
				minDist = distToRestroom[x+1][y];
				nextX = x + 1;
				nextY = y;
			}
			System.out.println("Move to " + nextX + "," + nextY);
			x = nextX;
			y = nextY;
		}
	}


	/*
	 * A more straightforward way is to simply do a BFS from the starting point
	 * till you find a restroom.
	 */
	private static void findNearestRestroom2(char[][] grid, int x, int y) {
		int m = grid.length;
		int n = grid[0].length;

		Point start = new Point(x,y);
		Queue<Point> toExplore = new ArrayDeque<>();
		toExplore.offer(start);
		
		int[][] distance = new int[m][n];
		distance[x][y] = 0;
		boolean[][] discovered = new boolean[m][n];
		discovered[x][y] = true;
		Point[][] parent = new Point[m][n];
		parent[x][y] = null;
		

		while (!toExplore.isEmpty()) {
			Point current = toExplore.poll();
			int d = distance[current.x][current.y];

			if (grid[current.x][current.y] == 'R') {
				System.out.println("Distance to nearestRestroom: " + distance[current.x][current.y]);
				unrollPath(parent, current);
				break;
			}
			

			if (current.y + 1 < n && !discovered[current.x][current.y + 1]
				&& grid[current.x][current.y + 1] != 'W') {
				discovered[current.x][current.y + 1] = true;
				toExplore.add(new Point(current.x, current.y + 1));
				distance[current.x][current.y + 1] = d + 1;
				parent[current.x][current.y + 1] = current;
			}
			
			if (current.x - 1 >= 0 && !discovered[current.x - 1][current.y]
			&& grid[current.x - 1][current.y] != 'W') {
				discovered[current.x - 1][current.y] = true;
				toExplore.add(new Point(current.x - 1, current.y));
				distance[current.x - 1][current.y] = d + 1;
				parent[current.x - 1][current.y] = current;
			}
			
			if (current.y - 1 >= 0 && !discovered[current.x][current.y - 1]
				&& grid[current.x][current.y - 1] != 'W') {
				discovered[current.x][current.y - 1] = true;
				toExplore.add(new Point(current.x, current.y - 1));
				distance[current.x][current.y - 1] = d + 1;
				parent[current.x][current.y - 1] = current;
			}
			
			if (current.x + 1 < n && !discovered[current.x + 1][current.y]
				&& grid[current.x + 1][current.y] != 'W') {
				discovered[current.x + 1][current.y] = true;
				toExplore.add(new Point(current.x + 1, current.y));
				distance[current.x + 1][current.y] = d + 1;
				parent[current.x + 1][current.y] = current;
			}

		}
	}

	private static void unrollPath(Point[][] parents, Point end) {
		if (end == null) {
			return;
		}
		unrollPath(parents, parents[end.x][end.y]);
		System.out.println("-> (" + end.x + "," + end.y + ")");
	}

	public static void main(String[] args) {
		char[][] grid = {{'.', '.', '.', '.', '.', 'W', '.', '.', '.', '.'},
						{'.', '.', '.', '.', '.', 'W', '.', '.', 'R', '.'},
						{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
						{'.', '.', 'R', '.', '.', '.', '.', '.', '.', '.'},
						{'.', '.', '.', 'W', 'W', 'W', 'W', 'W', '.', '.'},
						{'.', '.', '.', '.', '.', 'W', '.', '.', '.', '.'},
						{'R', 'W', '.', '.', '.', 'W', '.', '.', '.', '.'},
						{'.', 'W', '.', '.', '.', '.', 'W', '.', '.', '.'},
						{'.', 'W', '.', '.', '.', '.', '.', 'W', '.', '.'},
						{'.', '.', '.', '.', '.', '.', '.', '.', 'W', 'W'}};
		findNearestRestroom2(grid, 7, 5);
	}
}