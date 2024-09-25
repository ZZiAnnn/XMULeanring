import framework.*;

public class Main {
    public static void main(String[] args) {
        // 预备阶段
        Manager manager = new Manager();
        UnderlinePen upen = new UnderlinePen('~');
        MessageBox mbox = new MessageBox('*');
        MessageBox sbox = new MessageBox('/');
        manager.register("strong message", upen);
        manager.register("warning box", mbox);
        manager.register("slash box", sbox);

        // 实现部分
        //请问：P1、P2、P3是什么？从那里来的？
        Product p1 = manager.create("strong message");      
        p1.use("Hello, world.");
        Product p2 = manager.create("strong message");
        p2.use("Hello, XMU.");
        Product p3 = manager.create("strong message");
        p3.use("Hello, Software School.");
        Product p4 = manager.create("strong message");
        p4.use("Hello, Everyone.");
        p4.use("Hello, SA.");

    }
}

