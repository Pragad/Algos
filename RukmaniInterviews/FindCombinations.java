import java.util.*;

public class FindCombinations {

	// n choose c.
	private static int[][] findCombinations(int[] input, int c) {
		if (c == 0) {
			// Choosing zero elements from an array should return one possibility
			// Return a list of an empty array.
			return new int[1][0];
		}
		if (input.length == 0) {
			// Choosing 1 or more elements from an empty array is not possible.
			// So return an empty list.
			return new int[0][0];
		}
		int current = input[0];
		// Eg. [1,2,3,4,5] n = 5 c = 2

		// Pick current element, find all combinations of the rest of the array
		// [1] recurse on [2,3,4,5] with nC1
		int[][] remainingInclusive = findCombinations(
			Arrays.copyOfRange(input, 1, input.length),
			c-1);

		// Don't pick current element, find all combinations of the rest of the array
		// [] recurse on [2,3,4,5] with nC2
		int[][] remainingExclusive = findCombinations(
			Arrays.copyOfRange(input, 1, input.length),
			c);

		// number of combinations to return.
		int total = remainingExclusive.length + remainingInclusive.length;
		int[][] result = new int[total][];

		// Each combination in the exclusive list gets added as is.
		int index = 0;
		for (int[] each : remainingExclusive) {
			result[index++] = each;
		}

		// Each combination in the inclusive list needs to have the current element
		// added to it.
		for (int[] each : remainingInclusive) {
			int[] copy = Arrays.copyOfRange(each, 0, each.length+1);
			copy[each.length] = current;
			result[index++] = copy;
		}
		return result;
	}


	/*
	 * Input format for n choose c.
	 * 5 			// n
	 * 1 2 3 4 5	// the array
	 * 2			// c
	 */
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();

		int[] array = new int[n];
		for (int i = 0; i < n; i++) {
			array[i] = scanner.nextInt();
		}
		int c = scanner.nextInt();
		int[][] combinations = findCombinations(array, c);
		for (int i = 0; i < combinations.length; i++) {
			System.out.println(Arrays.toString(combinations[i]));
		}
	}
}