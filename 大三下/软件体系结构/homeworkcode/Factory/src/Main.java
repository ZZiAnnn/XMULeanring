import clothes.ClothesFactory;
import framework.*;
import idcard.*;

public class Main {
    public static void main(String[] args) {
        Factory factory = new IDCardFactory();
        Product card1 = factory.create("�Ƿ�");
        Product card2 = factory.create("�����");
        Product card3 = factory.create("����");
        card1.use();
        card2.use();
        card3.use();

        System.out.println();

        Factory factory2 = new ClothesFactory();
        Product clothes1= factory2.create("�Ƿ�");
        Product clothes2 = factory2.create("�����");
        Product clothes3 = factory2.create("����");
        clothes1.use();
        clothes2.use();
        clothes3.use();
    }
}


