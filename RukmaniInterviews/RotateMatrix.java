import java.util.*;

/*
 * Rotate a matrix by 90 degrees. Only square matrices are allowed.
 * The logic rotates the array from the outer layer to the inner layers
 * When we rotate the first row of elements, the outer layer is done
 *		  * * * *
 *		  *     *
 *		  *     *
 *		  * * * *
 * The next row rotate the next inner layer
 *		  * * * *
 *		  * # # *
 *		  * # # *
 *		  * * * *
 * And so on, until the left and right ends meet.
 */
public class RotateMatrix {

	private static int getNextRow(int row, int col, int n) {
		return col;
	}

	private static int getNextCol(int row, int col, int n) {
		return n - 1 - row;
	}

	private static void rotateMatrix(int[][] matrix) {
		int n = matrix.length;

		int left = 0;
		int right = n-1;
		// We go through one row at a time and perform all the rotations starting from
		// that row.
		int row = 0;
		while (left < right) {
			for (int col = left; col < right; col++) {
				// Perform 4 rotations each 90 degrees to complete a 360 degrees
				// to come back to the starting position.
				int nextRow = getNextRow(row, col, n);
				int nextCol = getNextCol(row, col , n);
				int temp = matrix[nextRow][nextCol];
				matrix[nextRow][nextCol] = matrix[row][col];

				int nextRow2 = getNextRow(nextRow, nextCol, n);
				int nextCol2 = getNextCol(nextRow, nextCol, n);
				int temp2 = matrix[nextRow2][nextCol2];
				matrix[nextRow2][nextCol2] = temp;

				nextRow = getNextRow(nextRow2, nextCol2, n);
				nextCol = getNextCol(nextRow2, nextCol2 , n);
				temp = matrix[nextRow][nextCol];
				matrix[nextRow][nextCol] = temp2;

				nextRow2 = getNextRow(nextRow, nextCol, n);
				nextCol2 = getNextCol(nextRow, nextCol, n);
				matrix[nextRow2][nextCol2] = temp;
			}
			row++;
			// With every row, start from one element inner and stop one element sooner.
			left++;
			right--;
		}
	}

	public static void main(String[] args) {
		int[][] matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
		rotateMatrix(matrix);
		System.out.println(Arrays.deepToString(matrix));

	}
}