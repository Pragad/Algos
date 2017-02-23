import java.util.*;

public class TowersOfHanoi {

	private static void move(Stack<Integer> from, int n,
		Stack<Integer> to,
		Stack<Integer> temp) {
		if (n == 1) {
			int top = from.pop();

			if (!to.isEmpty() && top > to.peek()) {
				System.out.println("VIOLATION");
			}
			to.push(top);
			return;
		}
		move(from, n-1, temp, to);
		
		int top = from.pop();
		if (!to.isEmpty() && top > to.peek()) {
			System.out.println("VIOLATION");
		}
		to.push(top);
		move(temp, n-1, to, from);
	}

	public static void main(String[] args) {
		Stack<Integer> first = new Stack<>();
		first.push(5);
		first.push(4);
		first.push(3);
		first.push(2);
		first.push(1);
		Stack<Integer> second = new Stack<>();
		Stack<Integer> third = new Stack<>();

		move(first, first.size(), third, second);

		while (!third.isEmpty()) {
			System.out.println(third.pop());
		}
	}
}