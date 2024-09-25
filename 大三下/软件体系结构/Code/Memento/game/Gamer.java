package game; 
import java.util.Vector; 
import java.util.Iterator; 
import java.util.Random; 
public class Gamer { 
    private int money;                          // 手边金钱总额 
    private Vector fruits = new Vector();       // 水果 
    private Random random = new Random();       // 随机数生成器 
    private static String fruitsname[] = {      // 水果名称一览表,类字段
        "蘋果", "葡萄", "香蕉", "橘子", 
    }; 
    public Gamer(int money) {                   // 构造子 
        this.money = money; 
    } 
    public int getMoney() {                     // 取得目前的手边金钱总额 
        return money; 
    } 
    public void bet() {                         // 下注…开始游戏 
        int dice = random.nextInt(6) + 1;       // 掷骰子 
        if (dice == 1) {                        // 第1次…手边金钱有变多 
            money += 100; 
            System.out.println("手边金钱增加了。"); 
        } else if (dice == 2) {                 // 第2次…手边金钱剩一半 
            money /= 2; 
            System.out.println("手边金钱剩一半。"); 
        } else if (dice == 6) {                 // 第6次…得到水果 
            String f = getFruit(); 
            System.out.println("得到水果(" + f + ")。"); 
            fruits.add(f); 
        } else {                                // 其他…沒有发生什么事 
            System.out.println("沒有发生什么事。"); 
        } 
    }    
    //!!!快照存储了那些东东？？？ 
    public Memento createMemento() {            // 快照（snapshot） 
        Memento m = new Memento(money);// 快照里是什么?
        Iterator it = fruits.iterator(); 
        while (it.hasNext()) { 
            String f = (String)it.next(); 
            if (f.startsWith("好吃的")) {       
                m.addFruit(f); 
            } 
        } 
        return m; 
    } 
    public void restoreMemento(Memento memento) {   // 进行复原 
        this.money = memento.money; 
        this.fruits = memento.getFruits(); 
    } 
    public String toString() {                      // 输出成字串 
        return "[money = " + money + ", fruits = " + fruits + "]"; 
    } 
    private String getFruit() {                     // 得到1個水果 
        String prefix = ""; 
        if (random.nextBoolean()) { 
            prefix = "好吃的"; 
        } 
        return prefix + fruitsname[random.nextInt(fruitsname.length)]; 
    } 
}

