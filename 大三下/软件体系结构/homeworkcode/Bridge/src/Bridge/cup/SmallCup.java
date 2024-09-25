package Bridge.cup;

import Bridge.add.Add;

public class SmallCup extends Cup {
    public SmallCup(Add add) {
        super(add);
    }

    public void drink() {
        System.out.println("小杯的饮料 " + add.showWhatAdded());
    }
}
