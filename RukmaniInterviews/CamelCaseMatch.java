import java.util.*;

/**
 * Eg. pattern = "FoBa" candidate = "FooBar" is a match but "FastByte" is not a match
 */
class CamelCaseMatch {

	private static List<String> match(String[] candidates, String pattern) {
		List<String> result = new ArrayList<>();
		for (String candidate : candidates) {
			if (match(candidate, pattern)) {
				result.add(candidate);
			}
		}
		return result;
	}

	/**
	 * Eg. pattern = "FoBa" candidate = "FooBar"
	 */
	private static boolean match(String candidate, String pattern) {
		List<String> patternPieces = toPieces(pattern);
		List<String> candidatePieces = toPieces(candidate);

		for (int i = 0; i < patternPieces.size(); i++) {
			String patternPiece = patternPieces.get(i);
			if (i >= candidatePieces.size()) {
				return false;
			}
			String candidatePiece = candidatePieces.get(i);
			if (patternPiece.length() > candidatePiece.length()) {
				return false;
			}
			if (!candidatePiece.substring(0, patternPiece.length())
				.equals(patternPiece)) {
				return false;
			}
		}
		return true;
	}

	private static List<String> toPieces(String string) {
		List<String> pieces = new ArrayList<>();
		StringBuilder builder = new StringBuilder();
		for (char each : string.toCharArray()) {
			if (each >= 'A' && each <= 'Z') {
				if (builder.length() > 0) {
					pieces.add(builder.toString());
					builder = new StringBuilder();
				}
			}
			builder.append(each);
		}
		if (builder.length() > 0) {
			pieces.add(builder.toString());
			builder = new StringBuilder();
		}
		return pieces;
	}

	public static void main(String[] args) {
		String[] candidates = new String[]{"FooBar", "FrameBuffer",
		"FoolishBasketBallPlayers", "CamelCase", "StringBufferReader"};
		String pattern = "FBB";

		System.out.println(match(candidates, pattern));
	}
	
}