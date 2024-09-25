package game;
import java.util.Vector;

public class Memento {   
    int money;                              // 手边金钱总额
    Vector fruits;                          // 水果
    public int getMoney() {                 // 取得手边金钱总额（narrow interface）
        return money;
    }
    Memento(int money) {                    // 构造子（wide interface），Why not public？
        this.money = money;
        this.fruits = new Vector();
    }
    void addFruit(String fruit) {           // 新增水果（wide interface）
        fruits.add(fruit);
    }
    Vector getFruits() {
      //return fruits;   
      return (Vector)fruits.clone();
    }
}

