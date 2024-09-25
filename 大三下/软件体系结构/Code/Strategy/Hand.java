public class Hand {
    public static final int HANDVALUE_GUU = 0;  // 表示石头之值
    public static final int HANDVALUE_CHO = 1;  // 表示剪刀之值
    public static final int HANDVALUE_PAA = 2;  // 表示布之值
    public static final Hand[] hand = {         // 表示猜拳手势的3个实例
        new Hand(HANDVALUE_GUU),
        new Hand(HANDVALUE_CHO),
        new Hand(HANDVALUE_PAA),
    };
    private static final String[] name = {      // 猜拳手势的字串
        "石头", "剪刀", "布",
    };
    private int handvalue;                      // 猜拳手势之值
    private Hand(int handvalue) {
        this.handvalue = handvalue;
    }
    public static Hand getHand(int handvalue) { // 从值取得实例
        return hand[handvalue];
    }
    public boolean isStrongerThan(Hand h) {     // 若this贏过h，则为true
        return fight(h) == 1;
    }
    public boolean isWeakerThan(Hand h) {       // 若this输给h，则为true
        return fight(h) == -1;
    }

    private int fight(Hand h) {           // 平手则为0，若this胜出则为1、若h胜出则为-1
        if (this == h) {
            return 0;
        } else if ((this.handvalue + 1) % 3 == h.handvalue) {
            return 1;
        } else {
            return -1;
        }
    }
    public String toString() {            // 转换成字串
        return name[handvalue];
    }
}

