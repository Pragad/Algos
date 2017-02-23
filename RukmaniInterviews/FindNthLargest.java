import java.util.*;

/**
 * Given an array, and a number n, find the n largest numbers in the array
 * in sorted order.
 */
class FindNthLargest {

	/**
	 * Approach 1: Use Quickselect method to partition the array around the nth
	 * largest element. Run time is O(m + nlogn) where m is the length of the array
	 * With no extra space.
	 */
	private static int[] largest(int[] input, int n) {
		// Translate n'th largest to an index in the array
		select(input, 0, input.length - 1, input.length - n);
		// input's nth position and above will have the top N elements.
		// Sort them.
		int[] result = Arrays.copyOfRange(input, input.length - n, input.length);
		Arrays.sort(result);
		return result;
	}

	/**
	 * end - is inclusive.
	 */
	private static void select(int[] input, int start, int end, int n) {
		// Base cases:
		if (start >= end || start >= input.length) {
			return;
		}
		int rankOfPivot = partition(input, start, end);
		if (rankOfPivot == n) {
			return;
		} else if (rankOfPivot > n) {
			select(input, start, rankOfPivot - 1, n);
		} else {
			select(input, rankOfPivot + 1, end, n - rankOfPivot - 1);
		}
	}

	private static int partition(int[] input, int start, int end) {
		int pivot = end;
		int pivotValue = input[pivot];
		// i represents a point in the array where all elements before it
		// inclusive is less than pivotValue.
		int i = start - 1;
		
		for (int j = start; j < end; j++) {
			if (input[j] < pivotValue) {
				// Maintain the invariant regarding i.
				int temp = input[i + 1];
				input[i + 1] = input[j];
				input[j] = temp;
				i++;
			}
		}

		// i + 1 is the rightful place for pivotValue.
		input[pivot] = input[i + 1];
		input[i + 1] = pivotValue;
		return i + 1;
	}

	public static void main(String[] args) {
		int[] input = new int[]{7, 4, 9, 1, 5, 0, 23, 6, 8, 10};
		int n = 5;
		System.out.println(Arrays.toString(largest(input, n)));
	}
	
}