import java.util.*;
import java.util.concurrent.*;

/**
 * A one-time buffer that waits for 4 requests or n seconds before processing them.
 */
class BufferRequests {
	public static void main(String[] args) throws Exception {
		final Consumer consumer = new Consumer();
		Thread consumerThread = new Thread(new Runnable() {
			public void run() {
				try {
					consumer.process();
				} catch (Exception e) {
					System.out.println(e);
				}
			}
		});
		consumerThread.start();

		// Get requests.
		for (int i = 0; i < 6; i++) {
			Thread.sleep(1000);
			System.out.println("Enqueuing " + i);
			consumer.enqueue(i);
		}

		consumerThread.join();
	}
}

class Consumer {

	private CountDownLatch countDownLatch = new CountDownLatch(4);
	private Queue<Integer> queue = new ArrayDeque<>();

	public void enqueue(int request) throws Exception {
		queue.offer(request);
		countDownLatch.countDown();
	}

	public void process() throws Exception {
		countDownLatch.await(3, TimeUnit.SECONDS);
		System.out.println("Processing...");
		while (!queue.isEmpty()) {
			System.out.println(queue.poll());
		}
	}
}