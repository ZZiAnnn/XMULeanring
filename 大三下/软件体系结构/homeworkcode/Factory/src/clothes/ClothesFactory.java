package clothes;

import framework.Factory;
import framework.Product;

import java.util.Vector;

public class ClothesFactory extends Clothes {
    private Vector owners = new Vector();
    protected Product createProduct(String owner) {
        return new Clothes(owner);
    }
    protected void registerProduct(Product product) {
        owners.add(((Clothes)product).getOwner());
    }
    public Vector getOwners() {
        return owners;
    }
}
