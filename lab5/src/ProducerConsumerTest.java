
public class ProducerConsumerTest {

    public static void main(String[] args){
        Store store = new Store();
        Thread  threadA = new ProducerThread(store);
        Thread  threadB = new ConsumerThread(store);

        threadA.start();
        threadB.start();
    }
}


