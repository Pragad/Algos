
public class LinkedListPalindrome {

	private static class Node {
		public int data;
		public Node next;

		public Node(int data, Node next) {
			this.data = data;
			this.next = next;
		}
	}

	private static Node INVALID_NODE = new Node(Integer.MAX_VALUE, null);

	private static Node checkPalindrome(Node current, Node head) {
		if (current.next == null) {
			// This is the last node in the linked list. Compare it with
			// the head.
			if (current.data == head.data) {
				// Tell the previous guy to now compare with the element
				// after head.
				return head.next;
			}
			return INVALID_NODE;
		}
		Node compareWith = checkPalindrome(current.next, head);
		if (compareWith == INVALID_NODE) {
			return INVALID_NODE;
		}
		if (current.data == compareWith.data) {
			// Tell the previous guy to now compare with the element
			// after what we compared to.
			return compareWith.next;
		}
		return INVALID_NODE;
	}

	private static boolean check(Node head) {
		if (checkPalindrome(head, head) == null) {
			return true;
		}
		return false;
	}

	public static void main(String[] args) {
		Node four = new Node(1, null);
		Node three = new Node(3, four);
		Node mid = new Node(5, three);
		Node two = new Node(3, mid);
		Node one = new Node(1, two);

		System.out.println("IsPalindrome? " + (check(one) ? "yes" : "no"));
	}
}