import java.util.*;

/**
 * Given a needle string "iss" and a haystack string, find all occurrences of all
 * permutations of the needle in the haystack.
 * Eg haystack = "mississipiandtheoasis" Output will be
 * [iss, ssi, sis, iss, ssi, sis]
 */
class StringMatchPermutations {

	private static void match(String needle, String haystack) {
		int n = needle.length();
		int h = haystack.length();
		List<String> result = new ArrayList<String>();

		// Keep two arrays to keep track of the character counts of the needle and haystack.
		Map<String, Integer> needleMap = new HashMap<String, Integer>();
		Map<String, Integer> haystackMap = new HashMap<String, Integer>();

		for (char each : needle.toCharArray()) {
			String key = String.valueOf(each);
			needleMap.put(key, needleMap.getOrDefault(key, 0) + 1);
		}
		// The number of characters whose counts need to match the haystack is the
		// number of unique characters in the needle.
		int numMatchesNeeded = needleMap.size();

		// Go through the first n characters of the haystack and see if there is a match.
		for (int i = 0; i < n; i++) {
			String key = String.valueOf(haystack.charAt(i));
			haystackMap.put(key, haystackMap.getOrDefault(key, 0) + 1);
		}
		int numMatchesSoFar = 0;
		for (String each : needleMap.keySet()) {
			if (haystackMap.getOrDefault(each, 0) == needleMap.get(each)) {
				numMatchesSoFar++;
			}
		}
		if (numMatchesSoFar == numMatchesNeeded) {
			result.add(haystack.substring(0, n));
		}

		// From now onwards, we slide this window of size n across the haystack
		for (int i = n; i < h; i++) {
			String newChar = String.valueOf(haystack.charAt(i));
			String oldChar = String.valueOf(haystack.charAt(i - n));
			
			// We decrement the count of the character that fell off the window
			if (needleMap.containsKey(oldChar) && 
				needleMap.get(oldChar) == haystackMap.get(oldChar)) {
				// If the character that fell off was needed to make a perfect match with the
				// needle, it got dropped off now, so decrement the count of chars matching the
				// needle.
				numMatchesSoFar--;
			}
			haystackMap.put(oldChar, haystackMap.get(oldChar) - 1);

			// And increment the count of the character that got added to the window.
			haystackMap.put(newChar, haystackMap.getOrDefault(newChar, 0) + 1);
			if (needleMap.containsKey(newChar) && 
				needleMap.get(newChar) == haystackMap.get(newChar)) {
				// If the character that got added newly, makes the char count match,
				// increment the number of chars matching.
				numMatchesSoFar++;
			}

			// If all character counts match, the window from n characters before to this char
			// is a match.
			if (numMatchesSoFar == numMatchesNeeded) {
				result.add(haystack.substring(i - n + 1 /* inclusive */, i + 1 /* exclusive */));
			}
		}

		System.out.println(result);
	}


	public static void main(String[] args) {
		match("iss", "mississipiandtheoasis");
	}
}