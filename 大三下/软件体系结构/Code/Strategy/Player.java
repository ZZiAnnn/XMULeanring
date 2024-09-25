public class Player {
    private String name;
    private Strategy strategy;
    private int wincount;
    private int losecount;
    private int gamecount;
    public Player(String name, Strategy strategy) {         // �õ�������ս��
        this.name = name;
        this.strategy = strategy;
    }
    public Hand nextHand() {                                // ��ս����ʾ����
        return strategy.nextHand();
    }
    public void win() {                 // ���A
        strategy.study(true);
        wincount++;
        gamecount++;
    }
    public void lose() {                // ����
        strategy.study(false);
        losecount++;
        gamecount++;
    }
    public void even() {                // ƽ��
        gamecount++;
    }
    public String toString() {
        return "[" + name + ":" + gamecount + " games, " + wincount + " win, " + losecount + " lose" + "]";
    }
}

