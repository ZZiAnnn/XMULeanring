package cn.xmu.edu.gumball;

public class HasQuarterState implements State {
    GumballMachine gumballMachine;

    public HasQuarterState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public String insertQuarter() {
        System.out.println("You can't insert another quarter");
        return "insertQuarter: You can't insert another quarter\n";
    }

    public String ejectQuarter() {
        System.out.println("Quarter returned");
        this.gumballMachine.setState(this.gumballMachine.getNoQuarterState());
        return "ejectQuarter: Quarter returned\n";
    }

    public String turnCrank() {
        System.out.println("You turned...");
        this.gumballMachine.setState(this.gumballMachine.getSoldState());
        return "turnCrank: You turned...\n";
    }

    public String dispense() {
        System.out.println("No gumball dispensed");
        return "dispense: No gumball dispensed\n";
    }

    public void refill() {
    }

    public String toString() {
        return "waiting for turn of crank\n";
    }
}