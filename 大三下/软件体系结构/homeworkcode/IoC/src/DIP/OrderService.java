package DIP;


// 高层模块 OrderService 依赖于低层模块 AlipayPaymentService
public class OrderService  {
    private PaymentService paymentService;

    public OrderService(PaymentService paymentService) {
        this.paymentService = paymentService;
    }

    public void processOrder(Order order) {
        // 处理订单逻辑
        this.paymentService.processPayment(order);
    }

}



