public class CoffeeMain{
   public static void main(String args[]){
 
      //拿出牛奶
		CoffeeImpSingleton coffeeImpSingleton = new CoffeeImpSingleton(new MilkCoffeeImp());

		//中杯加奶
		//MediumCoffee mediumCoffee = new MediumCoffee();
		//mediumCoffee.pourCoffee();

		//大杯加奶
		SuperSizeCoffee superSizeCoffee = new SuperSizeCoffee();
		superSizeCoffee.pourCoffee();
   }

}