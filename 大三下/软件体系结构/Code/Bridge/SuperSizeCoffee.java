//��
public class SuperSizeCoffee extends Coffee{
   public SuperSizeCoffee() {
   	setCoffeeImp();
   }
   public void pourCoffee(){
     CoffeeImp coffeeImp = this.getCoffeeImp();
     //�������ظ�������˵���ǳ��б����Ǵ� ,�ظ�5���Ǵ�
     for(int i=0;i<5;i++){
       coffeeImp.pourCoffeeImp();
     }
     System.out.println("������" );
   }
}
