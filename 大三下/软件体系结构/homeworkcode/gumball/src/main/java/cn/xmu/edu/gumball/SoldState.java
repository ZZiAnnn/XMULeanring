package cn.xmu.edu.gumball;

public class SoldState implements State {
    GumballMachine gumballMachine;

    public SoldState(GumballMachine gumballMachine) {
        this.gumballMachine = gumballMachine;
    }

    public String insertQuarter() {
        System.out.println("Please wait, we're already giving you a gumball");
        return "insertQuarter: Please wait, we're already giving you a gumball\n";
    }

    public String ejectQuarter() {
        System.out.println("Sorry, you already turned the crank");
        return "ejectQuarter: Sorry, you already turned the crank\n";
    }

    public String turnCrank() {
        System.out.println("Turning twice doesn't get you another gumball!");
        return "turnCrank: Turning twice doesn't get you another gumball!\n";
    }

    public String dispense() {
        String res = this.gumballMachine.releaseBall();
        if (this.gumballMachine.getCount() > 0) {
            this.gumballMachine.setState(this.gumballMachine.getNoQuarterState());
        } else {
            System.out.println("Oops, out of gumballs!");
            this.gumballMachine.setState(this.gumballMachine.getSoldOutState());
            return res + "\ndispense: Oops, out of gumballs!\n";
        }
        return res;
    }

    public void refill() {
    }

    public String toString() {
        return "dispensing a gumball";
    }
}