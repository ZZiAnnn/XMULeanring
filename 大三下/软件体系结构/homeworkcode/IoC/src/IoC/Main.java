package IoC;

public class Main {
    public static void main(String[] args) {
        Phone phone1 = new Phone("iphone");
        Person  person1 = new Person(phone1);
        person1.playPhone();

        Phone phone2 = new Phone("HUAWEI");
        Person  person2 = new Person(phone2);
        person2.playPhone();
    }
}