public class CoffeeMain{
   public static void main(String args[]){
 
      //�ó�ţ��
		CoffeeImpSingleton coffeeImpSingleton = new CoffeeImpSingleton(new MilkCoffeeImp());

		//�б�����
		//MediumCoffee mediumCoffee = new MediumCoffee();
		//mediumCoffee.pourCoffee();

		//�󱭼���
		SuperSizeCoffee superSizeCoffee = new SuperSizeCoffee();
		superSizeCoffee.pourCoffee();
   }

}