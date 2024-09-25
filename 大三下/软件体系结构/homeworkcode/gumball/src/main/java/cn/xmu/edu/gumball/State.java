package cn.xmu.edu.gumball;

public interface State {
    String insertQuarter();

    String ejectQuarter();

    String turnCrank();

    String dispense();

    void refill();
}