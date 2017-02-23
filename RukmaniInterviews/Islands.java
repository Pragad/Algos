import java.util.*;

public class Islands {

	private enum State {
		IN,
		OUT,
		ALREADYSEEN,
	}

	private static class Point {
		public int row;
		public int col;

		public Point(int row, int col) {
			this.row = row;
			this.col = col;
		}

		public String toString() {
			return "(" + row + "," + col + ")";
		}
	}

	/**
	 * Start from (0,0) and explore all adjacent points that have the same
	 * value as the starting point. Mark all points that have been seen from
	 * this floodfill. Repeat for every row and column pointin the grid that
	 * hasn't been discovered before. Each time we encounter a new undiscovered
	 * "1" will be part of a new island.
	 */
	private static int findNumIslands(int[][] grid) {
		int m = grid.length;
		int n = grid[0].length;

		boolean[][] discovered = new boolean[m][n];
		int numIslands = 0;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (!discovered[i][j]) {
					discovered[i][j] = true;
					if (grid[i][j] == 1) {
						// This 1 has not been discovered in any exploration
						// before this. So it has to be part of a new island
						// that we haven't seen before.
						numIslands++;
					}
					explore(i, j, discovered, m, n, grid);
				}
			}
		}
		return numIslands;
	}

	private static void explore(int i, int j, boolean[][] discovered,
		int m, int n, int[][] grid) {
		Queue<Point> toExplore = new ArrayDeque<>();
		toExplore.offer(new Point(i, j));
		int element = grid[i][j];

		while (!toExplore.isEmpty()) {
			Point curr = toExplore.poll();
			int row = curr.row;
			int col = curr.col;

			// Right
			if (col +  1 < n && !discovered[row][col + 1]
				&& grid[row][col + 1] == element) {
				discovered[row][col+1] = true;
				toExplore.offer(new Point(row, col+1));
			}
			// Left
			if (col -  1 >= 0 && !discovered[row][col - 1]
				&& grid[row][col - 1] == element) {
				discovered[row][col-1] = true;
				toExplore.offer(new Point(row, col-1));
			}
			// Down
			if (row +  1 < m && !discovered[row+1][col]
				&& grid[row + 1][col] == element) {
				discovered[row+1][col] = true;
				toExplore.offer(new Point(row+1, col));
			}
			// Up
			if (row -  1 >= 0 && !discovered[row-1][col]
				&& grid[row - 1][col] == element) {
				discovered[row-1][col] = true;
				toExplore.offer(new Point(row-1, col));
			}
		}
	}

	/**
	 * Input format:
	 *  3 			// m num rows in matrix
	 *	5			// n num columns in matrix
	 *	0 0 1 1 0	
	 *	1 0 1 0 0
	 *	0 0 1 0 0
	 * Question: Find the number of islands of 1 in the given matrix.
	 */
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int m = scanner.nextInt();
		int n = scanner.nextInt();

		int[][] matrix = new int[m][n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = scanner.nextInt();
			}
		}

		// Approach 1: To go through each row and column in order and try to
		// group 1's into islands.
		int num = 0;
		for (int i = 0; i < m; i++) {
			// For each row, we begin fresh.
			State state = State.OUT;
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] == 1) {
					switch (state) {
						case OUT:
							// This is the first 1 in this row.
							state = State.IN;
							num++; // Optimistically count it as an island unless proven otherwise.
							if (i > 0 && matrix[i-1][j] == 1) {
								state = State.ALREADYSEEN;
								num--;
							}
							break;
						case IN:
							// If this 1 is connected to a previously seen 1,
							// then we need to decrement the count, since we would have
							// incremented it when we saw the first 1 on this line.
							if (i > 0 && matrix[i-1][j] == 1) {
								state = State.ALREADYSEEN;
								num--;
							}
							break;
					}
				} else {
					state = State.OUT;
				}
			}
		}

		System.out.println(num);

		// Approach 2: Floodfill.
		System.out.println("NumIslands from method2: " + findNumIslands(matrix));

	}
}