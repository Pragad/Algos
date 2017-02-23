import java.util.*;

/**
 * Given a JSON array, and given a set of preferred keys and secondary keys,
 * return the value of any of the preferred keys if possible, else return
 * the value of any of the secondary keys. The keys are guaranteed to be strings
 * and have string values.
 * {
 *     "glossary": {
 *         "title": "example glossary",
 * 		"GlossDiv": {
 *             "title": "S",
 * 			"GlossList": {
 *                 "GlossEntry": {
 *                     "ID": "SGML",
 * 					"SortAs": "SGML",
 * 					"GlossTerm": "Standard Generalized Markup Language",
 * 					"Acronym": "SGML",
 * 					"Abbrev": "ISO 8879:1986",
 * 					"GlossDef": {
 *                      "para": "A meta-markup language, used to create markup languages such as DocBook.",
 * 						"GlossSeeAlso": ["GML", "XML"]
 *                     },
 * 					"GlossSee": "markup"
 *                 }
 *             }
 *         }
 *     }
 * }
 */
public class MatchJsonKey {

	private static String match(String json, String[] primaryKeys, String[] secondaryKeys) {

		int n = primaryKeys.length;
		int m = secondaryKeys.length;
		// These store the index in each string upto which a match has been found.
		// All initialized to zero since no match has been found yet.
		int[] matchTillPrimary = new int[n];
		int[] matchTillSecondary = new int[m];

		StringBuilder primaryValue = new StringBuilder();
		StringBuilder secondaryValue = new StringBuilder();

		int k = 0;
		while (k < json.length()) {
			char curr = json.charAt(k);

			// For each primary key.
			for (int i = 0; i < n; i++) {
				if (curr == primaryKeys[i].charAt(matchTillPrimary[i])) {
					matchTillPrimary[i]++;
					if (matchTillPrimary[i] == primaryKeys[i].length()) {
						// A primary key has matched fully.
						// Ignore next 3 chars ": "
						k = k + 4;

						primaryValue = new StringBuilder();
						while (json.charAt(k) != '"') {
							primaryValue.append(json.charAt(k));
							k++;
						}

						// Reset all indices.
						for (int j = 0; j < n; j++) {
							matchTillPrimary[j] = 0;
						}
						for (int j = 0; j < m; j++) {
							matchTillSecondary[j] = 0;
						}
						break;
					}
				} else {
					matchTillPrimary[i] = 0;
				}
			}

			// For each secondary key.
			for (int i = 0; i < m; i++) {
				if (curr == secondaryKeys[i].charAt(matchTillSecondary[i])) {
					matchTillSecondary[i]++;
					if (matchTillSecondary[i] == secondaryKeys[i].length()) {
						// A secondary key has matched fully.
						// Ignore next 3 chars ": "
						k = k + 4;

						secondaryValue = new StringBuilder();
						while (json.charAt(k) != '"') {
							secondaryValue.append(json.charAt(k));
							k++;
						}

						// Reset all indices.
						for (int j = 0; j < n; j++) {
							matchTillPrimary[j] = 0;
						}
						for (int j = 0; j < m; j++) {
							matchTillSecondary[j] = 0;
						}
						break;
					}
				} else {
					matchTillSecondary[i] = 0;
				}
			}

			k++;

		}
		return primaryValue.length() == 0 ? secondaryValue.toString() :  primaryValue.toString();

	}

	public static void main(String[] args) {
		String json = "{    \"glossary\": {        \"title\": \"example glossary\",		\"GlossDiv\": {            \"title\": \"S\",			\"GlossList\": {                \"GlossEntry\": {                    \"ID\": \"SGML\",					\"SortAs\": \"SGML\",					\"GlossTerm\": \"Standard Generalized Markup Language\",					\"Acronym\": \"SGML\",					\"Abbrev\": \"ISO 8879:1986\",					\"GlossDef\": {                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",						\"GlossSeeAlso\": [\"GML\", \"XML\"]                    },					\"GlossSee\": \"markup\"                }            }        }    }}";
		
		// Include the quotes in the strings,so that we dont' accidentally match a prefix of the
		// match patterns.
		System.out.println(match(json, new String[] {"\"para\"","\"GlossSee\""}, new String[] {"\"title\"", "\"SortAs\""}));
	}
}
