package abstractFactory.factory;

import abstractFactory.product.HuaweiPhone;
import abstractFactory.product.HuaweiRouter;
import abstractFactory.product.Phone;
import abstractFactory.product.Router;

public class HuaweiFactory implements ProductFactory {
    @Override
    public Phone getPhone() {
        return new HuaweiPhone();
    }

    @Override
    public Router getRouter() {
        return new HuaweiRouter();
    }
}
