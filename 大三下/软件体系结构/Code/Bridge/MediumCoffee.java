//中杯
public class MediumCoffee extends Coffee{
     public MediumCoffee() {
       setCoffeeImp();
     }
     public void pourCoffee(){
        CoffeeImp coffeeImp = this.getCoffeeImp();
        //我们以重复次数来说明是冲中杯还是大杯 ,重复2次是中杯
        for (int i=0;i<2;i++){
           coffeeImp.pourCoffeeImp();
        }
        System.out.println("中杯来了" );
     }
}
