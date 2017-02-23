import java.util.*;
import java.io.*;

/**
 * Given a grid like so
 * 0 W W B 0
 * B W W B 0
 * B W W B 0
 * B B B B 0
 * W W 0 B 0
 * A group of 'W's is said to be captured by the 'B's if they are completely surrounded by 'B's
 * Find out how many captures there are in a grid.
 * To run: java FloodFill gridinput.txt
 */
public class FloodFill {

	private static int numCapturedRegions(char[][] grid) {
		int m = grid.length;
		int n = grid[0].length;

		int numCapturedRegions = 0;
		boolean[][] visited = new boolean[m][n];
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {

				// For every 'W' that we encounter, explore all its connected 'W's and see if a '0'
				// can be reached from this blob.
				if (grid[i][j] == 'W' && !visited[i][j]) {
					if (!floodFill(i, j, visited, grid)) {
						// If a '0' cannot be reached from this blob, it has been captured.
						numCapturedRegions++;
					}
				}
 			}
		}

		return numCapturedRegions;
	}

	/**
	 * Returns true if there is an open space next to this block of 'W's
	 */
	private static boolean floodFill(int i, int j, boolean[][] visited, char[][] grid) {
		int m = visited.length;
		int n = visited[0].length;

		if (i < 0 || i >= m || j < 0 || j >= n) {
			return false;
		}
		if (visited[i][j]) {
			return false;
		}
		if (grid[i][j] == 'B') {
			// If a 'B' has been seen, stop the exploration and mark the route as blocked.
			return false;
		}
		if (grid[i][j] == '0') {
			// If a '0' is seen, stop the exploration and mark the route as open.
			return true;
		}

		visited[i][j] = true;
		boolean result = false;

		// If any of the four directions out of here can reach a '0', then we have not been captured.
		result |= floodFill(i, j + 1, visited, grid); // right
		result |= floodFill(i, j - 1, visited, grid); // left
		result |= floodFill(i - 1, j, visited, grid); // up
		result |= floodFill(i + 1, j, visited, grid); // down

		return result;
	}

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new FileReader(args[0]));

		int m = Integer.parseInt(br.readLine());
		int n = Integer.parseInt(br.readLine());
		char[][] input = new char[m][n];
		for (int i = 0; i < m; i++) {
			String line = br.readLine();
			if (line == null) {
				break;
			}
			String[] characters = line.split(" ");
			for (int j = 0; j < n; j++) {
				input[i][j] = characters[j].charAt(0);
			}
		}

		int result = numCapturedRegions(input);
		System.out.println("Num captured regions: " + result);
	}
}