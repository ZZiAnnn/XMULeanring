import java.util.Vector;
import java.util.Iterator;

public abstract class NumberGenerator {
    private Vector observers = new Vector();        // ����Observer 
    public void addObserver(Observer observer) {    // ����Observer
        observers.add(observer);
    }
    public void deleteObserver(Observer observer) { // �h��Observer
        observers.remove(observer);
    }
    public void notifyObservers() {               // ֪ͨObserver
        Iterator it = observers.iterator();
        while (it.hasNext()) {
            Observer o = (Observer)it.next();
            o.update(this);
        }
    }
    public abstract int getNumber();                // ȡ����ֵ
    public abstract void execute();                 // ������ֵ
}

