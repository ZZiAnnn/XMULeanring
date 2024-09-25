package observer;

import java.util.Observable;
import java.util.Observer;

public class GraphObserver implements Observer {
    @Override
    public void update(Observable o, Object arg) {
        System.out.print("GraphObserver: ");
        int count = ((NumberGenerator) o).getNumber();
        for(int i = 0; i < count; ++i)
        {
            System.out.print("*");
        }
        System.out.println();
        try{
            Thread.sleep(100);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
