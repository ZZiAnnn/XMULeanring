//�б�
public class MediumCoffee extends Coffee{
     public MediumCoffee() {
       setCoffeeImp();
     }
     public void pourCoffee(){
        CoffeeImp coffeeImp = this.getCoffeeImp();
        //�������ظ�������˵���ǳ��б����Ǵ� ,�ظ�2�����б�
        for (int i=0;i<2;i++){
           coffeeImp.pourCoffeeImp();
        }
        System.out.println("�б�����" );
     }
}
