package cn.xmu.edu.gumball;

public class GumballMachine {
    State soldOutState = new SoldOutState(this);
    State noQuarterState = new NoQuarterState(this);
    State hasQuarterState = new HasQuarterState(this);
    State soldState = new SoldState(this);
    State state;
    int count = 0;

    public GumballMachine(int numberGumballs) {
        this.count = numberGumballs;
        if (numberGumballs > 0) {
            this.state = this.noQuarterState;
        } else {
            this.state = this.soldOutState;
        }

    }

    public String insertQuarter() {
        return this.state.insertQuarter();
    }

    public String ejectQuarter() {
        return this.state.ejectQuarter();
    }

    public String turnCrank() {
        return this.state.turnCrank() + this.state.dispense();
    }

    String releaseBall() {
        System.out.println("A gumball comes rolling out the slot...");
        if (this.count != 0) {
            --this.count;
        }
        return "releaseBall: \nA gumball comes rolling out the slot...\n\n";
    }

    int getCount() {
        return this.count;
    }

    String refill(int count) {
        this.count += count;
        System.out.println("The gumball machine was just refilled; it's new count is: " + this.count);
        this.state.refill();
        return "The gumball machine was just refilled; it's new count is: " + this.count + "\n";
    }

    void setState(State state) {
        this.state = state;
    }

    public State getState() {
        return this.state;
    }

    public State getSoldOutState() {
        return this.soldOutState;
    }

    public State getNoQuarterState() {
        return this.noQuarterState;
    }

    public State getHasQuarterState() {
        return this.hasQuarterState;
    }

    public State getSoldState() {
        return this.soldState;
    }

    public String toString() {
        StringBuffer result = new StringBuffer();
        result.append("\nMighty Gumball, Inc.");
        result.append("\nJava-enabled Standing Gumball Model #2004");
        result.append("\nInventory: ").append(this.count).append(" gumball");
        if (this.count != 1) {
            result.append("s");
        }

        result.append("\n");
        result.append("Machine is ").append(this.state).append("\n");
        return result.toString();
    }
}