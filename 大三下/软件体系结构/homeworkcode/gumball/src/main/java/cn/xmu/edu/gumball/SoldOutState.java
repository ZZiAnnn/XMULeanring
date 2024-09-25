package cn.xmu.edu.gumball;

public class SoldOutState implements State {
    GumballMachine gumballMachine;

    public SoldOutState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public String insertQuarter() {
        System.out.println("You can't insert a quarter, the machine is sold out");
        return "insertQuarter: You can't insert a quarter, the machine is sold out\n";
    }

    public String ejectQuarter() {
        System.out.println("You can't eject, you haven't inserted a quarter yet");
        return "ejectQuarter: You can't eject, you haven't inserted a quarter yet\n";
    }

    public String turnCrank() {
        System.out.println("You turned, but there are no gumballs");
        return "turnCrank: You turned, but there are no gumballs\n";
    }

    public String dispense() {
        System.out.println("No gumball dispensed");
        return "dispense: No gumball dispensed\n";
    }

    public void refill() {
        this.gumballMachine.setState(this.gumballMachine.getNoQuarterState());
    }

    public String toString() {
        return "sold out";
    }
}