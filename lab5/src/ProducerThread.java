public class ProducerThread extends Thread{

    private Store store = null;

    public ProducerThread(Store store){

        this.store = store;
    }

    public void run() {
        for(int i=0; i < store.strings.size(); i++){
            //System.out.println("Producer" + i);
            store.add(store.strings.get(i));
            try {
                sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}