public class Main {
    public static void main(String[] args) {
	// 建立1个有'H'的CharDisplay的对象实例。
        AbstractDisplay d1 = new CharDisplay('H');
	// 建立1个有"Hello, world."的StringDisplay的对象实例。
        AbstractDisplay d2 = new StringDisplay("Hello, world.");
	// 建立1个有"你好。"的StringDisplay的对象实例。
        AbstractDisplay d3 = new StringDisplay("你好软件工程！");
        d1.display();	// d1,d2,d3都是AbstractDisplay的子类的对象实例，
			// 因此，
        d2.display();	// 可以调用继承到的display方法。
        d3.display();	// 实际动作则是规定在类CharDisplay、StringDisplay。
    }
}

