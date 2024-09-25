import observer.DigitObserver;
import observer.GraphObserver;
import observer.NumberGenerator;

import java.util.random.RandomGenerator;

public class Main {
    public static void main(String[] args) {
        NumberGenerator generator = new NumberGenerator();
        GraphObserver graphObserver = new GraphObserver();
        DigitObserver digitObserver = new DigitObserver();
        generator.addObserver(graphObserver);
        generator.addObserver(digitObserver);
        generator.execute();
    }
}