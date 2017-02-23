import java.util.*;

public class QueueUsingStack {

	Stack<Integer> inbox = new Stack<>();
	Stack<Integer> outbox = new Stack<>();

	public void enqueue(int element) {
		inbox.push(element);
	}

	public int dequeue() {
		if (outbox.isEmpty()) {
			while (!inbox.isEmpty()) {
				outbox.push(inbox.pop());
			}
		}
		return outbox.pop();
	}

	public boolean isEmpty() {
		return inbox.isEmpty() && outbox.isEmpty();
	}

	public static void main(String[] args) {
		QueueUsingStack q = new QueueUsingStack();
		q.enqueue(1);
		q.enqueue(2);
		q.enqueue(3);
		q.enqueue(4);
		q.enqueue(5);
		q.dequeue();
		q.enqueue(6);

		while (!q.isEmpty()) {
			System.out.println("Dequeued: " + q.dequeue());
		}

	}
}