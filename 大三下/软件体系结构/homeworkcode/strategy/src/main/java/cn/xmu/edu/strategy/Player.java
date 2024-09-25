package cn.xmu.edu.strategy;

public class Player {
    private String name;
    private Strategy strategy;
    private int wincount;
    private int losecount;
    private int gamecount;

    public Player(String name, Strategy strategy) {
        this.name = name;
        this.strategy = strategy;
    }

    public Hand nextHand() {
        return this.strategy.nextHand();
    }

    public void win() {
        this.strategy.study(true);
        ++this.wincount;
        ++this.gamecount;
    }

    public void lose() {
        this.strategy.study(false);
        ++this.losecount;
        ++this.gamecount;
    }

    public void even() {
        ++this.gamecount;
    }

    public String toString() {
        return "[" + this.name + ":" + this.gamecount + " games, " + this.wincount + " win, " + this.losecount + " lose" + "]";
    }
}
