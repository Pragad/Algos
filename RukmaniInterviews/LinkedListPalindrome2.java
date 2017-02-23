import java.util.*;

public class LinkedListPalindrome2 {

	private static class Node {
		public int data;
		public Node next;

		public Node(int data, Node next) {
			this.data = data;
			this.next = next;
		}
	}

	private static int length(Node head) {
		Node curr = head;
		int l = 0;
		while (curr != null) {
			l++;
			curr = curr.next;
		}
		return l;
	}

	private static boolean isPalindrome(Node head) {
		int n = length(head);

		Stack<Node> stack = new Stack<>();
		Node current = head;
		for (int i = 0; i < n/2; i++) {
			stack.push(current);
			current = current.next;
		}

		if (n % 2 == 1) {
			current = current.next;
		}

		while (current != null) {
			Node compareTo = stack.pop();
			if (current.data != compareTo.data) {
				return false;
			}
			current = current.next;
		}
		return true;
	}

	public static void main(String[] args) {
		Node four = new Node(1, null);
		Node three = new Node(3, four);
		Node mid = new Node(5, three);
		Node two = new Node(3, mid);
		Node one = new Node(1, two);

		System.out.println("IsPalindrome? " + (isPalindrome(one) ? "yes" : "no"));
	}
}