package abstractFactory.product;

public class HuaweiRouter implements Router {
    @Override
    public void openWifi() {
        System.out.println("华为路由器打开WiFi");
    }

    @Override
    public void setting() {
        System.out.println("华为路由器设置");
    }
}
