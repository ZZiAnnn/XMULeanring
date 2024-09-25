package observer;

import java.util.Observable;
import java.util.Observer;

public class DigitObserver implements Observer {
    @Override
    public void update(Observable o, Object arg) {
        System.out.println("DigitObserver: " + ((NumberGenerator) o).getNumber());
        try{
            Thread.sleep(100);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
