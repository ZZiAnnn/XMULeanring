package clothes;

import framework.Product;

public class Clothes extends Product {
    private String owner;
    Clothes(String owner) {
        System.out.println("��" + owner + "�·���");
        this.owner = owner;
    }
    public void use () {
        System.out.println(owner + "���·���");
    }
    public String getOwner() {
        return owner;
    }
}
