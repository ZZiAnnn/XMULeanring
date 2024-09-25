package DIP;

public class WechatPaymentService implements PaymentService {
    public void processPayment(Order order) {
        System.out.println("调用微信支付接口完成支付");
    }
}
