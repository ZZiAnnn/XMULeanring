import java.util.Random;

public class RandomNumberGenerator extends NumberGenerator {
    private Random random = new Random();   // �����������
    private int number;                     // Ŀǰ��ֵ
    public int getNumber() {                // ȡ����ֵ
        return number;
    }
    public void execute() {
        for (int i = 0; i < 10; i++) {
            number = random.nextInt(50);
            notifyObservers();
        }
    }
}

