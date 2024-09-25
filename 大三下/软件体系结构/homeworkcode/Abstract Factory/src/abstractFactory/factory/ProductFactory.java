package abstractFactory.factory;

import abstractFactory.product.Phone;
import abstractFactory.product.Router;

public interface ProductFactory {
    Phone getPhone();

    Router getRouter();
}
