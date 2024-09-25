public abstract class AbstractDisplay { // 抽象类AbstractDisplay
    public abstract void open();        // 由子类实现的抽象方法（1）open
    public abstract void print();       // 由子类实现的抽象方法（2）print
    public abstract void close();       // 由子类实现的抽象方法（3）close
    public final void display() {       // 在此抽象类中实现的方法display
        open();                         // 先open…
        for (int i = 0; i < 5; i++) {   // 反复5次print…
          print();
        }
        close();         // …最后close起來。这就是实现display方法时的內容
    }
}

