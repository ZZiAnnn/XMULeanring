package cn.xmu.edu.strategy;

import java.util.Random;

public class ProbStrategy implements Strategy {
    private Random random;
    private int prevHandValue = 0;
    private int currentHandValue = 0;
    private int[][] history = new int[][]{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

    public ProbStrategy(long seed) {
        this.random = new Random(seed);
    }

    public Hand nextHand() {
        int bet = this.random.nextInt(this.getSum(this.currentHandValue));
        int handvalue;
        if (bet < this.history[this.currentHandValue][0]) {
            handvalue = 0;
        } else if (bet < this.history[this.currentHandValue][0] + this.history[this.currentHandValue][1]) {
            handvalue = 1;
        } else {
            handvalue = 2;
        }

        this.prevHandValue = this.currentHandValue;
        this.currentHandValue = handvalue;
        return Hand.getHand(handvalue);
    }

    private int getSum(int hv) {
        int sum = 0;

        for(int i = 0; i < 3; ++i) {
            sum += this.history[hv][i];
        }

        return sum;
    }

    public void study(boolean win) {
        int var10002;
        if (win) {
            var10002 = this.history[this.prevHandValue][this.currentHandValue]++;
        } else {
            var10002 = this.history[this.prevHandValue][(this.currentHandValue + 1) % 3]++;
            var10002 = this.history[this.prevHandValue][(this.currentHandValue + 2) % 3]++;
        }

    }
}
