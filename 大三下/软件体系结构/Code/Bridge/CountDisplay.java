public class CountDisplay extends Display {
    public CountDisplay(DisplayImpl impl) {
        super(impl);
    }
    public void multiDisplay(int times) {       // 反复times次再打印??
        open();
        for (int i = 0; i < times; i++) {
            print();
        }
        close();
    }
}

