package abstractFactory.factory;

import abstractFactory.product.Phone;
import abstractFactory.product.Router;
import abstractFactory.product.XiaomiPhone;
import abstractFactory.product.XiaomiRouter;

public class XiaomiFactory implements ProductFactory {

    @Override
    public Phone getPhone() {
        return new XiaomiPhone();
    }

    @Override
    public Router getRouter() {
        return new XiaomiRouter();
    }
}
