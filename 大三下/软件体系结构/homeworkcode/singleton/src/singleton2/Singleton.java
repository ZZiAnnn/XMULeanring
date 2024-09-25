package singleton2;

import java.util.ArrayList;

public class Singleton {

    private static volatile ArrayList<Singleton> singletons = new ArrayList<>();
    public static volatile int num = 0;

    public static void setNum(int num) {
        Singleton.num = num;
    }

    public static Singleton getInstance() {
        if (singletons.size() < num) {
            synchronized (Singleton.class) {
                if (singletons.size() < num) {
                    singletons.add(new Singleton());
                }
            }
        }
        return singletons.get(singletons.size() - 1);
    }
}
