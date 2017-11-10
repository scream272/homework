import java.util.List;

public class ConsumerThread extends Thread{

    private Store store = null;
    private List<String> dumpResult;

    public ConsumerThread(Store store){
        this.store = store;
    }

    public void run() {
        int counter = 0;
        while(true){
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            //System.out.println("Consumer" + counter);
            dumpResult = store.dump();
            counter+=dumpResult.size();
            for(String iter: dumpResult) {
                System.out.println(new StringBuilder(iter).reverse());
            }
            if (counter == store.strings.size()) {
                break;
            }
        }
    }
}