package DIP;


// 低层模块 AlipayPaymentService
public class AlipayPaymentService implements PaymentService{
    public void processPayment(Order order) {
        System.out.println("调用支付宝支付接口完成支付");
    }
}

