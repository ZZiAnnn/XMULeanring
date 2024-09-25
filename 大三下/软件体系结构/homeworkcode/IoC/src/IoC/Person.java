package IoC;

public class Person {
    private Phone myPhone;
    public Person(Phone phone)
    {
        this.myPhone = phone;
    }

    public void playPhone() {
//        this.myPhone = new Phone("iphone");
       System.out.println("play:"+myPhone.getName());
    }
}
