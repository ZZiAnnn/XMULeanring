package observer;

import java.util.Observable;
import java.util.Random;

public class NumberGenerator extends Observable {
    private Random random = new Random();
    private Integer number;

    public Integer getNumber() {
        return this.number;
    }

    public void execute() {
        for(int i = 0; i < 10; ++i) {
            number = random.nextInt(50);
            setChanged();
            notifyObservers();
        }
    }
}
