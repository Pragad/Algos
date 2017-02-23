import java.util.*;

public class Justify {

	private static String justify(int N, String line) {
		if (line.length() == N) {
			return line;
		}
		
		String[] words = line.split(" ");
		int totalSpaces = N - line.length() + words.length - 1;
		int numWords = words.length;
		int numSpots = numWords - 1;
		int numSpaces = totalSpaces / numSpots;
		// If the number of spaces doesn't divvy up evenly among the available spots,
		// keep track the leftover spaces.
		int extra = totalSpaces % numSpots;

		StringBuilder builder = new StringBuilder();
		builder.append(words[0]);
		for (int j = 0; j < words.length - 1; j++) {
			for (int i = 0; i < numSpaces; i++) {
				builder.append("#");
			}
			// Remember the leftover spaces? Add one here till we run out of them.
			if (extra > 0) {
				builder.append("#");
				extra--;
			}
			builder.append(words[j+1]);
		}
		return builder.toString();
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in); 
		String line = scanner.nextLine();
		int n = scanner.nextInt();
		System.out.println(justify(n, line));
	}
}