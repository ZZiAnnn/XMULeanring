import game.Memento;
import game.Gamer;

public class Main {
    public static void main(String[] args) {
        Gamer gamer = new Gamer(100);               // һ��ʼ�ֱ߽�Ǯ�ܶ�Ϊ100
        Memento memento = gamer.createMemento();    // Ԥ�ȴ������״̬
        for (int i = 0; i < 10; i++) {
            System.out.println("==== " + i);        // �������
            System.out.println("�ֿ�:" + gamer.toString());    // ������˵�Ŀǰ״̬

            gamer.bet();    // ������Ϸ

            System.out.println("�ֱ߽�Ǯ�ܶ�Ϊ" + gamer.getMoney() + "Ԫ��");

            // ������δ���Memento
            if (gamer.getMoney() > memento.getMoney()) {
                System.out.println("    ����Ϊ�Ѿ��A�˲��٣����ȴ���Ŀǰ״̬��");
                memento = gamer.createMemento();
            } else if (gamer.getMoney() < memento.getMoney() / 2) {
                System.out.println("    ����Ϊ�Ѿ����˺ܶ࣬�ʻָ���ԭ��״̬��");
                gamer.restoreMemento(memento);
            }

            // �Ⱥ�
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
            }
            System.out.println("");
        }
    }
}

