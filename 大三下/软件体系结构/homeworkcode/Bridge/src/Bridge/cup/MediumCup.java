package Bridge.cup;


import Bridge.add.Add;

public class MediumCup extends Cup {
    public MediumCup(Add add) {
        super(add);
    }

    public void drink() {
        System.out.println("中杯的饮料 " + add.showWhatAdded());
    }
}

