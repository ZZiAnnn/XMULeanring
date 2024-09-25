import abstractFactory.factory.HuaweiFactory;
import abstractFactory.factory.XiaomiFactory;
import abstractFactory.product.Phone;
import abstractFactory.product.Router;

public class Main {
    public static void main(String[] args) {
        System.out.println("=============小米系列=============");
        XiaomiFactory xiaomiFactory = new XiaomiFactory();
        Phone phone = xiaomiFactory.getPhone();
        phone.callup();
        phone.sendSMS();
        Router router = xiaomiFactory.getRouter();
        router.openWifi();

        System.out.println("=============华为系列=============");
        HuaweiFactory huaweiFactory = new HuaweiFactory();
        phone = huaweiFactory.getPhone();
        phone.callup();
        phone.sendSMS();
        router = huaweiFactory.getRouter();
        router.openWifi();
    }
}