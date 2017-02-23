import java.util.*;
/**
 * You have a model that has a list of companies. Each company has ownership of
 * a perentage of one or more other companies. Eg.
 * A -> owns 5% of B
 * B -> owns 10% of C and so on.
 * A loop is an invalid state. Write a function to get the ownership of a source company
 * in a target company.
 * Eg. getOwnership(A, C) is 0.05 * 0.1 = 0.005 or 0.5%
 */
public class CompanyOwnership {

	private static class Company {
		public List<Ownership> ownerships = new ArrayList<>();

		public void addOwnership(Company a, double percentage) {
			ownerships.add(new Ownership(a, percentage));
		}
	}

	private static class Ownership {
		public Company c;
		public double percentage;

		Ownership(Company c, double percentage) {
			this.c = c;
			this.percentage = percentage;
		}
	}

	public static double getStake(Company a, Company b) {
		return getStakeRecursive(a, b, 1.0);
	}

	private static double getStakeRecursive(Company a, Company b, double percentageSoFar) {
		// Base case.
		if (a == b) {
			return percentageSoFar;
		}
		// Go through each child company.
		double result = 0.0;
		for (Ownership ownership : a.ownerships) {
			result += percentageSoFar * getStakeRecursive(ownership.c, b, ownership.percentage);
		}
		return result;
	}

	public static void main(String[] args) {
		Company A = new Company();
		Company B = new Company();
		Company C = new Company();
		Company D = new Company();

		A.addOwnership(B, 0.05);
		A.addOwnership(D, 0.03);
		B.addOwnership(C, 0.1);
		C.addOwnership(D, 0.02);

		double one = getStake(A, B);
		double two = getStake(A, D);
		System.out.println("A->B is " + one + "; A -> D is " + two);

	}
}