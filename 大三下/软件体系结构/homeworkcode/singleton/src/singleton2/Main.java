package singleton2;

public class Main {
    public static void main(String[] args) {
        Singleton.setNum(5);
        for (int i = 0; i < 10; i++) {
            new Thread(() -> System.out.println("Thread: " + Thread.currentThread().getName()
                    + ", Singleton: " + Singleton.getInstance())).start();
        }
    }
}
