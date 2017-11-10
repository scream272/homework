import java.util.*;

public class Store {
    Queue<String> queue = new LinkedList<String>();
    public List<String> strings;

    public Store() {
        strings = new ArrayList<String>(Arrays.asList("foo", "bar", "baz", "lion", "panda", "tiger"));
    }

    public synchronized void add(String value) {
        queue.add(value);
    }

    public synchronized List<String> dump() {
        List<String> tmp = new ArrayList<String>();
        String str;
        while ((str = queue.poll()) != null) {
            tmp.add(str);
        }
        return tmp;
    }
}