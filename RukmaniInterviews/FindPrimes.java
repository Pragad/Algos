import java.util.*;

public class FindPrimes {

	private static final int LEFT = 101;
	private static final int RIGHT = 102;
	private static final int DOWN = 103;
	private static final int NULL = 104;

	//  6  9  12  15  18  21 ...
	//  8  12 16  20  24  28 ...
	// 10  15 20  25  30  35 ...
	// All numbers to the left of a number are lesser than it.
	// All numbers to the right and below of a number are greater than it.

	private static void findPrimes(int n) {
		// Start looking for primes from the number 5
		int candidate = 5;
		int numPrimes = 0;
		// We start our search from the number 6 which is 3 * 2.
		int row = 3;
		int col = 2;

		while (numPrimes < n) {
			boolean found = search(candidate, row, col, NULL);
			if (!found) {
				System.out.println(candidate);
				numPrimes++;
			}
			// Consider only odd numbers.
			candidate += 2;
			// Move our start position for the search to the left of the first
			// number greater than the candidate.
			while (candidate > row * (col+1)) {
				col++;
			}
		}
	}

	private static boolean search(int candidate, int row, int column, int prevOp) {
		if (column < 2) {
			return false;
		}
		int current = row * column;
		if (current == candidate) {
			return true;
		}
		if (current < candidate) {
			if (prevOp != LEFT) {
				boolean found = search(candidate, row, column + 1, RIGHT);
				if (found) {
					return true;
				}
			}
			return search(candidate, row+1, column, DOWN);
		}
		if (current > candidate) {
			if (prevOp != RIGHT) {
				return search(candidate, row, column-1, LEFT);
			}
			return false;
		}
		// Should never reach here.
		return false;
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		findPrimes(n);
	}
}