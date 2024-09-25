package cn.xmu.edu.strategy;

public class Hand {
    public static final int HANDVALUE_GUU = 0;
    public static final int HANDVALUE_CHO = 1;
    public static final int HANDVALUE_PAA = 2;
    public static final Hand[] hand = new Hand[]{new Hand(0), new Hand(1), new Hand(2)};
    private static final String[] name = new String[]{"石头", "剪刀", "布"};
    private int handvalue;

    private Hand(int handvalue) {
        this.handvalue = handvalue;
    }

    public static Hand getHand(int handvalue) {
        return hand[handvalue];
    }

    public boolean isStrongerThan(Hand h) {
        return this.fight(h) == 1;
    }

    public boolean isWeakerThan(Hand h) {
        return this.fight(h) == -1;
    }

    private int fight(Hand h) {
        if (this == h) {
            return 0;
        } else {
            return (this.handvalue + 1) % 3 == h.handvalue ? 1 : -1;
        }
    }

    public String toString() {
        return name[this.handvalue];
    }
}
