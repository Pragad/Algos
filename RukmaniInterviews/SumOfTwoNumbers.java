
/**
 * Eg. {10, 22, 28, 29, 30, 40}, sum = 54 
 * Find two numbers in the sorted array whose sum is closest to 54.
 * Answer would be 22 and 30
 */
public class SumOfTwoNumbers {

	private static int[] find(int[] input, int sum) {
		int[] result = new int[2];

		int left = 0;
		int right = input.length - 1;
		int closestDiff = Integer.MAX_VALUE;

		while (left < right) {
			int currentSum = input[left] + input[right];
			int diff = Math.abs(sum - currentSum);

			if (diff < closestDiff) {
				closestDiff = diff;
				result[0] = left;
				result[1] = right;
			}

			if (currentSum == sum) {
				break;
			} else if (currentSum < sum) {
				left++;
			} else {
				right--;
			}
		}

		return result;
	}

	public static void main(String[] args) {
		int[] arr = new int[]{1, 3, 4, 7, 10};
		int[] result = find(arr, 15);
		System.out.println("Closest: " + arr[result[0]] + "," + arr[result[1]]);
	}
}