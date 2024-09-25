package prototype;


public class NPC implements Cloneable {
    private String name;
    private int health;
    private String role;
    private int[] position;
    private double agility;
    private double strength;

    public NPC(String name, int health, String role, int x, int y) {
        this.name = name;
        this.health = health;
        this.role = role;
        this.position = new int[] { x, y };
        this.agility = calculateAgility(health);
        this.strength = calculateStrength(health);
    }

    // 模拟的复杂计算，为敏捷性赋值
    private double calculateAgility(int health) {
        double base = 100.0;
        for (int i = 0; i < 10 * health; i++) {
            base *= 1.01;
        }
        return base - health;
    }

    // 模拟的复杂计算，为力量赋值
    private double calculateStrength(int health) {
        double base = 100.0;
        for (int i = 0; i < 10 * health; i++) {
            base *= 0.99;
        }
        return base + health;
    }

    // 克隆方法，实现深拷贝
    public NPC clone() {
        try {
            NPC cloned = (NPC) super.clone();
            cloned.position = this.position.clone(); // 深拷贝位置数组
            return cloned;
        } catch (CloneNotSupportedException e) {
            throw new AssertionError();
        }
    }

    public static void main(String[] args) {
        final int NUMBER_OF_OBJECTS = 1000000;
        // 测试构造函数创建对象的时间
        long startConstructorTime = System.nanoTime();
        for (int i = 0; i < NUMBER_OF_OBJECTS; i++) {
            NPC originalNPC = new NPC("Goblin", 100, "Warrior", 100, 200);
        }
        long endConstructorTime = System.nanoTime();
        long durationConstructor = endConstructorTime - startConstructorTime;

        NPC originalNPC = new NPC("Goblin", 100, "Warrior", 100, 200);

        // 测试克隆方法创建对象的时间
        long startCloneTime = System.nanoTime();
        for (int i = 0; i < NUMBER_OF_OBJECTS; i++) {
            NPC clonedNPC = originalNPC.clone();
        }
        long endCloneTime = System.nanoTime();
        long durationClone = endCloneTime - startCloneTime;

        System.out.println("Time taken by Constructor: " + durationConstructor / 1_000_000 + " ms");
        System.out.println("Time taken by Clone: " + durationClone / 1_000_000 + " ms");
    }
}
