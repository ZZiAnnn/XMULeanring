package game;
import java.util.Vector;

public class Memento {   
    int money;                              // �ֱ߽�Ǯ�ܶ�
    Vector fruits;                          // ˮ��
    public int getMoney() {                 // ȡ���ֱ߽�Ǯ�ܶnarrow interface��
        return money;
    }
    Memento(int money) {                    // �����ӣ�wide interface����Why not public��
        this.money = money;
        this.fruits = new Vector();
    }
    void addFruit(String fruit) {           // ����ˮ����wide interface��
        fruits.add(fruit);
    }
    Vector getFruits() {
      //return fruits;   
      return (Vector)fruits.clone();
    }
}

