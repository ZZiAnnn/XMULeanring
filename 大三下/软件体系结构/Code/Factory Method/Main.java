import framework.*;
import idcard.*;

public class Main {
    public static void main(String[] args) {
        Factory factory = new IDCardFactory();
        Product card1 = factory.create("««∑Â");
        Product card2 = factory.create("¡Ó∫¸≥Â");
        Product card3 = factory.create("Œ‰À…");
        card1.use();
        card2.use();
        card3.use();
    }
}


