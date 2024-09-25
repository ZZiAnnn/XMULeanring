public abstract class Coffee{
   CoffeeImp coffeeImp;
   public void setCoffeeImp(){
      this.coffeeImp = CoffeeImpSingleton.getTheCoffeeImp();
    }
    public CoffeeImp getCoffeeImp() {return this.coffeeImp;}
    public abstract void pourCoffee();
}