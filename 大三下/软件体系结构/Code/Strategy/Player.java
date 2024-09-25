public class Player {
    private String name;
    private Strategy strategy;
    private int wincount;
    private int losecount;
    private int gamecount;
    public Player(String name, Strategy strategy) {         // 得到姓名和战略
        this.name = name;
        this.strategy = strategy;
    }
    public Hand nextHand() {                                // 向战略请示手势
        return strategy.nextHand();
    }
    public void win() {                 // 猜贏
        strategy.study(true);
        wincount++;
        gamecount++;
    }
    public void lose() {                // 猜输
        strategy.study(false);
        losecount++;
        gamecount++;
    }
    public void even() {                // 平手
        gamecount++;
    }
    public String toString() {
        return "[" + name + ":" + gamecount + " games, " + wincount + " win, " + losecount + " lose" + "]";
    }
}

