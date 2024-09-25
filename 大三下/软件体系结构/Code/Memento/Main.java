import game.Memento;
import game.Gamer;

public class Main {
    public static void main(String[] args) {
        Gamer gamer = new Gamer(100);               // 一开始手边金钱总额为100
        Memento memento = gamer.createMemento();    // 预先储存最初状态
        for (int i = 0; i < 10; i++) {
            System.out.println("==== " + i);        // 输出次数
            System.out.println("现况:" + gamer.toString());    // 输出主人的目前状态

            gamer.bet();    // 进行游戏

            System.out.println("手边金钱总额为" + gamer.getMoney() + "元。");

            // 决定如何处理Memento
            if (gamer.getMoney() > memento.getMoney()) {
                System.out.println("    （因为已经贏了不少，故先储存目前状态）");
                memento = gamer.createMemento();
            } else if (gamer.getMoney() < memento.getMoney() / 2) {
                System.out.println("    （因为已经输了很多，故恢复到原先状态）");
                gamer.restoreMemento(memento);
            }

            // 等候
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
            }
            System.out.println("");
        }
    }
}

