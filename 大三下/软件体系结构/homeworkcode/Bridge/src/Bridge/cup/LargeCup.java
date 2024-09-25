package Bridge.cup;

import Bridge.add.Add;

public class LargeCup extends Cup {
    public LargeCup(Add add) {
        super(add);
    }

    public void drink() {
        System.out.println("大杯的饮料 " + add.showWhatAdded());
    }
}
