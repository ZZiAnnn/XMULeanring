public class Hand {
    public static final int HANDVALUE_GUU = 0;  // ��ʾʯͷֵ֮
    public static final int HANDVALUE_CHO = 1;  // ��ʾ����ֵ֮
    public static final int HANDVALUE_PAA = 2;  // ��ʾ��ֵ֮
    public static final Hand[] hand = {         // ��ʾ��ȭ���Ƶ�3��ʵ��
        new Hand(HANDVALUE_GUU),
        new Hand(HANDVALUE_CHO),
        new Hand(HANDVALUE_PAA),
    };
    private static final String[] name = {      // ��ȭ���Ƶ��ִ�
        "ʯͷ", "����", "��",
    };
    private int handvalue;                      // ��ȭ����ֵ֮
    private Hand(int handvalue) {
        this.handvalue = handvalue;
    }
    public static Hand getHand(int handvalue) { // ��ֵȡ��ʵ��
        return hand[handvalue];
    }
    public boolean isStrongerThan(Hand h) {     // ��this�A��h����Ϊtrue
        return fight(h) == 1;
    }
    public boolean isWeakerThan(Hand h) {       // ��this���h����Ϊtrue
        return fight(h) == -1;
    }

    private int fight(Hand h) {           // ƽ����Ϊ0����thisʤ����Ϊ1����hʤ����Ϊ-1
        if (this == h) {
            return 0;
        } else if ((this.handvalue + 1) % 3 == h.handvalue) {
            return 1;
        } else {
            return -1;
        }
    }
    public String toString() {            // ת�����ִ�
        return name[handvalue];
    }
}

