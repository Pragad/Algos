import java.util.concurrent.*;
import java.util.*;

/**
 * A server can process batches of 4 very efficiently. Batches of any other size take the
 * same amount of time to process albeit very inefficiently. Write a function to process incoming
 * requests with maximum throughput.
 */
class BufferRequestsContinuously {

	private Queue<Integer> requests = new ArrayDeque<>();
	private final ExecutorService pool = Executors.newFixedThreadPool(10);

	private void produce() throws Exception {
		Scanner scanner = new Scanner(System.in);
		while (true) {
			int n = scanner.nextInt();

			pool.submit(new Runnable() {
				public void run() {
					synchronized(requests) {
						requests.offer(n);
						// Notify consumer that it can consume.
						requests.notify();
					}
				}
			});
		}
	}

	/**
	 * Every time a new request comes in, we wait for a maximum timeout (eg. 10s)
	 * If 3 other requests have come in within this timeout, we batch it.
	 * If not, we process all requests that have come in within this timeout (< 4 requests)
	 */
	private void consume() throws Exception {
		while(true) {
			long timeRemaining = 10000; // 10 seconds.
			synchronized(requests) {
				if (requests.isEmpty()) {
					// Wait till first item arrives.
					requests.wait();
				}

				// Wait till a) buffer is full or 
				// 			 b) 10s have passed since the first item arrived.
				while (requests.size() != 4 && timeRemaining > 0) {
					long start = System.currentTimeMillis();
					requests.wait(timeRemaining);
					// Another item has arrived.
					System.out.println("Producer notified me. Queue size is now: "
						+ requests.size());

					// How long did I wait?
					long waitedFor = System.currentTimeMillis() - start;
					// If the buffer isn't full, I have to make sure I don't reset my timer.
					timeRemaining -= waitedFor;
					
				}
				// Consume everything in the queue, whether it's full or not.
				while (!requests.isEmpty()) {
					System.out.println("Consumer Consuming: " + requests.poll());
				}
			}
		}

	}

	public static void main(String[] args) throws Exception {
		BufferRequestsContinuously processor = new BufferRequestsContinuously();

		Thread producer = new Thread(new Runnable() {
			public void run() {
				try {
					processor.produce();
				} catch (Exception e) {
					
				}
				
			}
		});
		producer.start();

		Thread consumer = new Thread(new Runnable() {
			public void run() {
				try {
					processor.consume();
				} catch(Exception e) {
					
				}
				
			}
		});
		consumer.start();
	}
	
}