public class Main extends Thread {
    public static void main(String[] args) {
        SafeFrame frame = new SafeFrame("Example For State Pattern");
        while (true) {
            for (int hour = 0; hour < 24; hour++) {
                frame.setClock(hour);   // 设定时间
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                }
            }
        }
    }
}

