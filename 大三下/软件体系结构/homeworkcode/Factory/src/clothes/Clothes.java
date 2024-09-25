package clothes;

import framework.Product;

public class Clothes extends Product {
    private String owner;
    Clothes(String owner) {
        System.out.println("¸ø" + owner + "ÒÂ·þ¡£");
        this.owner = owner;
    }
    public void use () {
        System.out.println(owner + "´©ÒÂ·þ¡£");
    }
    public String getOwner() {
        return owner;
    }
}
