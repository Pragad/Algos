import java.util.*;

public class FindPermutations {

	// n choose c.
	private static int[][] findPermutations(int[] input, int c) {
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

		// Pick current element, find all permutations of the rest of the array
		// [1] recurse on [2,3,4,5] with nP1
		int[][] remainingInclusive = findPermutations(
			Arrays.copyOfRange(input, 1, input.length),
			c-1);

		// Don't pick current element, find all permutations of the rest of the array
		// [] recurse on [2,3,4,5] with nP2
		int[][] remainingExclusive = findPermutations(
			Arrays.copyOfRange(input, 1, input.length),
			c);

		// number of permutations to return.
		int total = remainingExclusive.length + remainingInclusive.length * c;
		int[][] result = new int[total][];

		// Each permutation in the exclusive list gets added as is.
		int index = 0;
		for (int[] each : remainingExclusive) {
			result[index++] = each;
		}

		// Each permutation in the inclusive list needs to have the current element
		// added to it in each possible position in the permutation.
		// Eg. current = 5 and each = [1,2]
		// we need to add [5,1,2] [1,5,2] and [1,2,5] to the result.
		for (int[] each : remainingInclusive) {
			for (int position = 0; position < each.length + 1; position++) {
				int[] copy = new int[each.length+1]; // one extra space to hold current element.

				int j = 0; // index into 'each'.
				for (int i = 0; i < copy.length; i++) {
					if (i == position) {
						copy[i] = current;
						continue;
					}
					copy[i] = each[j++];
				}

				result[index++] = copy;
			}
			
		}
		return result;
	}


	/*
	 * Input format for n P c.
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
		int[][] permutations = findPermutations(array, c);
		for (int i = 0; i < permutations.length; i++) {
			System.out.println(Arrays.toString(permutations[i]));
		}
	}
}