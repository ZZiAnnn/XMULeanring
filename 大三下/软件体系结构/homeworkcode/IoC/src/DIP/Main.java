package DIP;

public class Main {
    public static void main(String[] args) {
        PaymentService alipay = new AlipayPaymentService();
        WechatPaymentService wechat = new WechatPaymentService();

        OrderService orderService1 = new OrderService(alipay);
        OrderService orderService2 = new OrderService(wechat);

        Order order = new Order();
        orderService1.processOrder(order);
        orderService2.processOrder(order);
    }
}
