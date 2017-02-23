import java.util.*;

public class QuickSort {

	/**
	 * start and end are inclusive.
	 */
	private static void quickSort(int[] input, int start, int end) {
		// Base case: Arrays of size 1 are trivially sorted.
		if (start >= end) {
			return;
		}
		int pivot = input[end];
		int lower = start-1; 

		// Loop invariant: Array from start to lower contains elements <= pivot
		for (int i = start; i < end; i++) {
			if (input[i] < pivot) {
				lower++; // all elements below lower are <= pivot.

				// Exchange lower+1 and current element.
				int temp = input[i];
				input[i] = input[lower];
				input[lower] = temp;
			}
		}
		// lower points the last element <= pivot. Exchange the next element, so
		// pivot can fall into the right place.
		// Eg. [1 2 3 4 <== lower 6 7 8 9 5 <== pivot]
		int q = lower+1; // q is the rightful place of the pivot in the final sorted array
		input[end] = input[q];
		input[q] = pivot;

		quickSort(input, start, q-1);
		quickSort(input, q+1, end);
	}

	/*
	 * 5 			// n
	 * 1 2 3 4 5	// the array
	 */
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();

		int[] array = new int[n];
		for (int i = 0; i < n; i++) {
			array[i] = scanner.nextInt();
		}
		quickSort(array, 0, array.length-1);
		System.out.println(Arrays.toString(array));
	}
}