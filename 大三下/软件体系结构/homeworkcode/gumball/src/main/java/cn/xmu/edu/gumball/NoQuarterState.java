package cn.xmu.edu.gumball;

public class NoQuarterState implements State {
    GumballMachine gumballMachine;

    public NoQuarterState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public String insertQuarter() {
        System.out.println("You inserted a quarter");
        this.gumballMachine.setState(this.gumballMachine.getHasQuarterState());
        return "insertQuarter: You inserted a quarter\n";
    }

    public String ejectQuarter() {
        System.out.println("You haven't inserted a quarter");
        return "ejectQuarter: You haven't inserted a quarter\n";
    }

    public String turnCrank() {
        System.out.println("You turned, but there's no quarter");
        return "turnCrank: You turned, but there's no quarter\n";
    }

    public String dispense() {
        System.out.println("You need to pay first");
        return "dispense: You need to pay first\n";
    }

    public void refill() {
    }

    public String toString() {
        return "waiting for quarter";
    }
}