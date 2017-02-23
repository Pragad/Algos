import java.util.*;
/**
 * You are given a dictionary of words, eg. {bed, hat, and, bat, hand, beyond}
 * Given an input string, such as "bedbathandbeyond", output all valid words
 * contained sequentially in the string. eg. {bed, bath, and, beyond} {bed, bat, hand, beyond}
 * If there aren't valid adjacent words, return null.
 */
class MatchWords {

	private static class Dictionary {
		private static final List<String> dict = Arrays.asList(
			"bed", "bath", "bat", "hand", "and", "beyond");
		public static boolean isWord(String input) {
			return dict.contains(input);
		}
	}

	private static List<String> match(String input, Map<String, List<String>> cache) {
		// Base case. An empty string has 0 matching words.
		if (input.length() == 0) {
			return new ArrayList<>();
		}
		// If we've seen this string in a previous recursion, simply return the stored value.
		if (cache.containsKey(input)) {
			return cache.get(input);
		}
		int n = input.length();
		for (int i = 1; i < n + 1; i++) {
			// For each valid word prefix, recurse on the rest of the string.
			String curr = input.substring(0, i);
			if(Dictionary.isWord(curr)) {
				List<String> rest = match(input.substring(i, n), cache);
				if (rest != null) {
					rest.add(curr);
					// Cache this result, so we don't recompute it if we see it again.
					cache.put(input, rest);
					return rest;
				}
			}
		}
		return null;
	}

	public static void main(String[] args) {
		List<String> output = match("bedbathandbeyond", new HashMap<>());
		for (String each : output) {
			System.out.println(each);
		}
	}
	
}