package Bridge.cup;


import Bridge.add.Add;

public abstract class Cup {
    protected Add add;

    public Cup(Add add) {
        this.add = add;
    }

    abstract public void drink();
}
