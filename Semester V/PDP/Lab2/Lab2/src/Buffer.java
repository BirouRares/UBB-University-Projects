import java.util.LinkedList;
import java.util.Queue;import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static java.sql.Types.NULL;

public class Buffer
{

    //The shared resource where the producer places each computed product, and from which the consumer retrieves each product.
    //queue with synchronization
    private final Queue<Integer> queue = new LinkedList<>();
    private final Lock lock = new ReentrantLock();

    private final Condition readyToSendProduct = lock.newCondition();

    private final Condition readyToReceiveProduct = lock.newCondition();

    private Integer partialResult = NULL; //current product in the buffer

    public Buffer()
    {}

    public int get() throws InterruptedException //used by the consumer to add a computed product
    {
        lock.lock();
        try
        {
            while(partialResult == NULL)//if buffer has data we wait
            {
                System.out.println(Thread.currentThread().getName() + ": Buffer is empty");
                readyToReceiveProduct.await();
            }
            // the consumer removes the current product -> the producer adds the new product
            Integer value = queue.poll();
            if(value != null)
            {
                partialResult = NULL;
                System.out.printf("%s extracted value %d from the queue\n", Thread.currentThread().getName(), value);
                readyToSendProduct.signal(); //signals the consumer
            }
            return value;
        }
        finally
        {
            lock.unlock();
        }
    }

    public void put(int val) throws InterruptedException //used by the producer to retrieve a product from the buffer
    {
        lock.lock();

        try
        {
            while (partialResult != NULL) // if buffer is not empty -> consumer waits
            {
                System.out.println(Thread.currentThread().getName() + ": Queue is currently full");
                readyToSendProduct.await();
            }

            queue.add(val); // add the product to the buffer
            partialResult = val;
            System.out.printf("%s added value %d to the queue\n", Thread.currentThread().getName(), val);
            readyToReceiveProduct.signal(); //signals the producer

        }
        finally
        {
            lock.unlock();
        }
    }
}