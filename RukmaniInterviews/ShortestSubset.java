import java.util.*;

/**
 * Given a list of words as input and another list of words to match like so
 * "a", "b", "a", "d", "c", "b", "a", "e"
 * "b", "c"
 * find the shortest range of indices between which all words in the second list
 * are contained in the first i.e shortest subsequence
 * In the aboce example is [4, 5]
 */
public class ShortestSubset {

	private static int[] shortestSubset(List<String> input, List<String> words) {
		Map<String, Integer> occurrence = new HashMap<>();
		int n = words.size();
		int numMatches = 0;

		int start = Integer.MAX_VALUE;
		int end = -1;

		int i = 0;
		boolean allMatched = false;

		// First pass to go through and find the first start and end points
		// that encompass all words in 'words'.
		for (String next : input) {
			for (String word : words) {
				if (next.equals(word)) {
					if (!occurrence.containsKey(word)) {
						numMatches++;
					}
					occurrence.put(word, occurrence.getOrDefault(word, 0) + 1);
					start = Math.min(start, i);
					if (numMatches == n) {
						end = i;
						allMatched = true;
						break;
					}
				}
			}
			i++;

			if (allMatched) {
				break;
			}
		}

		System.out.println("First pass. start: " + start + " End: " + end);

		// Keep track of the shortest indices so far.
		int minLength = end - start + 1;
		int bestStart = start;
		int bestEnd = end;

		// We'll keep trying to shorten the subset from the left i.e every time
		// we increase the left index and see if the subset is still valid.
		while (start < input.size() && end < input.size()) {

			// Loop invariant: start - end is always a valid subset
			String curr = input.get(start);
			start++;
			if (!occurrence.containsKey(curr)) {
				// The left index didn't contain any matched word.
				// We can safely skip ahead without breaking the invariance.
			} else if (occurrence.get(curr) > 1) {
				// The left index did contain a matched word, but it is also
				// present at another index in our subset. so we can still
				// safely skip ahead.
				occurrence.put(curr, occurrence.get(curr)-1);
			} else {
				// Our subset from start-end is not valid anymore.
				// We will keep trying to extend end untill we find this particular
				// word that we lost.
				occurrence.put(curr, 0);
				numMatches--;
				end++;
				while (end < input.size() && !input.get(end).equals(curr)) {
					end++;
				}
				if (end < input.size() && input.get(end).equals(curr)) {
					occurrence.put(curr, 1);
					numMatches++;
				}
			}

			// Finally if our subset length is smaller, note that. 
			if (numMatches == n && (end - start + 1) < minLength) {
				bestStart = start;
				bestEnd = end;
				minLength = end - start + 1;
			}
		}

		return new int[]{bestStart, bestEnd};
	}

	public static void main(String[] args) {
		List<String> input = Arrays.asList("a", "b", "a", "d", "c", "b", "a", "e");
		List<String> words = Arrays.asList("b", "c");
		
		System.out.println(Arrays.toString(
			shortestSubset(input, words)));
	}
}